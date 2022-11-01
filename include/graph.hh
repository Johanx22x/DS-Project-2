#ifndef GRAPH_HH
#define GRAPH_HH

#include <iostream>
#include <string>

class Node {
public:
    int id;
    std::string name;
    Node *next = nullptr;

    Node(std::string name) : name(name) {}

    void print();
};

class Arc {
public:
    int id;
    Node *to;
    Arc *next = nullptr;

    Arc(Node *to) : to(to) {}

    void print();
};

#endif
