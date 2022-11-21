#include <cstdio>
#include <iostream>
#include <program.hh>
#include <encoding.hh>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
        return;
    }

    if (ctx->nodes->size == 0) {
        std::cout << "No graph to save!\n";
        return;
    }

    // Encode the actual graph
    char* buffer = new char[64000];
    char* buffer2 = new char[64000];
    encodeNodes(ctx->nodes, buffer);
    encodeArcs(ctx->arcs, buffer2);

    std::cout << "Enter the graph name: ";
    std::string dirName;
    getline(std::cin, dirName);

    dirName = "./GRAPHS/" + dirName;

    if (!(access(dirName.c_str(), F_OK) == 0)) {
        if (mkdir(dirName.c_str(), 0777) == -1) {
            std::cout << "Error saving graph!\n";
            return;
        }
    }

    std::string nodesPath = dirName + "/nodes.bin";
    std::string arcsPath = dirName + "/arcs.bin";

    FILE *out = fopen(nodesPath.c_str(), "w");
    fprintf(out, "%s", buffer);
    fflush(out);
    fclose(out);

    out = fopen(arcsPath.c_str(), "w");
    fprintf(out, "%s", buffer2);
    fflush(out);
    fclose(out);

    std::cout << "Graph saved to " << dirName << "!\n";
}
}
