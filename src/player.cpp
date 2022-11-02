#include <cstdio>
#include <iostream>
#include <string>
#include <person.hh>

std::string Person::toString() {
    std::string result = "Person (" + std::to_string(id) + "): " + name;
    return result;
}

void Person::addFriend(Person *newFriend) {
    if (friends == nullptr) {
        friends = new Proxy<Person>(newFriend);
    } else {
        friends->add(newFriend);
    }
}
