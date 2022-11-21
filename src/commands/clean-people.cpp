#include <person.hh>
#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
        return;
    }
    for (Person *person = ctx->people->head; person; person = person->next) {
        ctx->people->remove(person);
    }

    std::cout << "All people removed!\n";
}
}
