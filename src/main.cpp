#include <command_loader.hh>
#include <cstdio>
#include <cstdlib>
#include <encoding.hh>
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

/* static inline int __main() { */
  /* Node *ciudadQuesada = new Node("Ciudad Quesada"); */
  /* Node *sjo = new Node("San Jose"); */
  /* Node *tigra = new Node("La Tigra"); */

  /* Arc *cqSjo = new Arc(5, sjo); */
  /* Arc *sjoCq = new Arc(5, ciudadQuesada); */
  /* Arc *cqLt = new Arc(30, tigra); */

  /* ciudadQuesada->arcs->add(new Proxy<Arc>(cqLt)); */

  /* sjo->arcs->add(new Proxy<Arc>(sjoCq)); */

  /* ciudadQuesada->arcs->add(new Proxy<Arc>(cqSjo)); */

  /* LinkedList<Node> *graph = new LinkedList<Node>(); */

  /* graph->add(ciudadQuesada); */
  /* graph->add(sjo); */
  /* graph->add(tigra); */

  /* char buf[65000] = {0}; */
  /* int written = encode(graph, buf); */
  /* printf("Written: %d bytes\n", written); */

  /* FILE *ff = fopen("hola.bin", "w"); */
  /* fprintf(ff, "%s", buf); */
  /* puts("writing the buffer once again"); */
  /* fflush(ff); */
  /* fclose(ff); */

  /* LinkedList<Node> *secondGraph = new LinkedList<Node>(); */
  /* LinkedList<Arc> *arcs = new LinkedList<Arc>(); */

  /* ff = fopen("hola.bin", "r"); */
  /* decode("hola.bin", secondGraph, arcs); */

  /* fclose(ff); */

  /* ff = fopen("data.dot", "w"); */
  /* dumpGraph(ff, secondGraph); */

  /* fflush(ff); */
  /* fclose(ff); */

  /* /1* int parsed = parse(buf, graph2); *1/ */
  /* /1* printf("Parsed %d bytes\n", parsed); *1/ */
  /* /1* dumpGraph(ff, graph2); *1/ */
/* } */

int main() {

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
