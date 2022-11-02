#include <iostream>
#include <string>
#include <npc.hh>

std::string NPC::toString() {
    std::string str = "Person (" + std::to_string(id) + "):  " + name;
    return str;
}
