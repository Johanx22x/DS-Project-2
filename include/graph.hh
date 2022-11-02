#ifndef GRAPH_HH
#define GRAPH_HH

#include <iostream>
#include <string>
#include <person.hh>
#include <queue>
#include <linked_list.hh>
#include <proxy.hh>

class Node {
    static int next_id;
public:
    int id = next_id++;
    std::string name;
    Node *next = nullptr;
    Proxy<Person> *people = nullptr;
    LinkedList<Proxy<class Arc>> *arcs = new LinkedList<Proxy<class Arc>>();

    Node(std::string name) : name(name) {}

    void toString();
};

class Arc {
    static int next_id;
public:
    int id = next_id++;
    int time;
    Node *to;
    /* std::queue<NPC> *NPCQueue = new std::queue<NPC>; */
    /* std::queue<Player> *PlayerQueue = new std::queue<Player>; */
    /* std::queue<int> *queue = new std::queue<int>; */
    Arc *next = nullptr;

    Arc(int time, Node *to) : time(time), to(to) {}

    void toString();
};

#endif
