#include <proxy.hh>
#include <graph.hh>
#include <program.hh>
#include <iostream>
#include <string>
#include <uio.hh>

extern "C" {

void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
        return;
    }
  // Check if exist nodes
  if (!ctx->nodes->size) {
    std::cout << "No nodes in the graph to modify!\n";
    return;
  }

  std::cout << "Available nodes:\n";
  std::cout << "-------------------------\n";
  std::cout << "ID\tName\n";
  std::cout << "=========================\n";
  for (Node *node = ctx->nodes->head; node; node = node->next) {
      std::cout << node->id << "\t" << node->name << "\n";
  }
  std::cout << "-------------------------\n";

  std::cout << "Enter node id: ";
  int idToFind = getInt();

  Node *node = ctx->nodes->find(idToFind);
  if (!node) {
    std::cout << "Node not found!\n";
    return;
  }

  std::cout << "Options:\n";
  std::cout << "1 : Change node name\n";
  std::cout << "2 : Delete node\n";
  std::cout << "Select option: ";
  int option = getInt();

  switch (option) {
    case 1: {
      std::cout << "Enter new name: ";
      std::string newName = "";
      std::getline(std::cin, newName);
      node->name = newName;
      std::cout << "Node name changed to " << newName << "\n";
      break;
    }
    case 2: {
      for (Arc *arc = ctx->arcs->head; arc; arc = arc->next->next) {
        if (arc->next->to == node || arc->to == node) {
          ctx->arcs->remove(arc);
          ctx->arcs->remove(arc->next);
        }
      }
      for (Node *n = ctx->nodes->head; n; n = n->next) {
        for (Proxy<Arc> *arc = n->arcs->head; arc; arc = arc->next) {
          if (arc->link->to == node) {
            n->arcs->remove(arc);
          }
        }
      }
      for (Person *person = ctx->people->head; person; person = person->next) {
        if (person->from == node) {
          person->from = nullptr;
        }
      }
      ctx->nodes->remove(node);
      std::cout << "Node deleted!\n";
      break;
    }
    default: {
      std::cout << "Invalid option!\n";
      break;
    }
  }
}

}
