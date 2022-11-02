#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>
#include <string>
#include <proxy.hh>

enum MovementType {
    RANDOM,
    ADJACENT,
    THROUGH_ALL,
    DIRECT
};

class Person {
public:
    int id;
    std::string name;
    MovementType mode;
    Proxy<Person> *friends = nullptr;
    Person *next = nullptr;

    int steps = 0;
    class Arc *currentArc = nullptr;
    class Node *from = nullptr;
    class Node *to = nullptr;

    Person(int id, std::string name, Node from, Node to, MovementType mode);
    Person(int id, std::string name, MovementType mode);

    void addFriend(Person *person);

    std::string toString();
};

#endif
