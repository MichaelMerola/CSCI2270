#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <stdlib.h>

using namespace std;

template<typename T>
Graph<T>::Graph () {

}//end constructor

template<typename T>
Graph<T>::~Graph () {

}//end destructor

template<typename T>
void Graph<T>::addVertex(T name) {

    bool found = false;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].name == name) {
            found = true;
            break;
        }
    }//end for
    if (found == false) {
        vertex<string> v;
        v.name = name;
        vertices.push_back(v);
    }

}//end addVertex

template<typename T>
void Graph<T>::addEdge(T v1, T v2, int weight) {

    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].name == v1) {

            for (int j = 0; j < vertices.size(); j++) {
                if (vertices[j].name == v2 && i != j) {
                    adjVertex<string> av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }//end for j
        }//end if
    }//end for i

}//end addEdge

template<typename T>
void Graph<T>::readDataFile(char* filename) {

    int totalCount = 0;
    ifstream zombtxt;
    bool uniq;

    zombtxt.open(filename, ifstream::in); //open the file

    if (zombtxt.fail()) {
        cout << "Could not open file" << endl; // check if file opens successfully
    }
    else {
        //relevant variables
        string line;
        int j; //line counter

        while (getline(zombtxt, line)) { //run through all lines of data

            stringstream ss(line);
            string c;
            j = 0; //line counter

            vertex <string> v1;
            vertex <string> v2;

            while (getline(ss, c, ',')) { //check through each element (c) in the line
                if (j == 0) { //create vertices for each city on first line

                    int index = 0; //word counter
                    if (index > 0) {

                        addVertex(c); //create vertex with name 'c'
                    }//end if

                    index++;
                }//end first data line
                else { //create edges for each city
                    int index = 0;
                    if (index == 0) {
                        v1 = vertices[j-1];
                    }
                    else if (stoi(c) != -1 && stoi(c) != 0) { //ignore nonexistent edges

                        v2 = vertices[index-1];
                        addEdge(v1.name,v2.name, stoi(c.c_str()));
                    }

                    index++;
                }//end else

                j++;
            }//end while inner




        }//end while
    }//end else

}//end readDataFile
