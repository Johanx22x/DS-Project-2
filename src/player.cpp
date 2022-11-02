#include <cstdio>
#include <iostream>
#include <string>
#include <player.hh>

std::string Player::toString() {
    std::string result = "Person (" + std::to_string(id) + "): " + name;
    return result;
}
