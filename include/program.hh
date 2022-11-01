#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <linked_list.hh>
#include <graph.hh>

class Program { 
public:
    LinkedList<Node> *nodes = nullptr;
    LinkedList<Arc> *arcs = nullptr;

    Program();
    ~Program();
    void run();
};

#endif
