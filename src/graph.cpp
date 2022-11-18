#include <iostream>
#include <string>
#include <graph.hh>
#include <uio.hh>

int Arc::next_id = 0;

void Arc::toString() {
    std::cout << "Arc (" << this->id << ") to " << this->to->name << " with time " << this->time << "\n";
}

Arc::Arc(Node *to) {
    this->to = to;
    time = getRandomInt(1, 50);
}

int Node::next_id = 0;

void Node::toString() {
    std::cout << "Node (" << this->id << ") " << this->name << "\n";
}
