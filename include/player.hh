#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>
#include <graph.hh>

enum PlayerMovements {
    THROUGH_ALL,
    DIRECT
};

class Player {
public:
    int id;
    std::string name;
    Node *from = nullptr;
    Node *to = nullptr;
    PlayerMovements mode;
    Player *friends = nullptr;
    Player *next = nullptr;

    Player(int id, std::string name, Node from, Node to, PlayerMovements mode);

    void toString();
};

#endif
