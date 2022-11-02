#ifndef NPC_HH
#define NPC_HH

#include <iostream>
#include <string>

enum NPCMovements {
    RANDOM,
    ADJACENT
};

class NPC {
public:
    int id;
    std::string name;
    int steps = 0;
    NPCMovements mode;
    NPC *friends = nullptr;
    NPC *next = nullptr;

    NPC(int id, std::string name, NPCMovements mode);

    std::string toString();
};

#endif
