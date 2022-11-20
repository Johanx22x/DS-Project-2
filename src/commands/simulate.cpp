#include <person.hh>
#include <cstdio>
#include <program.hh>

extern "C" {

void command(Program *ctx) {

  puts("Simulation started");
  size_t totalMinutes = 0;

  Person *firstToFinish = nullptr;
  Person *lastToFinish = nullptr;

  bool valid = false;
  for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
    if (!tmp->from) continue;
    tmp->shortestPath(tmp->from, tmp->to);
    valid = true;
  }
  if (!valid) {
    std::cout << "Cannot simulate, create a person with a movement type 'direct' or 'through all' first!\n";
    return;
  }

  // Remove the first node in the person path (for Direct and Through all), because it is the starting point
  // We don't need to simulate the person going to the starting point
  for (Person *tmp = ctx->people->head; tmp; tmp = tmp->next) {
    if (!tmp->from) continue;
    tmp->path.pop();
  }

  while (true) {
    // primero simulamos lo que hace cada persona
    bool allFinished = true;
    for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
      if (tmp->mode == MovementType::DIRECT || tmp->mode == MovementType::THROUGH_ALL) allFinished = false;
      if (tmp->currentArc == nullptr) {
        Arc *next = tmp->nextArc();

        if (next == nullptr) {

          if (!firstToFinish) firstToFinish = tmp; // WARNING: This could be an error

          lastToFinish = tmp;
          ctx->people->remove(tmp);
          continue;
        }

        tmp->currentArc = next;
        tmp->to = next->to; // TEST: Esto se hace debido a que el parametro `to`
                            // de la persona inicia siendo el punto final

      } else if (tmp->steps >= tmp->currentArc->time) {

        Proxy<Person> *p = tmp->from->people->find(tmp->id);

        tmp->steps = 0;
        tmp->prev = tmp->from;
        tmp->from = tmp->currentArc->to;

        tmp->from->people->add(p);
        tmp->currentArc = tmp->nextArc();
        tmp->to = tmp->currentArc->to;

        // make the panas
        for (Proxy<Person> *_friend = tmp->from->people->head;
             _friend != nullptr; _friend = _friend->next) {
          if (_friend->link == tmp)
            continue;

          if (tmp->addFriend(_friend->link)) {
            printf("%s is now friends with %s\n", tmp->name.c_str(),
                   _friend->link->name.c_str());
          }
        }

        tmp->from->people->remove(p); // NOTE: remove person from previous node
      } else {
        tmp->steps++;
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

  printf("%s has the most friends, they have %d friends!\n",
         mostFriends->name.c_str(), mostFriends->friends->size);
}
}
