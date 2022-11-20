#include <cstdio>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>

struct conn {
    Node *from;
    Node *to;
};

int eputs(std::string);

#if defined(_WIN32)
#include <Windows.h>

void compileGraph(const *char name) {
  STARTUPINFO si = {0};
  PROCESS_INFORMATION pi;
  si.cb = sizeof(si);
  if (!CreateProcess(TEXT("dot.exe"), name, NULL, NULL, FALSE, 0, 0, 0, &si,
                     &pi)) {
    eputs("error spawning dot process\n");
    _Exit(1);
  }

  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);
}

#else

#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// This function compiles the graph into a png file
// using the dot program.
void compileGraph(char *const name) {
  pid_t pid = fork();
  if (pid == 0) {
    execlp("dot", "dot", "graph.dot", "-Tpng", "-o", name, NULL);
    eputs("error spawning dot process\n");
    return;
  } else if (pid < 0) {
    eputs("error forking\n");
    return;
  }

  int status;
  waitpid(pid, &status, 0);
  if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
    eputs("error compiling graph with dot\n");
    return;
  }
}

#endif

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

  LinkedList<Proxy<conn>> *conns = new LinkedList<Proxy<conn>>();
  while (tmp != nullptr) {

    if (tmp->arcs->head == nullptr) {
      tmp = tmp->next;
      continue;
    }

    for (Proxy<Arc> *arcs = tmp->arcs->head; arcs != nullptr; arcs = arcs->next) {
      bool found = false;
      for (Proxy<conn> *c = conns->head; c != nullptr; c = c->next) {
        if (c->link->from == arcs->link->to && c->link->to == tmp) {
            found = true;
            break;
        }
      }
      if (!found) {
          written +=
              fprintf(fp, "\t\"%s\" -- \"%s\" [label=%d]\n", tmp->name.c_str(),
                      arcs->link->to->name.c_str(), arcs->link->time);
          conns->add(new Proxy<conn>{new conn{tmp, arcs->link->to}});
      }
    }

    tmp = tmp->next;
  }

  written += fputs("}", fp);

  fflush(fp);

  return written;
}

int getRandomInt(int min, int max) {
  return (rand() % (max - min + 1)) + min;
}
