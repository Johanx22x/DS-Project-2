#include "linked_list.hh"
#include "proxy.hh"
#include <cstdio>
#include <encoding.hh>
#include <algorithm>
#include <person.hh>
#include <program.hh>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

void saveActualGraph(Program *ctx) {
  // Encode the actual graph
  char *buffer = new char[64000];
  encodeNodes(ctx->nodes, buffer);

  char *buffer2 = new char[64000];
  encodeArcs(ctx->arcs, buffer2);

  char *buffer3 = new char[64000];
  encodePeople(ctx->people, buffer3);

  std::string dirName = ".PS";
  dirName = "./GRAPHS/" + dirName;

  if (!(access(dirName.c_str(), F_OK) == 0)) {
    if (mkdir(dirName.c_str(), 0777) == -1) {
      std::cout << "Error saving graph!\n";
      return;
    }
  }

  std::string nodesPath = dirName + "/nodes.bin";
  FILE *out = fopen(nodesPath.c_str(), "w");
  fprintf(out, "%s", buffer);
  fflush(out);
  fclose(out);

  std::string arcsPath = dirName + "/arcs.bin";
  out = fopen(arcsPath.c_str(), "w");
  fprintf(out, "%s", buffer2);
  fflush(out);
  fclose(out);

  std::string peoplePath = dirName + "/people.bin";
  out = fopen(peoplePath.c_str(), "w");
  fprintf(out, "%s", buffer3);
  fflush(out);
  fclose(out);
}

#define INF 1000

void shortestPathThroughAll(Person *player, LinkedList<Node> *graph) {
  int matrix[graph->size][graph->size];
  for (int i = 0; i < graph->size; i++)
    for (int j = 0; j < graph->size; j++)
      if (i == j)
        matrix[i][j] = 0;
      else
        matrix[i][j] = INF;

  for (Node *node = graph->head; node != nullptr; node = node->next) {
    for (Proxy<Arc> *arc = node->arcs->head; arc != nullptr; arc = arc->next) {
      matrix[node->id][arc->link->to->id] = arc->link->time;
    }
  }

  for (int k = 0; k < graph->size; k++) {
    for (int i = 0; i < graph->size; i++) {
      for (int j = 0; j < graph->size; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
          matrix[i][j] = matrix[i][k] + matrix[k][j];
        }
      }
    }
  }

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

  for (int i = 0; i < graph->size; i++) {
    Node *next = graph->find(matrix[i][i + 1]);
    player->path.push(next);
  }
}

extern "C" {

void command(Program *ctx) {
    if (ctx->simulationDone) {
        std::cout << "Simulation already done!\n";
        std::cout << "Use 'reset' to reset the simulation.\n";
        return;
    }
  size_t totalMinutes = 0;
  Person *firstToFinish = nullptr;
  Person *lastToFinish = nullptr;

  bool valid = false;
  // Remove the first node in the person path (for Direct and Through all),
  // because it is the starting point We don't need to simulate the person going
  // to the starting point
  for (Person *person = ctx->people->head; person; person = person->next) {
      person->inSimulation = true;
      person->currentArc = nullptr;
      if (person->mode == MovementType::THROUGH_ALL) {
          person->inSimulation = false; // NOTE: We don't simulate this person
      }
      if (person->from == nullptr) {
          person->from = ctx->nodes->head;
          continue;
      }
      person->shortestPath(person->from, person->to);
      person->path.pop();
      valid = true;
  }
  if (!valid) {
    std::cout << "Cannot simulate, create a person with a movement type 'direct' or 'through all' first!\n";
    return;
  }


    for (Person *person = ctx->people->head; person != nullptr; person = person->next) {
        for (Person *_friend = ctx->people->head; _friend != nullptr; _friend = _friend->next) {
            if (person->id == _friend->id) {
                continue;
            }
            if (person->from->id == _friend->from->id) {
                  std::vector<Person*>::iterator it = find(person->friends->begin(), person->friends->end(), _friend);
                  if (it == person->friends->end()) {
                      person->friends->push_back(_friend);
                      printf("%s is now friends with %s!\n", person->name.c_str(), _friend->name.c_str());
                  }
            }
        }
    }

    // Save the actual GRAPH
    saveActualGraph(ctx);

    for (Person *person = ctx->people->head; person != nullptr; person = person->next){
      person->hasPath = true;
    }

  while (true) {
    bool allFinished = true;
    std::cout << "\u001b[34mTotal minutes: " << totalMinutes << "\u001b[0m\n";

    for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
      // If the person is not in simulation, skip it
      if (tmp->inSimulation == false) {
        continue;
      }

      // Check if exist a person with the movement type 'through all' or 'direct'
      if (tmp->mode == MovementType::DIRECT || tmp->mode == MovementType::THROUGH_ALL) {
          if (tmp->inSimulation) {
              allFinished = false;
          }
      }

      // Check if the person is in a node
      if (tmp->currentArc == nullptr) {
        Arc *next = tmp->nextArc();

        if (tmp->mode == MovementType::DIRECT || tmp->mode == MovementType::THROUGH_ALL) {
          if (next == nullptr) {
            if (!firstToFinish) firstToFinish = tmp;
            lastToFinish = tmp;
            tmp->inSimulation = false;
            tmp->inNode = false;
            continue;
          }
        } else {
          if (next == nullptr) {
            tmp->hasPath = false;
            tmp->inNode = false;
            tmp->inSimulation = false;
            continue;
          }
        }

        tmp->currentArc = next;
        tmp->to = next->to;
        if (tmp->inNode) {
          std::cout << tmp->name << " leaves " << tmp->from->name << "\n";
          tmp->from->people.pop();
          tmp->inNode = false;
        }
        tmp->steps++;
      } else if (tmp->steps >= tmp->currentArc->time) {
          tmp->steps = 0;
          tmp->from = tmp->to;
          tmp->currentArc = nullptr;
          tmp->inNode = true;

          std::cout << tmp->name << " is in " << tmp->from->name << "\n";
      } else {
        tmp->steps++;
      }

      // Check if the person is walking through an arc
      if (tmp->currentArc != nullptr) {
          if (tmp->mode == MovementType::DIRECT || tmp->mode == MovementType::THROUGH_ALL) {
              std::cout << tmp->name << " is going to " << tmp->to->name << "\n";
          }
      }
    }

    // make the friends
    for (Person *person = ctx->people->head; person != nullptr; person = person->next) {
        for (Person *_friend = ctx->people->head; _friend != nullptr; _friend = _friend->next) {
            if (person->id == _friend->id) {
                continue;
            }
            if (person->from->id == _friend->from->id) {
                if (person->inNode && _friend->inNode) {

                  std::vector<Person*>::iterator it = find(person->friends->begin(), person->friends->end(), _friend);
                  if (it == person->friends->end()) {
                      person->friends->push_back(_friend);
                      printf("%s is now friends with %s!\n", person->name.c_str(), _friend->name.c_str());
                  }

                }
            }
        }
    }

    totalMinutes++;
    std::cout << "\n";

    if (allFinished)
      break;
  }

  printf("Simulation finished after %zu minutes\n\n", totalMinutes);

  printf("Consults:\n");
  printf("The first person to finish was: %s\n", firstToFinish->name.c_str());
  printf("The last person to finish was: %s\n", lastToFinish->name.c_str());

  Person *mostFriends = ctx->people->head;
  for (Person *tmp = ctx->people->head; tmp != nullptr; tmp = tmp->next) {
    if (tmp->friends->size() >= mostFriends->friends->size()) {
      mostFriends = tmp;
    }
  }
  printf("%s has the most friends, they have %zu friends!\n", mostFriends->name.c_str(), mostFriends->friends->size());

  ctx->simulationDone = true;
}
}
