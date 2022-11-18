#include <program.hh>

extern "C" {
void command(Program *ctx) {

  size_t totalSteps = 0;

  while (true) {
    // primero simulamos lo que hace cada persona
    for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
      if (tmp->currentArc == nullptr) {
        // TODO: asignar el primer arco si la persona no está en uno
        Arc *next = tmp->nextArc();

        if (next == nullptr) {
          ctx->people->remove(tmp);
          continue;
        }

        tmp->currentArc = next;

      } else if (tmp->steps == 0) {

        tmp->steps++;

      } else if (tmp->steps >= tmp->currentArc->time) {

        Proxy<Person> *p = tmp->from->people->find(tmp->id);

        tmp->steps = 0;
        tmp->from->people->remove(p); // NOTE: remove person from previous node
        tmp->from = tmp->currentArc->to;

        tmp->from->people->add(p);
        tmp->currentArc = tmp->nextArc();
      }
    }

    totalSteps++;
  }
}
}
