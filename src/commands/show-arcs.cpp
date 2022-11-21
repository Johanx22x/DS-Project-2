#include <iostream>
#include <graph.hh>
#include <program.hh>
#include <string>

extern "C" {

void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
        return;
    }

  if (ctx->arcs->size == 0) {
    std::cout << "No arcs created yet.\n";
    return;
  } else {
    std::cout << "Arcs in the actual graph:\n";
    std::cout << "---------------------------------\n";
    std::cout << "ID\tTime\tInfo\n";
    std::cout << "=================================\n";
    for (Arc *arc = ctx->arcs->head; arc; arc = arc->next->next) {
        std::cout << arc->id << "\t" << arc->time << "\t" << arc->next->to->name << " <-> " << arc->to->name << "\n";
    }
    std::cout << "---------------------------------\n";
  }
}

}
