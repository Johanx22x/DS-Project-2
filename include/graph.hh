#ifndef GRAPH_HH
#define GRAPH_HH

#include <iostream>
#include <string>
#include <npc.hh>
#include <player.hh>
#include <queue>

class Node {
public:
    int id;
    std::string name;
    NPC *NPCList = nullptr;
    Player *PlayerList = nullptr;
    Node *next = nullptr;

    Node(std::string name) : name(name) {}

    void toString();
};

class Arc {
public:
    int id;
    int time;
    Node *to;
    std::queue<NPC> *NPCQueue = nullptr;
    std::queue<Player> *PlayerQueue = nullptr;
    std::queue<int> *queue = nullptr; // TODO: Initialize the queue with 0's 
    Arc *next = nullptr;

    Arc(Node *to) : to(to) {}

    void toString();
};

#endif
