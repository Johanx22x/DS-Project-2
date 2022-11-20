#include "person.hh"
#include <cstdio>
#include <program.hh>

#define INF 51

void shortestPathThroughAll(Person *player, LinkedList<Node> *graph) {
  int matrix[graph->size][graph->size];
  puts("begin floyd nigger shit");
  printf("graph = %d\n", graph->size);

  puts("must be here then");
  for (int i = 0; i < graph->size; i++)
    for (int j = 0; j < graph->size; j++)
      if (i == j)
        matrix[i][j] = 0;
      else
        matrix[i][j] = INF;

  puts("not here as well");
  for (Node *node = graph->head; node != nullptr; node = node->next) {
    for (Proxy<Arc> *arc = node->arcs->head; arc != nullptr; arc = arc->next) {
      matrix[node->id][arc->link->to->id] = arc->link->time;
      printf("Adding: Node(%d, %s) <-%d-> Node(%d, %s)\n", node->id,
             node->name.c_str(), arc->link->time, arc->link->to->id,
             arc->link->to->name.c_str());
    }
  }


  puts("not here");
  for (int k = 0; k < graph->size; k++) {
    for (int i = 0; i < graph->size; i++) {
      for (int j = 0; j < graph->size; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
          matrix[i][j] = matrix[i][k] + matrix[k][j];
        }
      }
    }
  }

  puts("begin printing matrix");
  for (int i = 0; i < graph->size; i++) {
    for (int j = 0; j < graph->size; j++) {
      int dist = matrix[i][j];
      if (dist < INF) {
        printf("\t%d", dist);
      } else
        printf("\tINF");
    }
    puts("\n");
  }

  puts("begin pushing nodes");

  for (int i = 0; i < graph->size; i++) {
    Node *next = graph->find(matrix[i][i + 1]);
    player->path.push(next);
  }
}
extern "C" {
void command(Program *ctx) {
  puts("nigger dog");
  for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
    puts("yui");
    if (tmp->mode == MovementType::THROUGH_ALL) {
      puts("vrallan mallers");
      shortestPathThroughAll(tmp, ctx->nodes);
      break;
    }
  }

  puts("yue");
}
}
