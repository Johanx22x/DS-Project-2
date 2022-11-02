#include <iostream>
#include <string>
#include <graph.hh>

Arc::Arc(int time, Node *node) {
    this->time = time;
    this->to = node;

    int i = 0;
    while (i < this->time) {
        this->queue->push(0);
        i++;
    }
}

void Arc::toString() {
    std::cout << "Arc (" << this->id << ") to " << this->to->name << " with time " << this->time << "\n";
}

void Node::toString() {
    std::cout << "Node (" << this->id << ") " << this->name << "\n";
}
