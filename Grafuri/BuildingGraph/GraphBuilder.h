//
// Created by alexandru-balan on 22/05/19.
//

#ifndef BUILDINGGRAPH_GRAPHBUILDER_H
#define BUILDINGGRAPH_GRAPHBUILDER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class GraphBuilder {
private:
    int n;
    vector<int> colabs;
    map <int,int> nodeBindings;
    bool canBuild = false;

    struct Edge {
        int v1, v2;
    };
    vector<Edge> edges;


    void isGraphic (vector<int> S) {

        canBuild = true;
        for (int i : S) {
            if (i != 0) {
                canBuild = false;
                break;
            }
            if (i < 0) {
                canBuild = false;
                return;
            }
        }


        sort(S.begin(),S.end(),std::greater_equal()); //sorts the vector decreasingly

        for (int i = 1; i <= S[0]; ++i) { // HAVEL-HAKIMI ALGORITHM
            S[i] --;
        }

        vector<int> S2;

        for (int j = 1; j < S.size(); ++j) {
            S2.push_back(S[j]);
        }

        if (!canBuild) {
            isGraphic(S2);
        }
    }

   /* void customSort (vector<int> &S) {
        for (int i = 0; i < S.size(); ++i) {
            for (int j = i; j < S.size(); ++j) {
                if (S[i] <= S[j]) {

                    swap(positions[i],positions[j]);
                }
            }
        }
    }*/

   int findNumber (int value) {
       int nodeNumber = 0;
       for (int j = 0; j < nodeBindings.size(); j++) {
           if (nodeBindings[j] == value) {
               nodeNumber = j;

           }
       }

       return nodeNumber;
   }

    void createPairs (vector<int> S) {

        sort(S.begin(),S.end(),std::greater_equal());

        static int offset = 0;

        if (!canBuild) {
            cout << "Cannot build such a graph!\n";
            return;
        }

        /*Testing if the vector has only 0*/
        bool flag = true;
        for (int i = 0; i <= S.size(); ++i) {
            if (S[i]) {
                flag = false;
                break;
            }
        }

        if (!flag) {

            for (int i = 1; i <= S[0]; ++i) {
                Edge newEdge;

                int posFirst = findNumber(S[0] + offset);
                nodeBindings.erase(posFirst);
                int v = findNumber(S[i] + offset);

                newEdge.v1 = posFirst;
                newEdge.v2 = v;

                /*Reduce the content of S*/
                S[i]--;
            }

            /*Making S2 so we can build further edges*/
            vector<int> S2;
            for (int j = 1; j < S.size(); ++j) {
                S2.push_back(S[j]);
            }

            offset++;
            createPairs(S2);
        } else {
            return;
        }
    }

public:

    explicit GraphBuilder(const char* path_to_file) {

        ifstream f(path_to_file);

        if (!f.is_open()) {
            perror("Cannot open file\n");
            return;
        }

        f>>n;

        for (int i = 0; i < n; ++i) {
            int x;
            f>>x;
            colabs.push_back(x);
            int key = i +1;
            nodeBindings.insert_or_assign(key,x);
        }
    }

    bool getCanBuild () {
        isGraphic(colabs);
        return canBuild;
    }

    /******************************************************************************************************************
     * offstream o = an output file stream; if not provided will print to screen
     *
     * buildPairs closes your stream even if it succeeds or not !
     * If you want to use the output file again later consider opening a new stream for it after calling this function.
     ******************************************************************************************************************/
    void buildPairs (ofstream* o = nullptr) {
        isGraphic(colabs);

        if (canBuild) {
            createPairs(colabs);
        } else {
            cout << "Cannot create such graph\n";
        }

        if (o != nullptr) {
            for (auto edge : edges) {
                *o << edge.v1 << " " << edge.v2 << endl;
            }
        } else {
            for (auto edge : edges) {
                cout << edge.v1 << " " << edge.v2 << endl;
            }
        }

        try {
            o->close();
        }
        catch (exception &e) {
            cout << e.what();
        }
    }

};


#endif //BUILDINGGRAPH_GRAPHBUILDER_H
