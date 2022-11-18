#include <command_loader.hh>
#include <cstdio>
#include <dump.hh>
#include <filesystem>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>
#include <map>
#include <program.hh>
#include <string>
#include <uio.hh>

#if defined(_WIN32)
#define DL ".dll"
#else
#define DL ".so"
#endif

using std::string;

int main() {
  Node *ciudadQuesada = new Node("Ciudad Quesada");
  Node *sjo = new Node("San José");

  Arc *cqSjo = new Arc(5, sjo);
  Arc *sjoCq = new Arc(5, ciudadQuesada);
  sjo->arcs->add(new Proxy<Arc>(sjoCq));
  ciudadQuesada->arcs->add(new Proxy<Arc>(cqSjo));
  LinkedList<Node> *graph = new LinkedList<Node>();
  graph->add(ciudadQuesada);
  graph->add(sjo);

  char buf[65000] = {0};
  int written = marshal(graph, buf);
  printf("Written: %d bytes\n", written);
  int cur = 0;
  while (written--) {
    putchar(buf[cur++]);
  }
  puts("");

  LinkedList<Node> *graph2 = new LinkedList<Node>();

  int parsed = parse(buf, graph2);
  printf("Parsed %d bytes\n", parsed);
  FILE *ff = fopen("data.dot", "w");
  dumpGraph(ff, graph2);
}

int omain() {

  Program *p = new Program();
  /* std::map<string, Command *> commands = std::map<string, Command *>(); */

  for (const std::filesystem::directory_entry &entry :
       std::filesystem::directory_iterator("./bin")) {

    string fileName = entry.path();

    int position = fileName.find_last_of(".");

    string ft = fileName.substr(position);

    if (ft.compare(DL) == 0) {

      fileName = fileName.erase(position);
      position = fileName.find_last_of("/");
      string cmdName = fileName.substr(position + 1);

      printf("loading: %s %s\n", fileName.c_str(), ft.c_str());
      Command *cmd = loadCommand(entry.path());
      printf("loaded: %s %s\n", fileName.c_str(), ft.c_str());
      p->commands->emplace(cmdName, cmd);
    }
  }

  p->run();

  return 0;
}
