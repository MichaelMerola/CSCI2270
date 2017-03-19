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

    DeleteAll(root);

}//end destructor


//
//private functions
//

void MovieTree::addNode(MovieNode* newNode, MovieNode* temp) {

    if (newNode->title > temp->title && temp->right != NULL){ //new > temp and temp has a right child
        addNode(newNode, temp->right); //move to right
        return;
    }
    else if (newNode->title < temp->title && temp->left != NULL){ //new < temp and temp has a left child
        addNode(newNode, temp->left); //move to left
        return;
    }
    else { //temp does not have any children

        if (newNode->title > temp->title){
            temp->right = newNode;
            newNode->parent = temp;
        }
        else if (newNode->title < temp->title){
            temp->left = newNode;
            newNode->parent = temp;
        }

    } //end else

    return;

}//end addNode

MovieNode* MovieTree::treeSearch(MovieNode* temp, string title) { //search inorder

    if (title < temp->title && temp->left != NULL) {
        return treeSearch(temp->left, title);
    }
    if (temp->title == title) {
        return temp;
    }
    if (title > temp->title && temp->right != NULL){
        return treeSearch(temp->right, title);
    }
    return NULL;
}//end treeSearch

MovieNode* MovieTree::inorderPrint(MovieNode* temp) {

    if(temp->left != NULL)
        inorderPrint(temp->left);

    cout << "Movie:" << temp->title << " " << temp->quantity << endl;

    if(temp->right != NULL)
        inorderPrint(temp->right);

}

void MovieTree::countNodes(MovieNode* temp, int* c) {

    if(temp->left != NULL)
        countNodes(temp->left, c);

    (*c)++;

    if(temp->right != NULL)
        countNodes(temp->right, c);

}

MovieNode* MovieTree::treeMax(MovieNode* temp) {

    if (temp == NULL)
        return NULL;

    while (temp->right != NULL) {
        temp = temp->right;
    }
    return temp; //returns max value of left subtree

}

void MovieTree::DeleteAll(MovieNode* temp) { //postorder traversal

    if (temp->left != NULL) {
        DeleteAll(temp->left);
    }
    if (temp->right != NULL) {
        DeleteAll(temp->right);
    }
    cout << "Deleting: "<< temp->title << endl;

    delete temp;

}//end DeleteAll

//
//public functions
//

void MovieTree::deleteMovieNode(string title) {
    MovieNode* found;
    found = treeSearch(root, title);

    if (found != NULL) {

        //No child
        if (found->right == NULL && found->left == NULL){
            if(found->parent->left == found){
                found->parent->left = NULL;
            }
            else {
                found->parent->right = NULL;
            }
            delete found;
        }
        //One child
        else if(found->right == NULL) {
            MovieNode *x = found->right;
            if (found->parent->right == found){
                found->parent->right = x;
            }
            else {
                found->parent->left = x;
            }
            x->parent = found->parent;
            delete found;
        }
        else if(found->left == NULL) {
            MovieNode *x = found->left;
            if (found->parent->left = found){
                found->parent->left = found->left;
            }
            else {
                found->parent->right = found->left;
            }
            found->left->parent = found->parent;
            delete found;
        }
        //Two child
        else {
            MovieNode* max = treeMax(found->left);//
            MovieNode* temp = found;
            max->right = found->right;
            max->left = found->left;
            found = max;
            delete temp;
            max->parent->right = NULL;
        }

    }//end outer if
    else {
        cout << "Movie not found." << endl;
    }

}

void MovieTree::countMovieNodes() {
    int *c = new int;
    *c = 0;
    countNodes(root, c);

    cout << "Tree contains: " << *c << " movies." << endl;
}

void MovieTree::rentMovie(string title) {

    MovieNode* found;
    found = treeSearch(root, title);

    if (found == NULL) {
        cout << "Movie not found." << endl;
    }
    else {
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << found->ranking << endl;
        cout << "Title:" << found->title << endl;
        cout << "Year:" << found->year << endl;
        cout << "Quantity:" << found->quantity << endl;

        found->quantity = found->quantity - 1;
        if (found->quantity == 0) {
            deleteMovieNode(title);
        }
    }
}

void MovieTree::printMovieInventory() {

    //prints recursively
    inorderPrint(root);
}

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
