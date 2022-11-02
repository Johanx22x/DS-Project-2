#include <command_loader.hh>
#include <context.hh>
#include <cstdio>
#include <filesystem>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>
#include <map>
#include <uio.hh>

#include <string>

#if defined(_WIN32)
#define DL ".dll"
#else
#define DL ".so"
#endif

using std::string;

int main() {

  /*   /1* Context ctx; *1/ */
  /*   std::map<string, Command *> commands = std::map<string, Command *>(); */

  /*   for (const std::filesystem::directory_entry &entry : */
  /*        std::filesystem::directory_iterator("./")) { */

  /*     string fileName = entry.path(); */

  /*     int position = fileName.find_last_of("."); */

  /*     string ft = fileName.substr(position); */

  /*     printf("%s %s\n", fileName.c_str(), ft.c_str()); */

  /*     if (ft.compare(DL) == 0) { */
  /*       Command *cmd = loadCommand(entry.path()); */
  /*       commands.emplace(entry.path(), cmd); */
  /*     } */
  /*   } */

  LinkedList<Arc> *arcs = new LinkedList<Arc>();

  LinkedList<Node> *l = new LinkedList<Node>();
  Node *niggerdog = new Node("Nigger dog");
  Arc *nd = new Arc(5, niggerdog);

  arcs->add(nd);
  Node *alphacentauri = new Node("Alpha centauri");
  alphacentauri->arcs->add(new Proxy<Arc>(nd));
  Node *cumdog = new Node("Cum dog");
  Node *campanita = new Node("Campanita");
  Node *pingalarga =
      new Node("La saguata de matey que me dejó el brazo hecho picha");

  l->add(niggerdog);
  l->add(alphacentauri);
  l->add(cumdog);
  l->add(campanita);
  l->add(pingalarga);

  FILE *lmao = fopen("pinga.dot", "w");
  int written = dumpGraph(lmao, l);
  printf("%d\n", written);
  return 0;
}
