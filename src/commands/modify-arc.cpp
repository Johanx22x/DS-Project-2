#include <proxy.hh>
#include <graph.hh>
#include <program.hh>
#include <iostream>
#include <string>
#include <uio.hh>

extern "C" {

void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation runned, can't modify the graph, use 'reset' to reset the graph.\n";
        return;
    }
  // Check if exist arcs
  if (!ctx->arcs->size) {
    std::cout << "No arcs in the graph to modify!\n";
    return;
  }

  std::cout << "Available arcs:\n";
  std::cout << "---------------------------------\n";
  std::cout << "ID\tTime\tInfo\n";
  std::cout << "=================================\n";
  for (Arc *arc = ctx->arcs->head; arc; arc = arc->next->next) {
      std::cout << arc->id << "\t" << arc->time << "\t" << arc->next->to->name << " <-> " << arc->to->name << "\n";
  }
  std::cout << "---------------------------------\n";

  std::cout << "Enter arc id: ";
  int idToFind = getInt();

  if (idToFind % 2 != 0) {
    std::cout << "Invalid arc id!\n";
    return;
  }

  Arc *arc = ctx->arcs->find(idToFind);
  if (!arc) {
    std::cout << "Arc not found!\n";
    return;
  }

  std::cout << "Options:\n";
  std::cout << "1 : Change arc distance\n";
  std::cout << "2 : Change arc source node\n";
  std::cout << "3 : Change arc destination node\n";
  std::cout << "4 : Delete arc\n";
  std::cout << "Select option: ";
  int option = getInt();

  switch (option) {
    case 1: {
      std::cout << "Enter new distance: ";
      int newDistance = -1;
      while (newDistance <= 0) {
        newDistance = getInt();
        if (newDistance <= 0) {
          std::cout << "Invalid distance! Try again: ";
        }
      }
      arc->time = newDistance;
      arc->next->time = newDistance;
      std::cout << "Arc distance changed!\n";
      break;
    }
    case 2: { // FIXME: Fix this
      std::cout << "Available nodes:\n";
      std::cout << "-------------------------\n";
      std::cout << "ID\tName\n";
      std::cout << "=========================\n";
      for (Node *node = ctx->nodes->head; node; node = node->next) {
          std::cout << node->id << "\t" << node->name << "\n";
      }
      std::cout << "-------------------------\n";

      std::cout << "Enter new source node id: ";
      int newSrcId = getInt();
      Node *newSrc = ctx->nodes->find(newSrcId);
      if (!newSrc) {
        std::cout << "Node not found!\n";
        return;
      }

      Node *oldSrc = arc->next->to;
      // Remove the arc from the old source node 
      for (Proxy<Arc> *proxy = oldSrc->arcs->head; proxy; proxy = proxy->next) {
        if (proxy->link->id == arc->id) {
          oldSrc->arcs->remove(proxy);
          break;
        }
      }
      newSrc->arcs->add(new Proxy<Arc>(arc));
      arc->next->to = newSrc;

      std::cout << "Arc source changed!\n";
      break;
    }
    case 3: { 
      std::cout << "Available nodes:\n";
      std::cout << "-------------------------\n";
      std::cout << "ID\tName\n";
      std::cout << "=========================\n";
      for (Node *node = ctx->nodes->head; node; node = node->next) {
          std::cout << node->id << "\t" << node->name << "\n";
      }
      std::cout << "-------------------------\n";

      std::cout << "Enter new destination node id: ";
      int newDestId = getInt();
      Node *newDest = ctx->nodes->find(newDestId);
      if (!newDest) {
        std::cout << "Node not found!\n";
        return;
      }

      Node *oldDest = arc->to;
      for (Proxy<Arc> *proxy = oldDest->arcs->head; proxy; proxy = proxy->next) {
        if (proxy->link->id == arc->next->id) {
          oldDest->arcs->remove(proxy);
          break;
        }
      }
      newDest->arcs->add(new Proxy<Arc>(arc->next));
      arc->to = newDest;

      std::cout << "Arc destination changed!\n";
      break;
    }
    case 4: { 
      // Delete the arc from the respective nodes
      for (Node *node = ctx->nodes->head; node; node = node->next) {
        for (Proxy<Arc> *tmpArc = node->arcs->head; arc; arc = arc->next) {
            if (tmpArc->link == arc) {
                node->arcs->remove(tmpArc);
            }
        }
      }

      // Delete the arc from the graph
      Arc *toDelete = ctx->arcs->find(idToFind);
      ctx->arcs->remove(toDelete);
      ctx->arcs->remove(toDelete->next);

      std::cout << "Bidirectional arc deleted!\n";
      break;
    }
    default: {
      std::cout << "Invalid option!\n";
      break;
    }
  }
}

}
