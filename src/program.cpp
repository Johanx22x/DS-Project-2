#include <program.hh>
#include <sys/types.h>

Program::Program() {}

void Program::run() {
  size_t totalSteps = 0;

  while (true) {
    // primero simulamos lo que hace cada persona
    for (Person *tmp = this->people->head; tmp != nullptr; tmp = tmp->next) {
      if (tmp->steps == 0) {
        tmp->steps++;
        continue;
      }

      if (tmp->steps >= tmp->currentArc->time) {
        Proxy<Person> *p = tmp->from->people->find(tmp->id);
        tmp->steps = 0;
        tmp->from->people->remove(p); // NOTE: remove person from previous node
        tmp->from = tmp->currentArc->to;

        tmp->from->people->add(p);
        /* tmp->currentArc-> */
        // tmp->to = TODO: implementar la función que le dije johan
      }
    }

    totalSteps++;
  }
}
