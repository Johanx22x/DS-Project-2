#include <person.hh>
#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *ctx) {
    for (Person *person = ctx->people->head; person; person = person->next) {
        ctx->people->remove(person);
    }

    std::cout << "All people removed!\n";
}
}
