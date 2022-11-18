#include <proxy.hh>
#include <graph.hh>
#include <program.hh>
#include <iostream>
#include <string>

extern "C" {

void command(Program *ctx) {
  // Check if exist a nodes
  if (ctx->nodes->head == nullptr) {
    std::cout << "No nodes in graph, please create some before creating arcs.\n";
    return;
  }

  // Show the available nodes in the graph
  std::cout << "Available nodes: \n";
  for (Node *temp = ctx->nodes->head; temp; temp = temp->next) {
      std::cout << temp->id << " : " << temp->name << std::endl;
  }

  std::cout << "Enter the id of the source node: ";
  int src;
  std::cin >> src;

  Node *srcNode = ctx->nodes->find(src);
  if (!srcNode) {
    std::cout << "Node not found\n";
    return;
  }

  std::cout << "Enter the destination node id: ";
  int dest;
  std::cin >> dest;

  Node *destination = ctx->nodes->find(dest);
  if (!destination) {
    std::cout << "Node not found\n";
    return;
  }

  std::cout << "Enter the distance of the arc (meters): ";
  int time = -1;
  while (time < 0) {
    std::cin >> time;
    if (time < 0) {
      std::cout << "Invalid distance, try again: ";
    }
  }

  Arc *arc = new Arc(time, destination);
  ctx->arcs->add(arc);
  srcNode->arcs->add(new Proxy<Arc>(arc));

  std::cout << "Arc with distance " << time << "m, from " << srcNode->name << " to " << destination->name << " created.\n";
}

}
