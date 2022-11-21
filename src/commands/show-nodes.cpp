#include <iostream>
#include <graph.hh>
#include <program.hh>
#include <string>

extern "C" {

void command(Program *ctx) {
  if (ctx->nodes->size == 0) {
    std::cout << "No nodes created yet.\n";
    return;
  }
  std::cout << "Nodes in the actual graph:\n";
  std::cout << "-------------------------\n";
  std::cout << "ID\tName\n";
  std::cout << "=========================\n";
  for (Node *node = ctx->nodes->head; node; node = node->next) {
      std::cout << node->id << "\t" << node->name << "\n";
      for (Proxy<Arc> *arc = node->arcs->head; arc; arc = arc->next) {
        std::cout << "\t" << " -> " << arc->link->to->name << "\n";
      }
      std::cout << "\n";
  }
  std::cout << "-------------------------\n";
}

}
