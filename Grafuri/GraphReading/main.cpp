#include <iostream>
#include "Graph.h"
#include "OrderedGraph.h"

using namespace std;

int main() {

    Graph *graph = new Graph ("graf.in");

    graph->toAdjMatrix();
    graph->toAdjLists();

    OrderedGraph orderedGraph("graf.in");

    orderedGraph.toAdjLists();
    orderedGraph.toAdjMatrix();

    return 0;
}