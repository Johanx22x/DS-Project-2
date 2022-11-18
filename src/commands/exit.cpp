#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *) {
    std::cout << "See you later!\n";
    exit(0);
}
}
