#include <iostream>
#include "Graph.h"

int main() {

   /* Graph graph1 ("graph2.in");
    graph1.isCyclic(false);*/

    Graph graph2 ("graphweighted.in", true);
    graph2.buildMST();
    graph2.buildMSTP();

    return 0;
}