#include <program.hh>
#include <iostream>
#include <string>
#include <person.hh>

extern "C" {

void command(Program *ctx) {
  std::cout << "Enter the name of the new node: ";
  std::string name;
  std::getline(std::cin, name);

  if (ctx->recently_charged) {
    Node::next_id = ctx->nodes->size;
    Arc::next_id = ctx->arcs->size;
    ctx->recently_charged = false;
  }
  ctx->nodes->add(new Node(name));

  std::cout << "Node " << name << " created.\n";
}

}
