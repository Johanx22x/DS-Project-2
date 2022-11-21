#include <cstdio>
#include <iostream>
#include <program.hh>
#include <uio.hh>

extern "C" {
void command(Program *ctx) { 
  if (ctx->simulationDone) {
      std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
      return;
  }

    FILE *f = fopen("graph.dot", "w");
    dumpGraph(f, ctx->nodes);
    compileGraph("graph.png");
    std::cout << "Graph saved to ./graph.png\n";
}
}
