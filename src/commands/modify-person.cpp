#include <proxy.hh>
#include <graph.hh>
#include <program.hh>
#include <iostream>
#include <string>
#include <uio.hh>

extern "C" {

void command(Program *ctx) {
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
        // TODO: Change person movement type
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
