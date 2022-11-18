#ifndef GRAPH_HH
#define GRAPH_HH

#include <iostream>
#include <linked_list.hh>
#include <person.hh>
#include <proxy.hh>
#include <queue>
#include <string>

class Node {
  static int next_id;

public:
  bool visited = false;
  int id = next_id++;
  std::string name;
  Node *next = nullptr;
  LinkedList<Proxy<Person>> *people = new LinkedList<Proxy<Person>>();
  LinkedList<Proxy<class Arc>> *arcs = new LinkedList<Proxy<class Arc>>();

  Node(std::string name) : name(name) {}

  void toString();
};

class Arc {
  static int next_id;

public:
  int id = next_id++;
  int time;
  Node *to;

  Arc *next = nullptr;

  Arc(int time, Node *to) : time(time), to(to) {}

  void toString();
};

#endif
