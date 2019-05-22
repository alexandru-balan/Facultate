#include <iostream>
#include "Graph.h"

using namespace std;

int main () {

    Graph graph ("graf.in");

    graph.getAdjMatrix(false);
    graph.printBridges();
    graph.printVulnerableNodes();

    return 0;
}