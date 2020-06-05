// Rachel Tieu
// 5-8-20
// This program contains the driver for the pathfinder, and initializes
//  a graph object, and calls the dijkstra algorithm on the graph, and
//  prints out the the shortest path from all the nodes in the graph to
//  a given node


#include <iostream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;


int pathfindDriver(int argc, char **argv) {

  Graph test;
  test.CreateGraph(argv[1]);
  int nodeinput = stoi(argv[2]);
  test.dijkstra(nodeinput);
  test.printDijkstra();

  return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
