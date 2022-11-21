#include <linked_list.hh>
#include <cstdio>
#include <iostream>
#include <program.hh>
#include <encoding.hh>
#include <dirent.h>
#include <sys/types.h>

void list_dir(const char *path) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   
   if (dir == NULL) {
      return;
   }

   std::string actual_dir = ".";
   std::string parent_dir = "..";
   std::string restricted_dir = ".PS";

   std::cout << "-----------------------\n";
   std::cout << "Available Graphs\n";
   std::cout << "=======================\n";
   while ((entry = readdir(dir)) != NULL) {
       if (entry->d_name == actual_dir || entry->d_name == parent_dir || entry->d_name == restricted_dir) {
           continue;
       }
       std::cout << entry->d_name << "\n";
   }
   std::cout << "-----------------------\n";
   closedir(dir);
}

extern "C" {
void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
        return;
    }

    std::cout << "If you load a graph, you will lose all unsaved changes. Are you sure you want to continue? (y/N): ";
    char c;
    std::cin >> c;
    if (!(c == 'y' || c == 'Y')) {
        return;
    }

    while (getchar() != '\n');

    ctx->nodes = new LinkedList<Node>();
    ctx->arcs = new LinkedList<Arc>();

    Node::next_id = 0;
    Arc::next_id = 0;

    list_dir("./GRAPHS");

    std::cout << "Enter graph name: ";
    std::string graph_name;
    getline(std::cin, graph_name);

    std::string graph_path = "./GRAPHS/" + graph_name;
    std::string nodes_path = graph_path + "/nodes.bin";
    std::string arcs_path = graph_path + "/arcs.bin";

    decodeNodes(nodes_path, ctx->nodes);
    decodeArcs(arcs_path, ctx->arcs, ctx->nodes);

    if (ctx->nodes->size == 0) {
        std::cout << "Graph not found.\n";
        return;
    }

    std::cout << "Loaded " << ctx->nodes->size << " nodes" << std::endl;
    std::cout << "Loaded " << ctx->arcs->size/2 << " arcs" << std::endl;

    ctx->recently_charged = true;
    std::cout << "Graph loaded successfully!" << std::endl;
}
}
