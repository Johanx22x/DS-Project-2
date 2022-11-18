#include <iostream>
#include <person.hh>
#include <program.hh>
#include <string>

extern "C" {

void command(Program *ctx) {
  if (ctx->people->size == 0) {
    std::cout << "No people created yet.\n";
    return;
  } else {
    std::cout << "People in the actual graph:\n";
    for (Person *curr = ctx->people->head; curr != nullptr; curr = curr->next) {
        std::cout << "ID: " << curr->id << "\n";
        std::cout << "Name: " << curr->name << "\n";
        switch (curr->mode) {
            case MovementType::DIRECT:
                std::cout << "Movement type: direct\n";
                break;
            case MovementType::RANDOM:
                std::cout << "Movement type: random\n";
                break;
            case MovementType::ADJACENT:
                std::cout << "Movement type: adjacent\n";
                break;
            case MovementType::THROUGH_ALL:
                std::cout << "Movement type: through all\n";
                break;
        }
        if (curr->from != nullptr && curr->to != nullptr) {
            std::cout << "From: " << curr->from->name << "\n";
            std::cout << "To: " << curr->to->name << "\n";
        }
    }
  }
}

}
