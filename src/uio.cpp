#include <cstdio>
#include <graph.hh>
#include <iostream>
#include <link_list.hh>

int getInt() {

  int out = 0;
  std::cin >> out;

  while (getchar() != '\n')
    ;

  return out;
}

#define _1KB 1024

int eputs(std::string __text) {
  char buf[_1KB];

  sprintf(buf, "\u001b[31m%s\u001b[0m", __text.c_str());
  return fputs(buf, stderr);
}

void dumpGraph(LinkedList<Node*> *nodes);
