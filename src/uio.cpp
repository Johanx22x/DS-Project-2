#include <cstdio>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>

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

int dumpGraph(FILE *fp, LinkedList<Node> *nodes) {
  if (nodes == nullptr)
    return 0;

  Node *tmp = nodes->head;

  int written = 0;

  written += fputs("graph A {\n", fp);

  while (tmp != nullptr) {

    if (tmp->arcs == nullptr) {
      tmp = tmp->next;
      continue;
    }

    Proxy<Arc> *arcs = tmp->arcs->head;
    while (arcs != nullptr) {
      written +=
          fprintf(fp, "\t\"%s\" -- \"%s\" [label=%d]\n", tmp->name.c_str(),
                  arcs->link->to->name.c_str(), arcs->link->time);
      arcs = arcs->next;
    }

    tmp = tmp->next;
  }

  written += fputs("}", fp);

  fflush(fp);

  return written;
}
