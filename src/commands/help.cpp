#include <cstdio>
#include <iostream>
#include <program.hh>

extern "C" {
void command(Program *) { 
    std::cout << "Program commands: \n";
    std::cout << "\thelp                Display this message.\n";
    std::cout << "\texit                Exit the program.\n";
    std::cout << "\n";
    std::cout << "Graph commands: \n";
    std::cout << "\tload-graph          Load a graph from a file.\n";
    std::cout << "\tsave-graph          Save the current graph to a file.\n";
    std::cout << "\tdraw-graph          Draw the current graph into a PNG image.\n";
    std::cout << "\tclean-graph         Remove all nodes and arcs from the graph.\n";
    std::cout << "\n";
    std::cout << "Nodes commands: \n";
    std::cout << "\tcreate-node         Create a new node.\n";
    std::cout << "\tmodify-node         Modify or delete a node.\n";
    std::cout << "\tshow-nodes          Show all nodes.\n";
    std::cout << "\n";
    std::cout << "Arcs commands: \n";
    std::cout << "\tcreate-arc          Create a new arc.\n";
    std::cout << "\tmodify-arc          Modify or delete an arc.\n";
    std::cout << "\tshow-arcs           Show all arcs.\n";
    std::cout << "\n";
    std::cout << "Person commands: \n";
    std::cout << "\tcreate-person       Create a new person.\n";
    std::cout << "\tmodify-person       Modify or delete a person.\n";
    std::cout << "\tshow-people         Show all people.\n";
    std::cout << "\tload-default-people Load default people (20).\n";
    std::cout << "\tclean-people        Remove all people.\n";
    std::cout << "\n";
    std::cout << "Simulation commands: \n";
    std::cout << "\tsimulate            Start the hike simulation.\n";
    std::cout << "\n";
    std::cout << "Report commands: \n";
    std::cout << "\tshow-amplitude      Report 1 - Show the amplitude of the graph.\n";
    std::cout << "\tshow-depth          Report 2 - Show the depth of the graph.\n";
    std::cout << "\tshow-people         Report 3 - Show all people in the list information.\n";
    std::cout << "\tshow-shortest-path  Report 4 - Show the shortest path for a person (Movement type Direc or Through all).\n";
    std::cout << "\tshow-friends        Report 5 - Show the names of the friends X person got\n";
    std::cout << "\tshow-no-friends     Report 6 - Show the names of the people who got 0 friends\n";
    std::cout << "\tshow-no-walkies     Report 7 - Show the names of the people who got trapped in a node due to there not being a way out\n";
}
}
