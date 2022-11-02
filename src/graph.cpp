#include <iostream>
#include <string>
#include <graph.hh>

void Arc::toString() {
    std::cout << "Arc (" << this->id << ") to " << this->to->name << " with time " << this->time << "\n";
}

void Node::toString() {
    std::cout << "Node (" << this->id << ") " << this->name << "\n";
}
