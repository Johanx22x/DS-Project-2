#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <graph.hh>
#include <linked_list.hh>
#include <string.h>

#define _64KB 65536

int marshal(LinkedList<Node> *__restrict graph, char *__restrict buf) {
  int written = 0;

  // meaning of bytes here
  // 0xA1: begin graph
  // 0xA2: begin node
  // 0xA3: end node
  // 0xA4: begin weight
  // 0xA5: end weight
  // 0xA6: end graph

  written += sprintf(buf, "\x01");
  printf("debug: writing a total of %d nodes\n", graph->size);
  for (Node *node = graph->head; node != nullptr; node = node->next) {

    for (Proxy<Arc> *arc = node->arcs->head; arc != nullptr; arc = arc->next) {
      written += sprintf(buf + written, "\x02%s\x03\x02%s\x03\x04%d\x05",
                         node->name.c_str(), arc->link->to->name.c_str(),
                         arc->link->time);
    }
  }

  written += sprintf(buf + written, "\x06");
  return written;
}

int parse(char *__restrict text, LinkedList<Node> *graph) {
  int written = 0;
  int idx = 0;

  while (true) {
  }

  return written;
}
