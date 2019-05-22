//
// Created by alexandru-balan on 22/05/19.
//

#ifndef MUCHIICRITICE_GRAPH_H
#define MUCHIICRITICE_GRAPH_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

class Graph {
private:

    int nbNodes;
    int nbEdges;
    set<int> Nodes;
    int** adjMatrix;
    vector<bool> visited;
    vector<int> discoveryTime;
    vector<int> lowestVertexAccess;
    vector<int> parent;
    int time = 0;

    void findBridges (int start) {
        visited[start] = 1;

        discoveryTime[start] = lowestVertexAccess[start] = ++time;

        for (int i = 0; i < nbNodes; ++i) {
            if (adjMatrix[start][i]) {
                if (!visited[i]) {
                    parent[i] = start;
                    findBridges(i);
                    lowestVertexAccess[start] = min(lowestVertexAccess[start], lowestVertexAccess[i]);
                    if (lowestVertexAccess[i] > discoveryTime[start]) {
                        cout << start + 1 << " --- " << i + 1 << endl;
                    }
                }
                else if (parent[start] != i) {
                    lowestVertexAccess[start] = min (lowestVertexAccess[start], discoveryTime[i]);
                }
            }
        }


    }

    void findVulnerableNodes (int start, set<int>& vulenrabilities) {
        visited [start] = true;

        lowestVertexAccess[start] = discoveryTime[start] = ++time;

        int children = 0;

        for (int i = 0; i < nbNodes; ++i) {
            children++;
            if (adjMatrix[start][i]) {

                if (!visited[i]) {
                    children++;
                    parent [i] = start;
                    findVulnerableNodes(i,vulenrabilities);
                    lowestVertexAccess[start] = min (lowestVertexAccess[start], lowestVertexAccess[i]);

                    /*if (parent[start] == -1 && children > 1) {
                        cout << start + 1 << " ";
                    }*/

                    if (parent[start] != -1 && lowestVertexAccess[i] >= discoveryTime[start]) {
                        vulenrabilities.insert(start + 1);
                    }
                }
                else if (i != parent[start]) {
                    lowestVertexAccess[start] = min (lowestVertexAccess[start], discoveryTime[i]);
                }
            }
        }
    }

public:

    Graph (const char* path_to_file) {
        ifstream f(path_to_file);

        if (!f.is_open()) {
            perror("Can't open file to read graph\n");
            return;
        }

        f>>nbNodes>>nbEdges;

        /*Matrix initialisation*/
        adjMatrix = new int* [nbNodes];
        for (int j = 0; j < nbNodes; ++j) {
            adjMatrix[j] = new int [nbNodes];
            for (int i = 0; i < nbNodes; ++i) {
                adjMatrix[j][i] = 0;
            }
        }

        for (int i = 0; i < nbEdges; ++i) {
            int v1, v2;
            f>>v1>>v2;

            Nodes.insert(v1); Nodes.insert(v2);

            /**
             * Constructing the matrix here because it is easier than reading the file all over again
             */
             adjMatrix[v1 - 1][v2 - 1] = adjMatrix[v2 - 1][v1 - 1] = 1;
        }

        visited.assign(nbNodes, false);
        discoveryTime.assign(nbNodes, 0);
        lowestVertexAccess.assign(nbNodes, 0);
        parent.assign(nbNodes, -1);

    }

    int** getAdjMatrix (bool quiet = true) {

        int** copyToReturn = new int* [nbNodes];

        for (int i = 0; i < nbNodes; ++i) {
            copyToReturn[i] = new int [nbNodes];
            for (int j = 0; j < nbNodes; ++j) {
                copyToReturn[i][j] = adjMatrix[i][j];
            }
        }

        if (!quiet) {
            for (int i = 0; i < nbNodes; ++i) {
                for (int j = 0; j < nbNodes; ++j) {
                    cout << copyToReturn[i][j] << " ";
                }
                cout << endl;
            }
        }

        return copyToReturn;
    }

    void printBridges() {
        for (int i = 0; i < nbNodes; ++i) {
            if (!visited[i]) {
                findBridges(i);
            }
        }

        visited.assign(nbNodes, false);
        discoveryTime.assign(nbNodes, 0);
        lowestVertexAccess.assign(nbNodes, 0);
        parent.assign(nbNodes, -1);
        time = 0;
    }

    void printVulnerableNodes () {
        set<int> vulnerabilities;

        cout << "Vulnerable Nodes in the Graph: ";
        for (int i = 0; i < nbNodes; ++i) {
            if (!visited[i]) {
                findVulnerableNodes(i,vulnerabilities);
            }
        }

        for (auto x : vulnerabilities) {
            cout << x << " ";
        }

        visited.assign(nbNodes, false);
        discoveryTime.assign(nbNodes, 0);
        lowestVertexAccess.assign(nbNodes, 0);
        parent.assign(nbNodes, -1);
        time = 0;

        cout << endl;
    }

};


#endif //MUCHIICRITICE_GRAPH_H
