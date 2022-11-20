#include <cstdio>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>

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

void compileGraph(char *const name) {
  pid_t pid;
  int status;
  pid_t ret;

  char *const args[6] = {name, "-Tpng", "-o", "out.png", NULL};
  char **env;
  extern char **environ;

  pid = fork();
  if (pid == -1) {
    eputs("error forking main process\n");
    exit(-1);
  } else if (pid != 0) {
    while ((ret = waitpid(pid, &status, 0)) == -1) {
      if (errno != EINTR) {
        break;
      }
    }
    if ((ret == 0) || !(WIFEXITED(status) && !WEXITSTATUS(status))) {
      eputs("unexpected child status\n");
      exit(-2);
    }
  } else {
    if (execve("dot", args, env) == -1) {
      eputs("unexpected return status\n");
      exit(-3);
    }
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

  while (tmp != nullptr) {

    if (tmp->arcs->head == nullptr) {
      tmp = tmp->next;
      continue;
    }

    for (Proxy<Arc> *arcs = tmp->arcs->head; arcs != nullptr;
         arcs = arcs->next) {
      written +=
          fprintf(fp, "\t\"%s\" -- \"%s\" [label=%d]\n", tmp->name.c_str(),
                  arcs->link->to->name.c_str(), arcs->link->time);
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
