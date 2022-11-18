#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <map>
#include <person.hh>
#include <uio.hh>

class Program {
public:
  LinkedList<Node> *nodes = nullptr;
  LinkedList<Arc> *arcs = nullptr;
  LinkedList<Person> *people = nullptr;
  std::map<std::string, class Command *> *commands =
      new std::map<std::string, class Command *>();

  Program();
  ~Program();

  void run();
};

#endif
