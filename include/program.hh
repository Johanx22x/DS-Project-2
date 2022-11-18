#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <map>
#include <person.hh>
#include <uio.hh>

class Program {
public:
  LinkedList<Node> *nodes = new LinkedList<Node>();
  LinkedList<Arc> *arcs = new LinkedList<Arc>();
  LinkedList<Person> *people = new LinkedList<Person>();
  std::map<std::string, class Command *> *commands =
      new std::map<std::string, class Command *>();

  Program();
  ~Program();

  void run();
};

#endif
