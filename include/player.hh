#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>

enum PlayerMovements {
    THROUGH_ALL,
    DIRECT
};

class Player {
public:
    int id;
    std::string name;
    int steps = 0;
    class Arc *currentArc = nullptr;
    class Node *from = nullptr;
    class Node *to = nullptr;
    PlayerMovements mode;
    Player *friends = nullptr;
    Player *next = nullptr;

    Player(int id, std::string name, Node from, Node to, PlayerMovements mode);

    void addFriend(Player *player);

    std::string toString();
};

#endif
