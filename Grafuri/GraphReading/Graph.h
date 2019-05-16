#include <utility>

//
// Created by alexandru-balan on 16.05.2019.
//

#ifndef GRAFURI_GRAPH_H
#define GRAFURI_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;

struct Edge {
    int v1;
    int v2;
};

class Graph {
private:
    int nb_of_nodes;
    int nb_of_edges;
    vector<Edge> edges;
    set<int> nodes;
    int **adj_matrix;
    map<int, vector<int>> adj_lists;

protected:
    void setAdjLists (map<int, vector<int>> newAdjLists) {
        this->adj_lists = move(newAdjLists);
    }

    void setMatrix (int **matrix) {
        /*Clear matrix*/
        if (adj_matrix != nullptr) {
            delete[](adj_matrix);
        }

        /*Init of matrix*/
        adj_matrix = new int*[nb_of_nodes];

        for (int i = 0; i < nb_of_nodes; ++i) {
            adj_matrix[i] = new int[nb_of_nodes];
            for (int j = 0; j < nb_of_nodes; ++j) {
                adj_matrix[i][j] = matrix[i][j];
            }
        }
    }

public:
    Graph() {
        nb_of_nodes = 0;
        nb_of_edges = 0;
        adj_matrix = nullptr;
    }

    Graph(const char* path_to_file) {
        ifstream f;
        f.open(path_to_file);

        if (!f.is_open()) {
            nb_of_nodes = 0;
            nb_of_edges = 0;
            return;
        }

        f>>nb_of_nodes>>nb_of_edges;

        for (int i = 0; i < nb_of_edges; ++i) {
            int v1,v2;
            f>>v1>>v2;
            /*Create new edge*/
            Edge edge;
            edge.v1 = v1;
            edge.v2 = v2;
            edges.push_back(edge);

            /*Push the read nodes to 'nodes' */
            nodes.insert(v1);
            nodes.insert(v2);
        }

        adj_matrix = nullptr;

        f.close();
    }

    int getNbOfNodes () {
        return this->nb_of_nodes;
    }

    int getNbOfEdges () {
        return  this->nb_of_edges;
    }

    vector<Edge> getEdges() {
        return this->edges;
    }

    set<int> getNodes () {
        return  this->nodes;
    }

    int** getAdjMatrix () {
        if (adj_matrix == nullptr) {
            return nullptr;
        }

        int** matrix = new int*[nb_of_nodes];
        for(int i = 0; i < nb_of_nodes; ++i) {
            matrix[i] = new int[nb_of_nodes];
            for (int j = 0; j < nb_of_nodes; ++j) {
                matrix[i][j] = adj_matrix[i][j];
            }
        }

        return matrix;
    }

    map<int, vector<int>> getAdjLists () {
        return this->adj_lists;
    }

    void setNbOfNodes (int number) {
        this->nb_of_nodes = number;
    }

    void setNbOfEdges (int number) {
        this->nb_of_edges = number;
    }

    void setEdges (vector<Edge> newVector) {
        if (newVector.size() < this->nb_of_edges) {
            perror("Cannot set edges. Too Few!");
            return;
        }

        this->edges = newVector;
    }

    void setNodes (set<int> newNodes) {
        if (newNodes.size() < this->nb_of_nodes) {
            perror("Cannot set nodes. Too Few!");
            return;
        }

        this->nodes = newNodes;
    }

    void toAdjMatrix (bool quiet = false) {
        /*Clear matrix*/
        if (adj_matrix != nullptr) {
            delete[](adj_matrix);
        }

        /*Init of matrix*/
        adj_matrix = new int*[nb_of_nodes];

        for (int i = 0; i < nb_of_nodes; ++i) {
            adj_matrix[i] = new int[nb_of_nodes];
            for (int j = 0; j < nb_of_nodes; ++j) {
                adj_matrix[i][j] = 0;
            }
        }

        /*Completing the matrix*/
        for (auto edge : edges) {
            adj_matrix[edge.v1 - 1][edge.v2 - 1] = adj_matrix[edge.v2 - 1][edge.v1 - 1] = 1;
        }

        if (!quiet) {
            cout << "----------------" << endl;
            cout << "Adjacency Matrix" << endl;
            cout << "----------------" << endl;

            if (adj_matrix == nullptr) {
                cout << "No matrix\n";
                return;
            }

            for (int i = 0; i < nb_of_nodes; ++i) {
                for (int j = 0; j < nb_of_nodes; ++j) {
                    cout << adj_matrix[i][j] << " ";
                }
                cout << endl;
            }
        }

    }

    void toAdjLists (bool quiet = false) {
        auto *lists = new vector<int>[nb_of_nodes + 1];

        /*Completing the lists*/
        for (auto edge : edges) {
            lists[edge.v1].push_back(edge.v2);
            lists[edge.v2].push_back(edge.v1);
        }

        /*Mapping the lists*/
        for (int i = 1; i <= nb_of_nodes; ++i) {
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

            for (int i = 1; i <= nb_of_nodes; ++i) {
                cout << i << ": ";
                vector<int> value_to_print = adj_lists.at(i);
                for (int j : value_to_print) {
                    cout << j << " ";
                }
                cout << endl;
            }
        }
    }

};


#endif //GRAFURI_GRAPH_H
