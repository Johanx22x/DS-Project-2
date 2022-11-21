#ifndef DUMP_HH
#define DUMP_HH

#include <graph.hh>
#include <linked_list.hh>

/**
 * Encodes the graph into a byte buffer
 *
 * @param nodes The graph
 * @param buf Output buffer
 * @return The number of bytes written
 */
int encodeNodes(LinkedList<Node> *__restrict nodes, char *__restrict buffer);

/**
 * Encodes a list of arcs into a byte buffer
 *
 * @param arcs The arcs list
 * @param buffer Output buffer
 * @return The number of bytes written
 */
int encodeArcs(LinkedList<Arc> *__restrict arcs, char *__restrict buffer);

/**
 * Encodes a list of people into a byte buffer
 *
 * @param people The people list
 * @param buf Output buffer
 * @return The number of bytes written
 */
int encodePeople(LinkedList<Person> *__restrict people, char *__restrict buf);

/**
 * Decodes a file containing a valid people list
 *
 * @param filename The name of the file
 * @param people The output list of people
 * @param graph The graph where to find each person's nodes
 */
void decodePeople(std::string filename, LinkedList<Person> *people, LinkedList<Node> *graph);

/**
 * Decodes a file containing a valid node list
 *
 * @param filename The name of the file
 * @param nodes The output list of nodes
 */
void decodeNodes(std::string filename, LinkedList<Node> *__restrict nodes);

/**
 * Decodes a file containing a valid arcs list
 *
 * @param filename The name of the file
 * @param arcs The output list of arcs
 * @param nodes The list of nodes where the function will try to find the arc's destination node
 */
void decodeArcs(std::string filename, LinkedList<Arc> *__restrict arcs, LinkedList<Node> *__restrict nodes);

#endif // DUMP_HH
