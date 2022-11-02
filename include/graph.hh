#ifndef GRAPH_HH
#define GRAPH_HH

#include <iostream>
#include <string>
#include <npc.hh>
#include <player.hh>
#include <queue>
#include <linked_list.hh>
#include <proxy.hh>

class Node {
public:
    int id;
    std::string name;
    Node *next = nullptr;
    Proxy<NPC> *npc = nullptr;
    Proxy<Player> *player = nullptr;
    LinkedList<Proxy<class Arc>> *arcs = new LinkedList<Proxy<class Arc>>();

    Node(std::string name) : name(name) {}

    void toString();
};

class Arc {
public:
    int id;
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
