#include <person.hh>
#include <cstdio>
#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *ctx) { 
    ctx->people->add(new Person("Mark Zuckerberg", MovementType::RANDOM));
    ctx->people->add(new Person("Steve Jobs", MovementType::RANDOM));
    ctx->people->add(new Person("Bill Gates", MovementType::RANDOM));
    ctx->people->add(new Person("Elon Musk", MovementType::RANDOM));
    ctx->people->add(new Person("Jeff Bezos", MovementType::RANDOM));

    ctx->people->add(new Person("Barack Obama", MovementType::ADJACENT));
    ctx->people->add(new Person("Donald Trump", MovementType::ADJACENT));
    ctx->people->add(new Person("Vladimir Putin", MovementType::ADJACENT));
    ctx->people->add(new Person("Xi Jinping", MovementType::ADJACENT));
    ctx->people->add(new Person("Angela Merkel", MovementType::ADJACENT));

    ctx->people->add(new Person("Cristiano Ronaldo", ctx->nodes->find(0), ctx->nodes->find(2), MovementType::THROUGH_ALL));
    ctx->people->add(new Person("Lionel Messi", ctx->nodes->find(1), ctx->nodes->find(4), MovementType::THROUGH_ALL));
    ctx->people->add(new Person("Neymar", ctx->nodes->find(2), ctx->nodes->find(0), MovementType::THROUGH_ALL));
    ctx->people->add(new Person("Kylian Mbappe", ctx->nodes->find(1), ctx->nodes->find(3), MovementType::THROUGH_ALL));
    ctx->people->add(new Person("Mohamed Salah", ctx->nodes->find(2), ctx->nodes->find(4), MovementType::THROUGH_ALL));

    ctx->people->add(new Person("Leonardo Viquez", ctx->nodes->find(0), ctx->nodes->find(4), MovementType::DIRECT));
    ctx->people->add(new Person("Abel Mendez", ctx->nodes->find(1), ctx->nodes->find(2), MovementType::DIRECT));
    ctx->people->add(new Person("Lorena Valerio", ctx->nodes->find(0), ctx->nodes->find(3), MovementType::DIRECT));
    ctx->people->add(new Person("Jorge Alfaro", ctx->nodes->find(3), ctx->nodes->find(0), MovementType::DIRECT));
    ctx->people->add(new Person("Rogelio Quiros", ctx->nodes->find(2), ctx->nodes->find(3), MovementType::DIRECT));

    ctx->reset = true;

    std::cout << "Default people loaded\n";
}
}
