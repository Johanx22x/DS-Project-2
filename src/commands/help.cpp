#include <cstdio>
#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *) { puts("Hello, world!"); }
}
