#include <iostream>
#include <program.hh>
#include <graph.hh>

extern "C" {
void command(Program *ctx) {
    for (Node *node = ctx->nodes->head; node; node = node->next) {
        ctx->nodes->remove(node);
    }

    for (Arc *arc = ctx->arcs->head; arc; arc = arc->next) {
        ctx->arcs->remove(arc);
    }

    std::cout << "Graph cleaned\n";
}
}
