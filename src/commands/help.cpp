#include <iostream>
#include <program.hh>

void print() { std::cout << "nigger dog\n"; }

extern "C" {
void command(Program *ctx) {
  (void)ctx;
  print();
}
}
