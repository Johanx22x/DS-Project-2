#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <person.hh>
#include <uio.hh>
#include <map>

class Program {
public:
  LinkedList<Node> *nodes = nullptr;
  LinkedList<Arc> *arcs = nullptr;
  LinkedList<Person> *people = nullptr;
  std::map<std::string, class Command *> *commands = nullptr;

  Program();
  ~Program();
  void run();
};

#endif
