#include <proxy.hh>
#include <graph.hh>
#include <program.hh>
#include <iostream>
#include <string>
#include <uio.hh>

extern "C" {

void command(Program *ctx) {
  // Check if exist a nodes
  if (ctx->nodes->size < 2) {
    std::cout << "You need to create at least two nodes before create an arc.\n";
    return;
  }

  // Show the available nodes in the graph
  std::cout << "Available nodes: \n";
  for (Node *temp = ctx->nodes->head; temp; temp = temp->next) {
      std::cout << temp->id << " : " << temp->name << std::endl;
  }

  std::cout << "Enter the id of the source node: ";
  int src = getInt();

  Node *srcNode = ctx->nodes->find(src);
  if (!srcNode) {
    std::cout << "Node not found\n";
    return;
  }

  std::cout << "Enter the destination node id: ";
  int dest = getInt();

  Node *destination = ctx->nodes->find(dest);
  if (!destination) {
    std::cout << "Node not found\n";
    return;
  }

  if (srcNode == destination) {
    std::cout << "You can't create an arc between the same node.\n";
    return;
  }

  for (Proxy<Arc> *temp = srcNode->arcs->head; temp; temp = temp->next) {
    if (temp->link->to == destination) {
      std::cout << "This arc already exists\n";
      return;
    }
  }

  std::cout << "Enter the distance of the arc (meters): ";
  int time = -1;
  while (time <= 0) {
    time = getInt();
    if (time <= 0) {
      std::cout << "Invalid distance, try again: ";
    }
  }

  Arc *arcFrom = new Arc(time, destination);
  ctx->arcs->add(arcFrom);
  srcNode->arcs->add(new Proxy<Arc>(arcFrom));

  Arc *arcTo = new Arc(time, srcNode);
  ctx->arcs->add(arcTo);
  destination->arcs->add(new Proxy<Arc>(arcTo));

  std::cout << "Bidirectional arc with distance " << time << "m from " << srcNode->name << " to " << destination->name << " created.\n";
}

}
