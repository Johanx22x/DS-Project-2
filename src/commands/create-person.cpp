#include <iostream>
#include <person.hh>
#include <program.hh>
#include <string>

extern "C" {

void command(Program *ctx) {
  std::cout << "Enter the name of the person: ";
  std::string name;
  std::getline(std::cin, name);

  std::cout << "1 - Random\n";
  std::cout << "2 - Adjacent\n";
  std::cout << "3 - Through all\n";
  std::cout << "4 - Direct\n";
  std::cout << "Select movement type: ";

  int movementType = 0;
  while (true) {
    std::cin >> movementType;
    if (movementType >= 1 && movementType <= 4) {
      break;
    }
    std::cout << "Invalid movement type. Try again: ";
  }

  ctx->people->add(new Person(name, MovementType(movementType)));
}
}
