//
// Created by alexandru-balan on 16.05.2019.
//

#ifndef GRAFURI_ORDEREDGRAPH_H
#define GRAFURI_ORDEREDGRAPH_H

#include "Graph.h"

class OrderedGraph : public Graph {
public:
    OrderedGraph () : Graph() {}

    OrderedGraph (const char* path_to_file) : Graph (path_to_file) {};

    void toAdjMatrix (bool quiet = false) {
        /*Clear matrix*/
        int **adj_matrix = getAdjMatrix();
        if (adj_matrix != nullptr) {
            delete[](adj_matrix);
        }

        /*Init of matrix*/
        adj_matrix = new int*[getNbOfNodes()];

        for (int i = 0; i < getNbOfNodes(); ++i) {
            adj_matrix[i] = new int[getNbOfNodes()];
            for (int j = 0; j < getNbOfNodes(); ++j) {
                adj_matrix[i][j] = 0;
            }
        }

        /*Completing the matrix*/
        for (auto edge : getEdges()) {
            adj_matrix[edge.v1 - 1][edge.v2 - 1] = 1;
        }

        if (!quiet) {
            cout << "----------------" << endl;
            cout << "Adjacency Matrix" << endl;
            cout << "----------------" << endl;

            if (adj_matrix == nullptr) {
                cout << "No matrix\n";
                return;
            }

            for (int i = 0; i < getNbOfNodes(); ++i) {
                for (int j = 0; j < getNbOfNodes(); ++j) {
                    cout << adj_matrix[i][j] << " ";
                }
                cout << endl;
            }
        }

        setMatrix(adj_matrix);
    }

    void toAdjLists (bool quiet = false) {
        auto *lists = new vector<int>[getNbOfNodes() + 1];

        auto adj_lists = getAdjLists();

        /*Completing the lists*/
        for (auto edge : getEdges()) {
            lists[edge.v1].push_back(edge.v2);
        }

        /*Mapping the lists*/
        for (int i = 1; i <= getNbOfNodes(); ++i) {
            adj_lists.insert_or_assign(i,lists[i]);
        }

        if (!quiet) {
            cout << "---------------" << endl;
            cout << "Adjacency Lists" << endl;
            cout << "---------------" << endl;

            if (adj_lists.empty()) {
                cout << "No lists\n";
                return;
            }

            for (int i = 1; i <= getNbOfNodes(); ++i) {
                cout << i << ": ";
                vector<int> value_to_print = adj_lists.at(i);
                for (int j : value_to_print) {
                    cout << j << " ";
                }
                cout << endl;
            }
        }

        setAdjLists(adj_lists);
    }
};


#endif //GRAFURI_ORDEREDGRAPH_H
