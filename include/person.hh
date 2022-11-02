#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>
#include <proxy.hh>

enum MovementType {
    RANDOM = 1,
    ADJACENT,
    THROUGH_ALL,
    DIRECT
};

class Person {
    static int next_id;
public:
    int id = next_id++;
    std::string name;
    MovementType mode;
    Proxy<Person> *friends = nullptr;
    Person *next = nullptr;

    int steps = 0;
    class Arc *currentArc = nullptr;
    class Node *from = nullptr;
    class Node *to = nullptr;

    Person(std::string name, Node from, Node to, MovementType mode);
    Person(std::string name, MovementType mode);

    bool addFriend(Person *person);

    std::string toString();
};

#endif
