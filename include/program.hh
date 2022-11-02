#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <command.hh>
#include <graph.hh>
#include <linked_list.hh>
#include <map>

class Program {
public:
  LinkedList<Node> *nodes = nullptr;
  LinkedList<Arc> *arcs = nullptr;
  std::map<std::string, Command *> *commands = nullptr;

  Program();
  ~Program();
  void run();
};

#endif
