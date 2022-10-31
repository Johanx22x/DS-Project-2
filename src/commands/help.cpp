#include <context.hh>
#include <iostream>

void print() {
  std::cout << "nigger dog\n";
}

extern "C" {
void command(Context *ctx) {
  (void)ctx;
  print();
}
}
