#include "encoding.hh"
#include "person.hh"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>
#include <sstream>
#include <stdio.h>
#include <string>
#include <uio.hh>

#define _64KB 65536

using std::string;

/* int encode(LinkedList<Node> *__restrict graph, char *__restrict buf) { */
/*   int written = 0; */

/*   // meaning of bytes: */
/*   // 0xf4: separator */
/*   // 0xc3: end of node */
/*   printf("debug: writing a total of %d nodes\n", graph->size); */
/*   for (Node *node = graph->head; node != nullptr; node = node->next) { */

/*     for (Proxy<Arc> *arc = node->arcs->head; arc != nullptr; arc = arc->next)
 * { */
/*       written += sprintf(buf + written, "%d\xf4%d\xf4%s\xf4%d\xf4%s\xc3", */
/*                          arc->link->id, node->id, node->name.c_str(), */
/*                          arc->link->to->id, arc->link->to->name.c_str()); */
/*     } */
/*   } */

/*   return written; */
/* } */

int encodeNodes(LinkedList<Node> *__restrict nodes, char *__restrict buf) {
  int written = 0;

  // meaning of bytes:
  // 0xf4: separator
  for (Node *node = nodes->head; node != nullptr; node = node->next) {
    written += sprintf(buf + written, "%s\xf4", node->name.c_str());
  }

  return written;
}

int encodeArcs(LinkedList<Arc> *__restrict arcs, char *__restrict buf) {
  int written = 0;

  // meaning of bytes:
  // 0xf4: separator
  // 0xc3: end of arc
  for (Arc *arc = arcs->head; arc != nullptr; arc = arc->next->next) {
    written +=
        sprintf(buf + written, "%d\xf4%d\xc3", arc->next->to->id, arc->to->id);
  }

  return written;
}

int encodePeople(LinkedList<Person> *__restrict people, char *__restrict buf) {
  int written = 0;

  for (Person *person = people->head; person != nullptr;
       person = person->next) {
    written +=
        sprintf(buf + written, "%s\xf4%d\xf4%d\xf4%d\xc3", person->name.c_str(),
                person->from->id, person->to->id, person->mode);
  }

  return written;
}

void decodePeople(string filename, LinkedList<Person> *people,
                  LinkedList<Node> *graph) {
  std::ifstream file = std::ifstream(filename);
  string raw_data((std::istreambuf_iterator<char>(file)),
                  (std::istreambuf_iterator<char>()));
  std::istringstream content(raw_data);

  string people_str;
  while (std::getline(content, people_str, (char)0xc3)) {
    std::istringstream person_str(people_str);
    string name;
    std::getline(person_str, name, (char)0xf4);
    int from, to, movement_type;
    person_str >> from;
    person_str.ignore(1, (char)0xf4);
    person_str >> to;
    person_str.ignore(1, (char)0xf4);
    person_str >> movement_type;

    people->add(new Person(name, graph->find(from), graph->find(to),
                           static_cast<MovementType>(movement_type)));
  }
}

void decodeNodes(string filename, LinkedList<Node> *nodes) {
  std::ifstream file = std::ifstream(filename);
  string raw_data((std::istreambuf_iterator<char>(file)),
                  (std::istreambuf_iterator<char>()));
  std::istringstream content(raw_data);
  string nodes_str;
  // first load all nodes into the graph
  while (std::getline(content, nodes_str, (char)0xf4)) {
    nodes->add(new Node(nodes_str));
  }
}

void decodeArcs(string filename, LinkedList<Arc> *arcs,
                LinkedList<Node> *nodes) {
  std::ifstream file = std::ifstream(filename);
  string raw_data((std::istreambuf_iterator<char>(file)),
                  (std::istreambuf_iterator<char>()));
  std::istringstream content(raw_data);
  string arcs_str;
  while (std::getline(content, arcs_str, (char)0xc3)) {
    std::istringstream arc_str(arcs_str);
    int from, to;
    arc_str >> from;
    arc_str.ignore(1, (char)0xf4);
    arc_str >> to;

    int time = getRandomInt();

    Node *toNode = nodes->find(to);
    Arc *arcTo = new Arc(time, nodes->find(to));

    Node *fromNode = nodes->find(from);
    Arc *arcFrom = new Arc(time, nodes->find(from));

    fromNode->arcs->add(new Proxy<Arc>(arcTo));
    toNode->arcs->add(new Proxy<Arc>(arcFrom));

    arcs->add(arcTo);
    arcs->add(arcFrom);
  }
}

/* void decode(string filename, LinkedList<Node> *nodes, LinkedList<Arc> *arcs)
 * { */
/*   std::ifstream file = std::ifstream(filename); */
/*   string raw_data((std::istreambuf_iterator<char>(file)), */
/*                   (std::istreambuf_iterator<char>())); */
/*   std::istringstream content(raw_data); */
/*   string nodes; */
/*   // first load all nodes into the graph */
/*   while (std::getline(content, nodes, (char)0xc3)) { */
/*     std::istringstream node(nodes); */
/*     Node *nn = new Node(); */
/*     string arcid; */
/*     std::getline(node, arcid, (char)0xf4); */

/*     string id; */
/*     std::getline(node, id, (char)0xf4); */
/*     std::istringstream(id) >> nn->id; */

/*     std::getline(node, nn->name, (char)0xf4); */

/*     if (graph->find(nn->id) == nullptr) { // this means the node already
 * exists */
/*       graph->add(nn); */
/*     } else */
/*       delete nn; */

/*     Node *nn2 = new Node(); */

/*     string id2; */
/*     std::getline(node, id2, (char)0xf4); */
/*     std::istringstream(id2) >> nn2->id; */

/*     std::getline(node, nn2->name, (char)0xf4); */

/*     if (graph->find(nn2->id) == nullptr) { */
/*       graph->add(nn2); */
/*     } else */
/*       delete nn2; */
/*   } */

/*   content = std::istringstream(raw_data); */

/*   while (std::getline(content, nodes, (char)0xc3)) { */

/*     std::istringstream arc(nodes); */
/*     string _arcid; */
/*     std::getline(arc, _arcid, (char)0xf4); */
/*     int arcId; */
/*     std::istringstream(_arcid) >> arcId; */

/*     if (arcs->find(arcId) != nullptr) { */
/*       continue; // this means this arc already exists */
/*     } */

/*     string _id1; */
/*     string name1; */

/*     string _id2; */
/*     string name2; */

/*     std::getline(arc, _id1, (char)0xf4); */
/*     std::getline(arc, name1, (char)0xf4); */

/*     std::getline(arc, _id2, (char)0xf4); */
/*     std::getline(arc, name2, (char)0xf4); */

/*     int id1; */
/*     std::istringstream(_id1) >> id1; */
/*     int id2; */
/*     std::istringstream(_id2) >> id2; */

/*     Node *from = graph->find(id1); */
/*     Node *to = graph->find(id2); */

/*     int arcTime = getRandomInt(5, 60); */

/*     Arc *tarc = new Arc(arcTime, to); */
/*     tarc->id = arcId; */
/*     arcs->add(tarc); */
/*     from->arcs->add(new Proxy<Arc>(tarc)); */

/*     for (Proxy<Arc> *arc = from->arcs->head; arc != nullptr; arc = arc->next)
 * { */
/*         if (arc->link->to->id == to->id) { */
/*             arc->link->time = arcTime; */
/*         } */
/*     } */
/*   } */
/*   // create the arcs */
/* } */
