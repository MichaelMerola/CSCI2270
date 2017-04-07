#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <iostream>
#include <string>

using namespace std;

struct MovieNode{
    int ranking;
    string title;
    int year;
    int quantity;
    bool isRed;

    MovieNode* parent;
    MovieNode* left;
    MovieNode* right;

    MovieNode(){};

    MovieNode(int in_ranking, string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;

        parent = NULL;
        left = NULL;
        right = NULL;
        isRed = true;
    }

};

class MovieTree
{

    public:
        MovieTree();
        virtual ~MovieTree();
        void printMovieInventory();
        void countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);

        bool isValid();
        int countLongestPath();

        void readDataFile(char* filename);

    protected:

    private:
        void DeleteAll(MovieNode* temp); //use this for the post-order traversal deletion of the tree
        void printMovieInventory(MovieNode* node);
        void countNodes(MovieNode* temp, int* c);
        MovieNode* treeSearch(MovieNode* temp, std::string title);
        MovieNode* treeMin(MovieNode* temp);

        void addNode(MovieNode* newNode, MovieNode* temp);
        MovieNode* inorderPrint(MovieNode* temp);

        void rbAddFixup(MovieNode * node); //called after insert to fix tree
        void leftRotate(MovieNode * x); //rotate the tree left with x as the root of the rotation
        //void rbDelete(MovieNode * z); //delete a node. Call this from deleteMovieNode, the actual delete functionality happens here.
        void rightRotate(MovieNode * x); //rotate the tree right with x as the root of the rotation
        void rbDeleteFixup(MovieNode * node); //called after delete to fix the tree
        void rbTransplant(MovieNode * u, MovieNode * v); //replace node u in tree with node v. Your solution doesn't necessarily need to use this method
        int rbValid(MovieNode * node); //check if the tree is valid, with node as the root of the trees
        int rcountLongPath(MovieNode *temp); //longest path from node to a leaf node in the tree

        MovieNode* root;
        MovieNode* leaf;
};

#endif //MOVIETREE_H
