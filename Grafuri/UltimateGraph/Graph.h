//
// Created by alexandru-balan on 24.05.2019.
//

#ifndef ULTIMATEGRAPH_GRAPH_H
#define ULTIMATEGRAPH_GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    /*Basic stuff*/
    int nbVertices, nbEdges;
    set<int> Vertices;

    /*Adjacency constructions*/
    map<int, vector<int>> adjMap;

    /*Cycle detection*/
    void cycleUtil (int start, vector<bool> &visited, vector<int> &parent, bool &detected, vector<int> &aCycle) { // A slightly modified DF
        visited[start] = true;

        for (auto x : adjMap[start]) {
            if (!visited[x]) {
                parent[x] = start;
                cycleUtil(x,visited,parent,detected,aCycle);
            } else
                if (x != parent[start]) {
                    if (aCycle.empty()) {
                        while (start != x ) {
                            aCycle.push_back(start);
                            start = parent[start];
                        }
                        aCycle.push_back(start);
                    }
                    detected = true;
                    return;
                }
        }
    }

    /*Weighted graphs utils*/
    struct Edge {
        int v1, v2, w;
    };
    vector<Edge> edges;
    vector<int> weights;
    void readWeightedGraph (const char* path_to_file) {
        /*File stream declaration*/
        ifstream f (path_to_file);
        if (!f.is_open()) {
            perror("Cannot open file\n");
            return;
        }

        /*File reading and additional constructions*/
        f>>nbVertices>>nbEdges;
        for (int i = 0; i < nbEdges; ++i) {
            int v1,v2,w;
            f>>v1>>v2>>w;
            adjMap[v1].push_back(v2);
            adjMap[v2].push_back(v1);
            Edge edge;
            edge.v1 = v1; edge.v2 = v2; edge.w = w;
            edges.push_back(edge);
            Vertices.insert(v1); Vertices.insert(v2);
        }

        f.close();
    }
    void disjointedBFS (int start, vector<bool> &visited) {
        queue<int> Q;
        Q.push(start);

        while (!Q.empty()) {
            int x = Q.front(); Q.pop();
            visited[x] = true;
            for (auto v : adjMap[x]) {
                if (!visited[v]) {
                    Q.push(v);
                }
            }
        }
    }

    /*Kruskal Algorithm*/
    vector<int> parents;
    vector<int> ranks;
    void makeSet (int v) {
        parents[v] = v;
    }
    int find (int v) {
        if (parents[v] != v) {
            parents[v] = find(parents[v]);
        }
        return parents[v];
    }
    void Union (int x, int y) {
        int xr = find(x);
        int yr = find(y);

        if (xr == yr) {
            return;
        }

        if (xr < yr) {
            swap(xr, yr);
        }

        parents[yr] = xr;
        if (ranks[xr] == ranks[yr]) {
            ranks[xr]++;
        }
    }
    static bool compareEdges (Edge e1, Edge e2) {
        return (e1.w < e2.w);
    }
    vector<Edge> Kruskal (vector<Edge> edges) {
        vector<Edge> MST;

        for (auto edge : edges) {
            if (find(edge.v1) != find(edge.v2)) {
                MST.push_back(edge);
                Union(edge.v1, edge.v2);
            }
        }

        return MST;
    }

    /*Prim's Algorithm*/
    static vector<int> cost;
    vector<Edge> E;
    bool static costCompare (int v1, int v2) {
        return (cost[v1] > cost[v2]);
    }
    vector<Edge> Prim (int start, vector<Edge> edges) {
        Edge flag; flag.w = -42;
        cost.assign(nbVertices+1, INT32_MAX);
        E.assign(nbVertices+1, flag);

        cost[start] = 0;


        vector<Edge> MST;
        vector<int> Q;
        for (auto x : Vertices) {
            Q.push_back(x);
        }
        make_heap(Q.begin(),Q.end(),costCompare);

        while (!Q.empty()) {
            int x = Q.front(); //the vertex with the smallest cost
            pop_heap(Q.begin(),Q.end()); Q.pop_back();

            if (Q.empty()) {
                for (auto edge : edges) {
                    if (edge.v1 == x) {
                        if ((edge.w < cost[edge.v1]) ) {
                            /*cost[edge.v2] = edge.w;
                            E[edge.v2] = edge;*/
                            MST.push_back(edge);
                            break;
                        }
                    }
                    if (edge.v2 == x) {
                        if ((edge.w < cost[edge.v2]) ) {
                            /*cost[edge.v2] = edge.w;
                            E[edge.v2] = edge;*/
                            MST.push_back(edge);
                            break;
                        }
                    }
                }
                break;
            }

            if (E[x].w != -42) {
                MST.push_back(E[x]);
            }
            for (auto edge : edges) {
                if (edge.v1 == x || edge.v2 == x) {
                    if ((edge.w < cost[edge.v2]) ) {
                        sort_heap(Q.begin(),Q.end());
                        if (x == edge.v1) {
                            if (binary_search(Q.begin(),Q.end(),edge.v2)) {
                                cost[edge.v2] = edge.w;
                                E[edge.v2] = edge;
                            }
                        }
                        if (x == edge.v2) {
                            if (binary_search(Q.begin(),Q.end(),edge.v1)) {
                                cost[edge.v1] = edge.w;
                                E[edge.v1] = edge;
                            }
                        }
                        make_heap(Q.begin(),Q.end(),costCompare);
                    }
                }
            }
        }

        return MST;
    }


public:
    explicit Graph (const char* path_to_file, bool isWeighted = false) {

        if (isWeighted) {
            readWeightedGraph(path_to_file);
            return;
        }

        /*File stream declaration*/
        ifstream f (path_to_file);
        if (!f.is_open()) {
            perror("Cannot open file\n");
            return;
        }

        /*File reading and additional constructions*/
        f>>nbVertices>>nbEdges;
        for (int i = 0; i < nbEdges; ++i) {
            int v1,v2;
            f>>v1>>v2;
            adjMap[v1].push_back(v2);
            adjMap[v2].push_back(v1);
            Vertices.insert(v1); Vertices.insert(v2);
        }

        f.close();
    }

    /*Returns true or false if it finds a cycles*/
    bool isCyclic (bool quiet = true) {
        vector<bool> visited(nbVertices+1, false);
        vector<int> parent(nbVertices+1, -1);
        vector<int> aCycle;
        bool detected = false;
        cycleUtil(1,visited,parent,detected, aCycle);

        if (!quiet) {
            cout << "Provided graph contains cycles\n";
            cout << "A cycle: ";
            for (auto x : aCycle) {
                cout << x << " ";
            }
            cout << endl;
        }

        return detected;
    }

    bool isDisjointed () {
        vector<bool> visited(nbVertices+1, false);
        visited[0] = true;
        disjointedBFS(1, visited);

        for (auto x : visited) {
            if (!x) {
                return true;
            }
        }

        return false;
    }

    void buildMST () {
        if (this->isDisjointed()) {
            cout << "Cannot build MST\n";
            return;
        }

        /*Initializing forests*/
        parents.assign(nbVertices+1,-1);
        ranks.assign(nbVertices+1,0);
        for (auto v : Vertices) {
            makeSet(v);
        }

        /*Sorting edges by weight*/
        sort(edges.begin(),edges.end(),compareEdges);

        /*Calling Kruskal main function*/
        vector<Edge> MST = Kruskal(edges);

        for (auto edge : MST) {
            cout << edge.v1 << " " << edge.v2 << endl;
        }
    }

    void buildMSTP () {
        vector<Edge> MST = Prim(1,edges);

        for (auto edge : MST) {
            cout << edge.v1 << " " << edge.v2 << endl;
        }
    }
};

vector<int> Graph::cost(50,100);


#endif //ULTIMATEGRAPH_GRAPH_H
