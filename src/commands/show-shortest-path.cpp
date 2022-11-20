#include "person.hh"
#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *ctx) {
  for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
    if (tmp->mode == MovementType::DIRECT || tmp->mode == MovementType::THROUGH_ALL) {
        tmp->shortestPath(tmp->from, tmp->to);

        if (!tmp->hasPath) {
            std::cout << "No path found for " << tmp->name << "\n\n";
            continue;
        }

        std::cout << tmp->name << ":\nShortest path from " << tmp->from->name << " to " << tmp->to->name << " is: ";
        while (tmp->path.empty() == false) {
            if (tmp->path.size() == 1) {
                std::cout << tmp->path.front()->name << "\n";
            } else {
                std::cout << tmp->path.front()->name << " -> ";
            }
            tmp->path.pop();
        }
        tmp->hasPath = false;
        tmp->path = std::queue<Node *>();
        tmp->shortestTime = 0;
        std::cout << "\n";
    }
  }
}
}
