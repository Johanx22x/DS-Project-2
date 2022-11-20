#include "linked_list.hh"
#include "proxy.hh"
#include <person.hh>
#include <cstdio>
#include <program.hh>
#include <encoding.hh>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void saveActualGraph(Program *ctx) {
  // Encode the actual graph
  char* buffer = new char[64000];
  encodeNodes(ctx->nodes, buffer);

  char* buffer2 = new char[64000];
  encodeArcs(ctx->arcs, buffer2);

  std::string dirName = ".PS";
  dirName = "./GRAPHS/" + dirName;

  if (!(access(dirName.c_str(), F_OK) == 0)) {
      if (mkdir(dirName.c_str(), 0777) == -1) {
          std::cout << "Error saving graph!\n";
          return;
      }
  }

  std::string nodesPath = dirName + "/nodes.bin";
  FILE *out = fopen(nodesPath.c_str(), "w");
  fprintf(out, "%s", buffer);
  fflush(out);
  fclose(out);

  std::string arcsPath = dirName + "/arcs.bin";
  out = fopen(arcsPath.c_str(), "w");
  fprintf(out, "%s", buffer2);
  fflush(out);
  fclose(out);
}

LinkedList<Proxy<Person>>* copyPeople(LinkedList<Person> *ctxPeople) {
    LinkedList<Proxy<Person>> *newPeople = new LinkedList<Proxy<Person>>();
    for (Person *tmp = ctxPeople->head; tmp; tmp = tmp->next) {
        newPeople->add(new Proxy<Person>(tmp));
    }
    return newPeople;
}

LinkedList<Person>* copy_people(LinkedList<Person> *ctxPeople) {
    LinkedList<Person> *newPeople = new LinkedList<Person>();
    for (Person *tmp = ctxPeople->head; tmp; tmp = tmp->next) {
        newPeople->add(new Person(tmp->name, tmp->from, tmp->to, tmp->mode));
    }
    return newPeople;
}

extern "C" {

void command(Program *ctx) {
  // Save the actual GRAPH 
  saveActualGraph(ctx);
  LinkedList<Proxy<Person>> *peopleBackup = new LinkedList<Proxy<Person>>();
  peopleBackup = copyPeople(ctx->people);

  LinkedList<Person> *peopleBackupCopy = copy_people(ctx->people);

  puts("Simulation started");
  size_t totalMinutes = 0;

  Person *firstToFinish = nullptr;
  Person *lastToFinish = nullptr;

  bool valid = false;
  for (Proxy<Person> *tmp = peopleBackup->head; tmp != nullptr; tmp = tmp->next) {
    if (tmp->link->mode == MovementType::THROUGH_ALL) {
        peopleBackup->remove(tmp); // FIX: Temporarily remove people who are going through all nodes
    }
    if (!tmp->link->from) continue;
    tmp->link->shortestPath(tmp->link->from, tmp->link->to);
    valid = true;
  }
  if (!valid) {
    std::cout << "Cannot simulate, create a person with a movement type 'direct' or 'through all' first!\n";
    return;
  }

  // Remove the first node in the person path (for Direct and Through all), because it is the starting point
  // We don't need to simulate the person going to the starting point
  for (Proxy<Person> *tmp = peopleBackup->head; tmp; tmp = tmp->next) {
    if (!tmp->link->from) continue;
    tmp->link->path.pop();
  }

  std::cout << "Simulation started\n";

  while (true) {
    // primero simulamos lo que hace cada persona
    bool allFinished = true;
    for (Proxy<Person> *tmp = peopleBackup->head; tmp != nullptr; tmp = tmp->next) {
      if (tmp->link->mode == MovementType::DIRECT || tmp->link->mode == MovementType::THROUGH_ALL) allFinished = false;
      std::cout << "DEBUG: first\n";
      if (tmp->link->currentArc == nullptr) {
        Arc *next = tmp->link->nextArc();
        std::cout << "DEBUG: second\n";

        if (next == nullptr) {

          if (!firstToFinish) firstToFinish = tmp->link; // WARNING: This could be an error

          lastToFinish = tmp->link;
          peopleBackup->remove(tmp);
          continue;
        }

        std::cout << "DEBUG: third\n";

        tmp->link->currentArc = next;
        tmp->link->to = next->to; // TEST: Esto se hace debido a que el parametro `to`
                            // de la persona inicia siendo el punto final
        std::cout << "DEBUG: fourth\n";

      } else if (tmp->link->steps >= tmp->link->currentArc->time) {
          std::cout << "DEBUG: fifth\n";

        Proxy<Person> *p = tmp->link->from->people->find(tmp->link->id);

        std::cout << "DEBUG: sixth\n";
        tmp->link->steps = 0;
        tmp->link->prev = tmp->link->from;
        tmp->link->from = tmp->link->currentArc->to;

        std::cout << "DEBUG: seventh\n";

        tmp->link->from->people->add(p);
        tmp->link->currentArc = tmp->link->nextArc();
        tmp->link->to = tmp->link->currentArc->to;

        std::cout << "DEBUG: eighth\n";

        std::cout << tmp->link->name << " is now in " << tmp->link->from->name << "\n";

        // make the panas
        for (Proxy<Person> *_friend = tmp->link->from->people->head;
             _friend != nullptr; _friend = _friend->next) {
          if (_friend->link == tmp->link)
            continue;

          if (tmp->link->addFriend(_friend->link)) {
            printf("%s is now friends with %s\n", tmp->link->name.c_str(),
                   _friend->link->name.c_str());
          }
        }

        std::cout << "DEBUG: ninth\n";

        tmp->link->from->people->remove(p); // NOTE: remove person from previous node
      } else {
        tmp->link->steps++;
      }
    }

    if (allFinished) break;

    totalMinutes++;
  }

  printf("Simulation finished after %zu minutes\n", totalMinutes);
  printf("The first person to finish was: %s\n", firstToFinish->name.c_str());
  printf("The last person to finish was: %s\n", lastToFinish->name.c_str());

  Person *mostFriends = nullptr;
  for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
    if (mostFriends->friends->size < tmp->friends->size)
      mostFriends = tmp;
  }

  printf("%s has the most friends, they have %d friends!\n", mostFriends->name.c_str(), mostFriends->friends->size);

  ctx->people = peopleBackupCopy;
}
}
