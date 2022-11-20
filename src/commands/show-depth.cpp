#include "proxy.hh"
#include "uio.hh"
#include <iostream>
#include <program.hh>
#include <graph.hh>

void depth(Node *start) {
  if ((start == nullptr) || start->visited) {
    std::cout << "\n";
    return;
  }

  start->visited = true;

  for (Proxy<Arc> *arc = start->arcs->head; arc; arc = arc->next) {
      std::cout << start->name << " -> " << arc->link->to->name << " : " << arc->link->time << ", ";
      depth(arc->link->to);
  }
}

void unmark_all(Node *start) {
  while (start) {
    start->visited = false;
    start = start->next;
  }
}

extern "C" {
void command(Program *ctx) {
  std::cout << "Available nodes:\n";
  std::cout << "-------------------------\n";
  std::cout << "ID\tName\n";
  std::cout << "=========================\n";
  for (Node *node = ctx->nodes->head; node; node = node->next) {
      std::cout << node->id << "\t" << node->name << "\n";
  }
  std::cout << "-------------------------\n";

  std::cout << "Enter the ID of the node to start from calculating the depth: ";
  int id = getInt();
  Node *start = ctx->nodes->find(id);
  if (start == nullptr) {
    std::cout << "Node with ID " << id << " not found.\n";
    return;
  }
  std::cout << "Depth from " << start->name << ":\n";
  depth(start);
  unmark_all(ctx->nodes->head);
}
}
