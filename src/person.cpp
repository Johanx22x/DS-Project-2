#include <cstdio>
#include <iostream>
#include <string>
#include <person.hh>

int Person::next_id = 0;

std::string Person::toString() {
    std::string result = "Person (" + std::to_string(id) + "): " + name;
    return result;
}

bool Person::addFriend(Person *person) {
    // Check if the new friend is already in the list 
    Proxy<Person> *curr = friends;
    while (curr != NULL) {
        if (curr->link == person) {
            return false;
        }
        curr = curr->next;
    }

    // Add the new friend to the list
    if (friends == nullptr) {
        friends = new Proxy<Person>(person);
    } else {
        friends->add(person);
    }

    return true;
}
