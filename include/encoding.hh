#ifndef DUMP_HH
#define DUMP_HH

#include <graph.hh>
#include <linked_list.hh>

int encode(LinkedList<Node> *__restrict graph, char *__restrict buffer);
int decode(std::string, LinkedList<Node> *, LinkedList<Arc> *);

#endif // DUMP_HH
