#ifndef DUMP_HH
#define DUMP_HH

#include <graph.hh>
#include <linked_list.hh>

/* int encode(LinkedList<Node> *__restrict graph, char *__restrict buffer); */
int encodeNodes(LinkedList<Node> *__restrict nodes, char *__restrict buffer);
int encodeArcs(LinkedList<Arc> *__restrict arcs, char *__restrict buffer);
void decodeNodes(std::string filename, LinkedList<Node> *__restrict nodes);
void decodeArcs(std::string filename, LinkedList<Arc> *__restrict arcs, LinkedList<Node> *__restrict nodes);
/* int decode(std::string, LinkedList<Node> *, LinkedList<Arc> *); */

#endif // DUMP_HH
