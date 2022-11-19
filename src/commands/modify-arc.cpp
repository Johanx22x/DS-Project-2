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
    std::cout << "No arcs in the graph to modify!\n";
    return;
  }

  std::cout << "Available arcs:\n";
  std::cout << "-------------------------\n";
  std::cout << "ID\tInfo\n";
  std::cout << "=========================\n";
  for (Arc *arc = ctx->arcs->head; arc; arc = arc->next->next) {
    std::cout << arc->id << "\t" << arc->to->name << " <-> " << arc->next->to->name << "\n";
  }
  std::cout << "-------------------------\n";

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

      if (newSource == arc->to) {
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

      if (newDestination == arc->next->to) {
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
