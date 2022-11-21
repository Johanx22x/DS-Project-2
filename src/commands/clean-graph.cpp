#include <iostream>
#include <program.hh>
#include <graph.hh>

extern "C" {
void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
        return;
    }
    
    for (Node *node = ctx->nodes->head; node; node = node->next) {
        ctx->nodes->remove(node);
    }

    for (Arc *arc = ctx->arcs->head; arc; arc = arc->next) {
        ctx->arcs->remove(arc);
    }

    std::cout << "Graph cleaned\n";
}
}
