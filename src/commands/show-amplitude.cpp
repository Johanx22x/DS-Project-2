#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
        return;
    }

    Node *graph = ctx->nodes->head;
    
    while (graph != nullptr) {
        std::cout << "Node " << graph->name << ":\n";

        for (Proxy<Arc> *arc = graph->arcs->head; arc != nullptr; arc = arc->next) {
            std::cout << "\t" << graph->name << " -> " << arc->link->to->name << " = " << arc->link->time << "m\n";
        }

        graph = graph->next;
    }
}
}
