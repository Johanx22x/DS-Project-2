#include <proxy.hh>
#include <graph.hh>
#include <program.hh>
#include <iostream>
#include <string>
#include <uio.hh>

extern "C" {

void command(Program *ctx) {
  // Check if exist arcs
  if (!ctx->arcs->size) {
    std::cout << "No nodes in the graph" << std::endl;
    return;
  }

  std::cout << "Available arcs:\n";
  for (Arc *arc = ctx->arcs->head; arc; arc = arc->next->next) {
    std::cout << arc->id << " : " << arc->to->id << " <-> " << arc->next->to->id << "\n";
  }

  std::cout << "Enter arc id: ";
  int idToFind = getInt();

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
      int newDistance = getInt();
      arc->time = newDistance;
      arc->next->time = newDistance;
      break;
    }
    case 2: { // FIXME: Fix this
      std::cout << "Enter new source node id: ";
      int newSourceId = getInt();
      Node *newSource = ctx->nodes->find(newSourceId);
      if (!newSource) {
        std::cout << "Node not found!\n";
        return;
      }

      if (newSource == arc->next->to) {
        std::cout << "Source and destination cannot be the same!\n";
        return;
      }

      for (Node *node = ctx->nodes->head; node; node = node->next) {
        for (Proxy<Arc> *tmpArc = node->arcs->head; arc; arc = arc->next) {
            if (tmpArc->link == arc) {
                node->arcs->remove(tmpArc);
            }
        }
      }
      arc->next->to = newSource;
      newSource->arcs->add(new Proxy(arc->next));
      break;
    }
    case 3: { // FIXME: Fix this case
      std::cout << "Enter new destination node id: ";
      int newDestinationId = getInt();
      Node *newDestination = ctx->nodes->find(newDestinationId);
      if (!newDestination) {
        std::cout << "Node not found!\n";
        return;
      }

      if (newDestination == arc->to) {
        std::cout << "Source and destination cannot be the same!\n";
        return;
      }

      for (Node *node = ctx->nodes->head; node; node = node->next) {
        for (Proxy<Arc> *tmpArc = node->arcs->head; arc; arc = arc->next) {
            if (tmpArc->link == arc->next) {
                node->arcs->remove(tmpArc);
            }
        }
      }

      arc->to = newDestination;
      newDestination->arcs->add(new Proxy(arc->next));
      break;
    }
    case 4: { // FIXME: Fix the remove function
      for (Node *node = ctx->nodes->head; node; node = node->next) {
        for (Proxy<Arc> *tmpArc = node->arcs->head; arc; arc = arc->next) {
            if (tmpArc->link == arc) {
                node->arcs->remove(tmpArc);
            }
            if (tmpArc->link == arc->next) {
                node->arcs->remove(tmpArc);
            }
        }
      }
      ctx->arcs->remove(arc);
      ctx->arcs->remove(arc->next);
      break;
    }
    default: {
      std::cout << "Invalid option!\n";
      break;
    }
  }
}

}
