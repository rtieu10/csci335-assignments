// Rachel Tieu
// 5-8-20
// This program initializes a GRaph object and calls the functions that
//  builds the graph, and prints out the nodes that are adjacent to it
//  along with the weights on the edges if connected 

#include <iostream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv) {


    Graph test;
    test.CreateGraph(argv[1]);
    test.isConnected(argv[2]);

    return 0;
}

int main(int argc, char **argv) {

    graphTestDriver(argc, argv);

    return 0;
}
