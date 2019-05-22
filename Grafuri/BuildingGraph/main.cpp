/*
 * There are n people that say they have worked together with k other people.
 * Is it possible that what they are saying is true?
 * Can we make a graph form their information? If yes, then build a possible graph.
 */

#include <iostream>
#include <fstream>
#include "GraphBuilder.h"

using namespace std;

int main() {

    GraphBuilder graphBuilder("graph.in");

    cout << graphBuilder.getCanBuild();

    ofstream o("graf.out");
    graphBuilder.buildPairs(&o);

    return 0;
}