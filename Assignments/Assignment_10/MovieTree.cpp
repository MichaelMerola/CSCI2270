#include "MovieTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

MovieTree::MovieTree () {
    root = NULL;
    leaf = new MovieNode(0, "", 0, 0);
    leaf->isRed = false;

}//end constructor

MovieTree::~MovieTree () {

    DeleteAll(root);

}//end destructor

//
// Red/Black functions
//

int MovieTree::countLongestPath() {

    int path = rcountLongPath(root);

    if (path != 0)
        return path;

    return 0;

}//end countLongestPath

int MovieTree::rcountLongPath(MovieNode *temp) {
    if (temp == leaf) {
        return 0;
    }
    else {
        int pathRight = rcountLongPath(temp->right);
        int pathLeft = rcountLongPath(temp->left);
        if (pathLeft > pathRight){
            return pathLeft + 1;//include root
        }
        else {
            return pathRight + 1;
        }
    }
}//end rcountLongPath

void MovieTree::rbAddFixup(MovieNode* node) {

    MovieNode* x = node;
    MovieNode* uncle;

    while (x != root and x->parent->isRed == true) {
        if (x->parent == x->parent->parent->left) { //x->parent is a left child
            uncle = x->parent->parent->right;
            if (uncle->isRed == true) {
                //CASE1LEFT(x, uncle)
                x->parent->isRed = false;
                uncle->isRed = false;
                x->parent->parent->isRed = true;

                x = x->parent->parent;
            }//end unlce->isRed
            else {
                if (x == x->parent->right) {
                    x = x->parent;
                    leftRotate(x);
                }
                //CASE3LEFT(x)
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                rightRotate(x->parent->parent);

            }//end else
        }
        else { //x->parent is a right child
            uncle = x->parent->parent->left;
            if (uncle->isRed == true) {
                //CASE1Right(x, uncle)
                x->parent->isRed = false;
                uncle->isRed = false;
                x->parent->parent->isRed = true;

                x = x->parent->parent;
            }//end unlce->isRed
            else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rightRotate(x);
                }
                //CASE3Right(x)
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                leftRotate(x->parent->parent);

            }//end else

        }
    }//end while
    root->isRed = false;
}//end rbAddFixup

void MovieTree::leftRotate(MovieNode* x) {
    MovieNode* y = x->right;
    x->right = y->left;
    if (y->left != leaf) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == leaf) {
        root = y;
    }
    else {
        if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}//end leftRotate

void MovieTree::rightRotate(MovieNode* x) {
    MovieNode* y = x->left;
    x->left = y->right;
    if (y->right != leaf) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == leaf) {
        root = y;
    }
    else {
        if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }
    y->right = x;
    x->parent = y;
}

int MovieTree::rbValid(MovieNode* node) { // Returns 0 if the tree is invalid, otherwise returns the black node height.
    int lh = 0;
    int rh = 0;
    // If we are at a nil node just return 1
    if (node == leaf)
        return 1;
    else {
        // First check for consecutive red links.
        if (node->isRed) {
            if(node->left->isRed || node->right->isRed) {
                return 0;
            }
        }
        // Check for valid binary search tree.
        if ((node->left != leaf && node->left->title.compare(node->title) > 0) || (node->right != leaf && node->right->title.compare(node->title) < 0)) {
            return 0;
        }
        // Deteremine the height of let and right children.
        lh = rbValid(node->left);
        rh = rbValid(node->right);
        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh) {
            return 0;
        }
        // If neither height is zero, incrament if it if black.
        if (lh != 0 && rh != 0) {
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        }
        else
            return 0;
    }
} //end rbValid




//
//private functions
//

void MovieTree::addNode(MovieNode* newNode, MovieNode* temp) {

    if (newNode->title > temp->title && temp->right != leaf){ //new > temp and temp has a right child
        addNode(newNode, temp->right); //move to right
        return;
    }
    else if (newNode->title < temp->title && temp->left != leaf){ //new < temp and temp has a left child
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
    rbAddFixup(newNode);

    rbValid(root);

    return;

}//end addNode

MovieNode* MovieTree::treeSearch(MovieNode* temp, string title) { //search inorder

    if (title < temp->title && temp->left != leaf) {
        return treeSearch(temp->left, title);
    }
    if (temp->title == title) {
        return temp;
    }
    if (title > temp->title && temp->right != leaf){
        return treeSearch(temp->right, title);
    }
    return NULL;
}//end treeSearch

MovieNode* MovieTree::inorderPrint(MovieNode* temp) {

    if(temp->left != leaf)
        inorderPrint(temp->left);

    cout << "Movie: " << temp->title << " " << temp->quantity << endl;

    if(temp->right != leaf)
        inorderPrint(temp->right);

}

void MovieTree::countNodes(MovieNode* temp, int* c) {

    if(temp->left != leaf)
        countNodes(temp->left, c);

    (*c)++;

    if(temp->right != leaf)
        countNodes(temp->right, c);

}

MovieNode* MovieTree::treeMin(MovieNode* temp) {

    if (temp == NULL)
        return NULL;

    while (temp->left != leaf) {
        temp = temp->left;
    }
    return temp; //returns min value of left subtree

}

void MovieTree::DeleteAll(MovieNode* temp) { //postorder traversal

    if (temp->left != leaf and temp->left != NULL) {
        DeleteAll(temp->left);
    }
    if (temp->right != leaf and temp->right != NULL) {
        DeleteAll(temp->right);
    }
    cout << "Deleting: "<< temp->title << endl;

    delete temp;

}//end DeleteAll

//
//public functions
//

void MovieTree::deleteMovieNode(string title) {

    MovieNode * foundMovie = treeSearch(root, title);

    // If the movie exists
    if (foundMovie != NULL)
    {
        // If it has no children
        if (foundMovie->left == leaf && foundMovie->right == leaf)
        {
            // If this node is the left child, set the parents left child to NULL
            if (foundMovie->parent->left == foundMovie)
                foundMovie->parent->left = leaf;
            // Else, this node is the right child, set that to NULL
            else
                foundMovie->parent->right = leaf;
            // Delete the node
            delete foundMovie;

        }
        // If it only has a left child
        else if (foundMovie->right == leaf)
        {
            if (foundMovie->parent->left == foundMovie)
                foundMovie->parent->left = foundMovie->left;
            else
                 foundMovie->parent->right = foundMovie->left;

            delete foundMovie;

        }
        // If it only has a right child
        else if (foundMovie->left == leaf)
        {
            if (foundMovie->parent->left == foundMovie)
                foundMovie->parent->left = foundMovie->right;
            else
                 foundMovie->parent->right = foundMovie->right;

            delete foundMovie;
        }

        // Node has two children, we need the smallest node from the right child
        else
        {
            // Start on the right sub-tree
            MovieNode * replacementNode = foundMovie->right;

            // search for the smallest left child
            while (replacementNode->left != leaf)
            {
                replacementNode = replacementNode->left;
            }

            // Swap in all the info from the replacement to this node we are "deleting"
            foundMovie->title = replacementNode->title;
            foundMovie->quantity = replacementNode->quantity;
            foundMovie->ranking = replacementNode->ranking;
            foundMovie->year = replacementNode->year;


            // If the replacement node has a right child, update the parent
            if (replacementNode->right != leaf)
                replacementNode->right->parent = replacementNode->parent;

            // If the replacement node is a left child
            if (replacementNode->parent->left == replacementNode)
                replacementNode->parent->left = replacementNode->right;
            // If it is a right child
            else
                replacementNode->parent->right = replacementNode->right;

            // Delete the node
            delete replacementNode;
        }
    }
    // If it doesn't exist
    else
        cout << "Movie not found." << endl;



    /*
    MovieNode* found;
    found = treeSearch(root, title);

    if (found != NULL) {

        //No child
        if (found->right == leaf && found->left == leaf){
            if(found->parent->left == found){
                found->parent->left = leaf;
            }
            else {
                found->parent->right = leaf;
            }
            delete found;
        }
        //One child
        else if(found->right == leaf) {
            MovieNode *x = found->left;
            if (found->parent->right == found){
                found->parent->right = x;
            }
            else {
                found->parent->left = x;
            }
            x->parent = found->parent;
            delete found;
        }
        else if(found->left == leaf) {
            MovieNode *x = found->right;
            if (found->parent->left == found){
                found->parent->left = x;
            }
            else {
                found->parent->right = x;
            }
            x->parent = found->parent;
            delete found;
        }
        //Two child
        else {
            MovieNode* min = treeMin(found->right);

            // If minimum is the right child of toFind
            if(min == found->right) {
                found->parent->left = min;
                min->parent = found->parent;
                min->left = found->left;
                min->left->parent = min;
            }
            else {
                min->parent->left = min->right;
                min->right->parent = min->parent;
                min->parent = found->parent;
                found->parent->left = min;
                min->left = found->left;
                min->right = found->right;
                found->right->parent = min;
                found->left->parent = min;
            }
        }

    }//end outer if
    else {
        cout << "Movie not found." << endl;
    }
    */
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
        found->quantity = found->quantity - 1;
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << found->ranking << endl;
        cout << "Title:" << found->title << endl;
        cout << "Year:" << found->year << endl;
        cout << "Quantity:" << found->quantity << endl;

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
        cout << "Could not open file" << endl; // check if file opens successfully
    }
    else {
        //cout << "Opened file" << endl;
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
            n->left = leaf;
            n->right = leaf;
            MovieNode* temp;

            if (root == NULL) { // !!!possible error: root is never set to anything
                root = n; //add newNode to root
                root->isRed = false;
                root->parent = leaf;
            }
            else {
                temp = root;
                addNode(n, temp); //add node to BST
            }

            //next line
        }//end data
    }//end else

}//end readDataFile
