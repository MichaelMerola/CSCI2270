#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <iostream>

using namespace std;

struct MovieNode{
    int ranking;
    std::string title;
    int year;
    int quantity;

    MovieNode* parent;
    MovieNode* left;
    MovieNode* right;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;

        parent = NULL;
        left = NULL;
        right = NULL;
    }

};

class MovieTree
{

    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        void countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);

        void readDataFile(char* filename);

    protected:

    private:
        void DeleteAll(MovieNode* temp); //use this for the post-order traversal deletion of the tree
        void printMovieInventory(MovieNode* node);
        void countNodes(MovieNode* temp, int* c);
        //MovieNode* search(std::string title);
        MovieNode* treeSearch(MovieNode* temp, std::string title);
        MovieNode* treeMin(MovieNode* temp);
        MovieNode* root;

        void addNode(MovieNode* newNode, MovieNode* temp);
        MovieNode* inorderPrint(MovieNode* temp);
};

#endif //MOVIETREE_H
