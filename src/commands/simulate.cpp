#include "linked_list.hh"
#include "proxy.hh"
#include <cstdio>
#include <encoding.hh>
#include <person.hh>
#include <program.hh>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void saveActualGraph(Program *ctx) {
  // Encode the actual graph
  char *buffer = new char[64000];
  encodeNodes(ctx->nodes, buffer);

  char *buffer2 = new char[64000];
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

LinkedList<Proxy<Person>> *copyPeople(LinkedList<Person> *ctxPeople) {
  LinkedList<Proxy<Person>> *newPeople = new LinkedList<Proxy<Person>>();
  for (Person *tmp = ctxPeople->head; tmp; tmp = tmp->next) {
    newPeople->add(new Proxy<Person>(tmp));
  }
  return newPeople;
}

#define INF 1000

void shortestPathThroughAll(Person *player, LinkedList<Node> *graph) {
  int matrix[graph->size][graph->size];
  for (int i = 0; i < graph->size; i++)
    for (int j = 0; j < graph->size; j++)
      if (i == j)
        matrix[i][j] = 0;
      else
        matrix[i][j] = INF;

  for (Node *node = graph->head; node != nullptr; node = node->next) {
    for (Proxy<Arc> *arc = node->arcs->head; arc != nullptr; arc = arc->next) {
      matrix[node->id][arc->link->to->id] = arc->link->time;
    }
  }

  for (int k = 0; k < graph->size; k++) {
    for (int i = 0; i < graph->size; i++) {
      for (int j = 0; j < graph->size; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
          matrix[i][j] = matrix[i][k] + matrix[k][j];
        }
      }
    }
  }

  for (int i = 0; i < graph->size; i++) {
    for (int j = 0; j < graph->size; j++) {
      int dist = matrix[i][j];
      if (dist < INF) {
        printf("\t%d", dist);
      } else
        printf("\tINF");
    }
    puts("\n");
  }

  for (int i = 0; i < graph->size; i++) {
    Node *next = graph->find(matrix[i][i + 1]);
    player->path.push(next);
  }
}

LinkedList<Person> *copy_people(LinkedList<Person> *ctxPeople) {
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

  size_t totalMinutes = 0;

  Person *firstToFinish = nullptr;
  Person *lastToFinish = nullptr;

  bool valid = false;
  for (Proxy<Person> *tmp = peopleBackup->head; tmp != nullptr;
       tmp = tmp->next) {
    if (tmp->link->mode == MovementType::THROUGH_ALL) {
      /* peopleBackup->remove(tmp); // FIX: Temporarily remove people who are
       * going */
      // through all nodes
      shortestPathThroughAll(tmp->link, ctx->nodes);
    }
    if (!tmp->link->from) {
      continue;
    }
    tmp->link->shortestPath(tmp->link->from, tmp->link->to);
    valid = true;
  }
  if (!valid) {
    std::cout << "Cannot simulate, create a person with a movement type "
                 "'direct' or 'through all' first!\n";
    return;
  }

  // Remove the first node in the person path (for Direct and Through all),
  // because it is the starting point We don't need to simulate the person going
  // to the starting point
  for (Proxy<Person> *tmp = peopleBackup->head; tmp; tmp = tmp->next) {
    if (!tmp->link->from) {
      tmp->link->from = ctx->nodes->head;
      continue;
    }
    tmp->link->path.pop();
  }

  std::cout << "All ready to simulate!\n";

  while (true) {
    // primero simulamos lo que hace cada persona
    bool allFinished = true;
    for (Proxy<Person> *tmp = peopleBackup->head; tmp != nullptr; tmp = tmp->next) {

      // Check if the person is walking
      if (tmp->link->currentArc != nullptr) {
          std::cout << tmp->link->name << " is going to " << tmp->link->to->name << "\n";
          std::cout << "Steps left: " << tmp->link->currentArc->time - tmp->link->steps << "\n";
      }

      // Check if the simulation is finished
      if (tmp->link->mode == MovementType::DIRECT || tmp->link->mode == MovementType::THROUGH_ALL) {
          allFinished = false;
      }

      // Check if the person is in a node
      if (tmp->link->currentArc == nullptr) {
        Arc *next = tmp->link->nextArc();

        if (next == nullptr) {
          lastToFinish = tmp->link;
          peopleBackup->remove(tmp);
          continue;
        }

        tmp->link->currentArc = next;
        tmp->link->to = next->to; // TEST: Esto se hace debido a que el parametro `to` de la persona inicia siendo el punto final
                                  
        tmp->link->from->people->remove(tmp->link->from->people->find(tmp->link->id));
      } else if (tmp->link->steps >= tmp->link->currentArc->time) {

        Proxy<Person> *p = tmp->link->from->people->find(tmp->link->id);

        tmp->link->steps = 0;
        tmp->link->prev = tmp->link->from;
        tmp->link->from = tmp->link->currentArc->to;

        tmp->link->from->people->add(p);
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

        tmp->link->from->people->remove(
            p); // NOTE: remove person from previous node
      } else {
        tmp->link->steps++;
        std::cout << "Person " << tmp->link->name
                  << " steps: " << tmp->link->steps << "\n";
      }
    }

    totalMinutes++;

    if (allFinished)
      break;
  }

  printf("Simulation finished after %zu minutes\n", totalMinutes);
  printf("The first person to finish was: %s\n", firstToFinish->name.c_str());
  printf("The last person to finish was: %s\n", lastToFinish->name.c_str());

  Person *mostFriends = nullptr;
  for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
    if (mostFriends->friends->size < tmp->friends->size)
      mostFriends = tmp;
  }

  printf("%s has the most friends, they have %d friends!\n",
         mostFriends->name.c_str(), mostFriends->friends->size);

  ctx->people = peopleBackupCopy;
}
}
