#include "uio.hh"
#include <iostream>
#include <person.hh>
#include <program.hh>
#include <string>

extern "C" {

void command(Program *ctx) {
  if (ctx->simulationDone) {
      std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
      return;
  }

  std::cout << "Enter the name of the person: ";
  std::string name;
  std::getline(std::cin, name);

  std::cout << "1 - Random\n";
  std::cout << "2 - Adjacent\n";
  std::cout << "3 - Through all\n";
  std::cout << "4 - Direct\n";
  std::cout << "Select movement type: ";

  if (ctx->reset) {
    Person::next_id = ctx->people->size;
    ctx->reset = false;
  }

  int movementType = 0;
  while (true) {
    movementType = getInt();
    if (movementType >= 1 && movementType <= 4) {
      break;
    }
    std::cout << "Invalid movement type. Try again: ";
  }

  MovementType type = static_cast<MovementType>(movementType - 1);

  if (type == MovementType::DIRECT || type == MovementType::THROUGH_ALL) {
      if (ctx->nodes->size < 2) {
          std::cout << "There are no sufficient nodes to create a person with this movement type.\nPlese create at least two nodes.\n";
          return;
      }

      std::cout << "Available nodes:\n";
      for (Node *curr = ctx->nodes->head; curr != nullptr; curr = curr->next) {
          std::cout << curr->id << " - " << curr->name << "\n";
      }

      std::cout << "Enter the id of the node from: ";
      int fromId = getInt();

      Node *from = ctx->nodes->find(fromId);
      if (from == nullptr) {
          std::cout << "Invalid node id.\n";
          return;
      }

      std::cout << "Enter the id of the node to: ";
      int toId = getInt();

      Node *to = ctx->nodes->find(toId);
      if (to == nullptr) {
          std::cout << "Invalid node id.\n";
          return;
      }

      if (from == to) {
          std::cout << "The nodes must be different.\n";
          return;
      }

      ctx->people->add(new Person(name, from, to, type));
  } else {
    ctx->people->add(new Person(name, type));
  }

  std::cout << "Person created successfully!\n";
}
}
