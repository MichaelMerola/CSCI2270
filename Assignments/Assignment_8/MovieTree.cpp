#include "MovieTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

MovieTree::MovieTree () {
    root = NULL;

}//end constructor

MovieTree::~MovieTree () {


}//end destructor


//
//private functions
//

void MovieTree::addNode(MovieNode* newNode, MovieNode* temp) {

    int newChar = newNode->title[0];
    int tempChar = temp->title[0];

    if (newChar > tempChar && temp->right != NULL){ //new > temp and temp has a right child
        addNode(newNode, temp->right); //move to right
        return;
    }
    else if (newChar > tempChar && temp->left != NULL){ //new < temp and temp has a left child
        addNode(newNode, temp-> left); //move to left
        return;
    }
    else { //temp does not have any children

        if (newChar > tempChar){
            temp->right = newNode;
            newNode->parent = temp;
        }
        else if (newChar < tempChar){
            temp->left = newNode;
            newNode->parent = temp;
        }

    } //end else

    return;

}//end addNode

MovieNode* MovieTree::treeSearch(MovieNode* temp, string title) { //search preorder

    int searchChar = title[0];
    int tempChar = temp->title[0];

    cout << temp->title << endl;

    if (temp->title == title) {
        return temp;
    }
    else if (tempChar > searchChar && temp->left != NULL) {
        return treeSearch(temp->left, title);
    }
    else if (tempChar < searchChar && temp->right != NULL){
        return treeSearch(temp->right, title);
    }

}//end treeSearch


//
//public functions
//

void MovieTree::findMovie(string title) {

    MovieNode* found;
    found = treeSearch(root, title);

    if (found == NULL) {
        cout << "Movie not found." << endl;
    }
    else {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << found->ranking << endl;
        cout << "Title:" << found->title << endl;
        cout << "Year:" << found->year << endl;
        cout << "Quantity:" << found->quantity << endl;
    }

}//end findMovie

void MovieTree::readDataFile(char* filename) {

    int totalCount = 0;
    ifstream movietxt;
    //int length;
    bool uniq;

    movietxt.open(filename, ifstream::in); //open the file

    if (movietxt.fail()) {

        cout << "Something went wrong" << endl;
        //return false; // check if file opens successfully
    }
    else {
        //relevant variables
        string line;
        int j = 0; //line counter

        int rank; //IMDB Ranking
        string title; //movie title
        int year; //release year
        int quantity; //number in stock

        while (getline(movietxt, line)) { //run through all lines of data

            stringstream ss(line);
            string c;
            j = 0;

            while (getline(ss, c, ',')) { //check through each element (c) in the line

                switch(j) {
                    case 0:
                        rank = stoi(c);
                        break;
                    case 1:
                        title = c;
                        break;
                    case 2:
                        year = stoi(c);
                        break;
                    case 3:
                        quantity = stoi(c);
                        break;
                }//end switch

                j++;
            }//end while

            MovieNode* n = new MovieNode(rank, title, year, quantity);
            MovieNode* temp;

            cout << n->title << endl;

            if (root == NULL) { // !!!possible error: root is never set to anything

                root = n; //add newNode to root
            }
            else {
                temp = root;
                addNode(n, temp); //add node to BST
            }

            //next line
        }//end data
    }//end else


}//end readDataFile
