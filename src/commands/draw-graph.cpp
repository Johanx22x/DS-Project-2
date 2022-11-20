#include <cstdio>
#include <iostream>
#include <program.hh>
#include <uio.hh>

extern "C" {
void command(Program *ctx) { 
    FILE *f = fopen("graph.dot", "w");
    dumpGraph(f, ctx->nodes);
    compileGraph("graph.png");
    std::cout << "Graph saved to ./graph.png\n";
}
}
