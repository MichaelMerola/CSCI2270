#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <map>
#include <stdlib.h>

using namespace std;

template<class T>
Graph<T>::Graph () {

}//end constructor

template<class T>
Graph<T>::~Graph () {

}//end destructor

template<class T>
void Graph<T>::printGraph() { //adapted from moodle

    for (int i = 0; i < vertices.size(); i++){
        cout << vertices[i].district << ":" << vertices[i].name << "-->";
        for (int j = 0; j < vertices[i].adj.size(); j++){
            cout << vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size() - 1) {
                cout << "***";
            }
        }
        cout << endl;
    }

}//end printGraph

template<class T>
void Graph<T>::assignDistricts() {
    int district = 1;
    for(int i = 0; i < vertices.size(); i++) {
        if (vertices[i].district == -1) {
          BFTraversalLabel(vertices[i].name, district);//search breadth first

          district++;
        }
    }
}//end assignDistricts

template<class T>
void Graph<T>::BFTraversalLabel(T startingCity, int distID) {

    queue<vertex<string>*> qu;
    for (int i = 0; i < vertices.size(); i++) {

        vertices[i].visited = false;
    }

    for (int i = 0; i < vertices.size(); i++) {

        if (vertices[i].name == startingCity) {

            vertices[i].visited = true;
            qu.push(&vertices[i]);

            vertices[i].district = distID;

            break;
        }
    }

    while (qu.empty() != true) {

        vertex<string>* head = qu.front();
        qu.pop();

        for (int i = 0; i < head->adj.size(); i++) {
            if (head->adj[i].v->visited == false) {
                head->adj[i].v->visited = true;
                head->adj[i].v->district = distID;

                qu.push(head->adj[i].v);
            }
        }//end for
    }
}//end breadthFirst

template<class T>
void Graph<T>::shortestPath(T startingCity, T endingCity) {

    vertex<string>* start = findVertex(startingCity);
    vertex<string>* end = findVertex(endingCity);

    if (start == NULL || end == NULL) {

        cout << "One or more cities doesn't exist" << endl;
        return;
    }
    if (end->district != start->district) {

        cout << "No safe path between cities" << endl;
        return;
    }
    if (end->district == -1 || start->district == -1) {

        cout << "Please identify the districts before checking distances" << endl;
        return;
    }

    for (int i = 0; i < vertices.size(); i++) {

        vertices[i].visited = false;
    }

    start->visited = true;
    queueVertex<string> v;

    v.distance = 0;
    v.path.push_back(start);

    queue<queueVertex<string> > qu;
    qu.push(v);

    while (qu.empty() != true) {
        v = qu.front();
        qu.pop();

        for (int i = 0; i < v.path.back()->adj.size(); i++) {

            if (v.path.back()->adj[i].v->visited == false) {

                vector<vertex<string> *> path = v.path;
                v.path.back()->adj[i].v->visited = true;

                int dist = v.distance + 1;

                path.push_back(v.path.back()->adj[i].v);
                queueVertex<string> temp;

                temp.path = path; //set path
                temp.distance = dist; //set distance

                if (v.path.back()->adj[i].v == end) {

                    cout << temp.distance;
                    for (int j = 0; j < temp.path.size(); j++) {

                        cout << "," << temp.path[j]->name;
                    }
                    cout << endl;
                    return;
                }
                else {

                    qu.push(temp);

                }
            }//end if

        }//end for
    }//end while
    return;
}//end shortestPath

template<class T>
vertex<T>* Graph<T>::findVertex(T name) {

    for (int i = 0; i < vertices.size(); i++) {

        if (vertices[i].name == name) {

          return &vertices[i];
        }
    }//end for

    return NULL;
}//end findVertex

template<class T>
void Graph<T>::addVertex(T name) { //adapted from moodle
  bool found = false;
  for (int i = 0; i < vertices.size(); i++){
    if(vertices[i].name == name){
      found = true;
      cout<<vertices[i].name<<" found."<<endl;
    }
  }

  if(found == false){
    vertex<T> v;
    v.name = name;
    v.district = -1;
    vertices.push_back(v);
  }
}//end addVertex

template<class T>
void Graph<T>::addEdge(T v1, T v2, int weight) { //adapted from moodle

  for(int i = 0; i < vertices.size(); i++){

    if(vertices[i].name == v1){
      for(int j = 0; j < vertices.size(); j++){

        if(vertices[j].name == v2 && i != j){

          adjVertex<T> av;
          av.v = &vertices[j];
          av.weight = weight;
          vertices[i].adj.push_back(av);
        }
      }

    }
  }
}//end addEdge

template<class T>
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
        int row = 0; //line counter
        int index; //word counter
        map<int, string> cities;

        while (getline(zombtxt, line)) { //run through all lines of data

            stringstream ss(line);
            string c;
            index = 0;

            string v1;
            string v2;

            while (getline(ss, c, ',')) { //check through each element (c) in the line
                if (row == 0) { //create vertices for each city on first line

                    if (index != 0) {
;
                        cities[index] = c;
                        addVertex(c); //create vertex with name 'c'
                    }//end if

                    index++;
                }//end first data line
                else { //create edges for each city

                    if (index == 0) {

                        v1 = c;
                    }
                    else if (stoi(c) != -1) { //ignore nonexistent edges

                        v2 = cities[index];
                        addEdge(v1, v2, 1);
                    }

                    index++;
                }//end else

            }//end while inner

            row++;
        }//end while
    }//end else

}//end readDataFile

template class Graph<string>;
