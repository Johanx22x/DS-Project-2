#include <iostream>
#include <graph.hh>
#include <program.hh>
#include <string>

extern "C" {

void command(Program *ctx) {
  if (ctx->nodes->size == 0) {
    std::cout << "No nodes created yet.\n";
    return;
  } else {
    std::cout << "Nodes in the actual graph:\n";
    for (Node *curr = ctx->nodes->head; curr != nullptr; curr = curr->next) {
        std::cout << "\nID: " << curr->id << "\n";
        std::cout << "Name: " << curr->name << "\n";
    }
  }
}

}
