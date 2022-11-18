#ifndef UIO_HH
#define UIO_HH

#include <cstdio>
#include <linked_list.hh>
#include <graph.hh>
#include <string>

// TODO: add docs
int getInt();

// TODO: add docs
int getRandomInt(int min, int max);

// TODO: add docs
int eputs(std::string);

// TODO: add docs
int dumpGraph(FILE *, LinkedList<Node> *);

// TODO: add docs
void compileGraph(char *const);
#endif // UIO_HH
