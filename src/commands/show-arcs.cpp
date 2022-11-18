#include <iostream>
#include <graph.hh>
#include <program.hh>
#include <string>

extern "C" {

void command(Program *ctx) {
  if (ctx->arcs->size == 0) {
    std::cout << "No arcs created yet.\n";
    return;
  } else {
    std::cout << "Arcs in the actual graph:\n";
    for (Arc *curr = ctx->arcs->head; curr != nullptr; curr = curr->next) {
        std::cout << "\nID: " << curr->id << "\n";
        std::cout << "To: " << curr->to->name << "\n";
        std::cout << "Distance: " << curr->time << "m\n";
    }
  }
}

}
