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
  // Check if exist people
  if (!ctx->people->size) {
    std::cout << "No people to modify!\n";
    return;
  }

  std::cout << "Available people:\n";
  std::cout << "-------------------------\n";
  std::cout << "ID\tName\n";
  std::cout << "=========================\n";
  for (Person *curr = ctx->people->head; curr; curr = curr->next) {
    std::cout << curr->id << "\t" << curr->name << "\n";
  }
  std::cout << "-------------------------\n";

  std::cout << "Enter person id: ";
  int idToFind = getInt();

  Person *person = ctx->people->find(idToFind);
  if (!person) {
    std::cout << "Person not found!\n";
    return;
  }

  bool special = false;

  std::cout << "Options:\n";
  std::cout << "1 : Change person name\n";
  std::cout << "2 : Change person movement type\n";
  std::cout << "3 : Delete person\n";
  if (person->from) {
    std::cout << "4 : Change person start position\n";
    std::cout << "5 : Change person end position\n";
    special = true;
  }
  std::cout << "Select option: ";
  int option = getInt();

  switch (option) {
    case 1: {
      std::cout << "Enter new name: ";
      std::string name;
      getline(std::cin, name);
      person->name = name;
      std::cout << "Person name changed!\n";
      break;
    }
    case 2: {
      std::cout << "1 - Random\n";
      std::cout << "2 - Adjacent\n";
      std::cout << "3 - Through all\n";
      std::cout << "4 - Direct\n";
      std::cout << "Select movement type: ";
      
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
          std::cout << "There are no sufficient nodes to modify this person with this movement type.\nPlese create at least two nodes.\n";
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

        person->from = from;
        person->to = to;
      }
      person->mode = type;
      break;
    }
    case 3: {
      ctx->people->remove(person);
      std::cout << "Person deleted!\n";
      break;
    }
    case 4: {
      if (!special) {
        std::cout << "Invalid option!\n";
        break;
      }
      std::cout << "Available nodes:\n";
      std::cout << "-------------------------\n";
      std::cout << "ID\tName\n";
      std::cout << "=========================\n";
      for (Node *node = ctx->nodes->head; node; node = node->next) {
          std::cout << node->id << "\t" << node->name << "\n";
      }
      std::cout << "-------------------------\n";
      std::cout << "Enter new start position id: ";
      Node *node = ctx->nodes->find(getInt());
      if (!node) {
        std::cout << "Node not found!\n";
        break;
      }
      if (person->to == node) {
        std::cout << "Start and end position can't be the same!\n";
        break;
      }
      if (person->from == node) {
        std::cout << "Start position already set!\n";
        break;
      }
      person->from = node;
      std::cout << "Person start position changed!\n";
      break;
    }
    case 5: {
      if (!special) {
        std::cout << "Invalid option!\n";
        break;
      }
      std::cout << "Available nodes:\n";
      std::cout << "-------------------------\n";
      std::cout << "ID\tName\n";
      std::cout << "=========================\n";
      for (Node *node = ctx->nodes->head; node; node = node->next) {
          std::cout << node->id << "\t" << node->name << "\n";
      }
      std::cout << "-------------------------\n";
      std::cout << "Enter new end position id: ";
      Node *node = ctx->nodes->find(getInt());
      if (!node) {
        std::cout << "Node not found!\n";
        break;
      }
      if (person->from == node) {
        std::cout << "Start and end position can't be the same!\n";
        break;
      }
      if (person->to == node) {
        std::cout << "End position already set!\n";
        break;
      }
      person->to = node;
      std::cout << "Person end position changed!\n";
      break;
    }
    default: {
      std::cout << "Invalid option!\n";
      break;
    }
  }
}

}
