#include <linked_list.hh>
#include <cstdio>
#include <iostream>
#include <program.hh>
#include <encoding.hh>
#include <dirent.h>
#include <sys/types.h>

extern "C" {
void command(Program *ctx) {
    if (!ctx->recently_charged) {
        std::cout << "You must run the 'simulate' command before running the 'reset' command.\n";
        return;
    }

    std::string graph_name = ".PS";

    std::string graph_path = "./GRAPHS/" + graph_name;
    std::string nodes_path = graph_path + "/nodes.bin";
    std::string arcs_path = graph_path + "/arcs.bin";
    std::string people_path = graph_path + "/people.bin";

    ctx->nodes = new LinkedList<Node>();
    ctx->arcs = new LinkedList<Arc>();
    ctx->people = new LinkedList<Person>();

    Node::next_id = 0;
    Arc::next_id = 0;
    Person::next_id = 0;

    std::cout << "Resetting the graph...\n";

    decodeNodes(nodes_path, ctx->nodes);
    decodeArcs(arcs_path, ctx->arcs, ctx->nodes);
    decodePeople(people_path, ctx->people, ctx->nodes);

    std::cout << "Graph reset.\n";

    std::cout << "Loaded " << ctx->nodes->size << " nodes\n";
    std::cout << "Loaded " << ctx->arcs->size/2 << " arcs\n";
    std::cout << "Loaded " << ctx->people->size << " people\n";

    ctx->recently_charged = true;
    ctx->reset = true;
    ctx->simulationDone = false;
    std::cout << "Graph reset successfully.\n";
}
}
