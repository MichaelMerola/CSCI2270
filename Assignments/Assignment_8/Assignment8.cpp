#include "MovieTree.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

string printMenu() {
    string input;

    cout <<	"======Main Menu======"	<< endl;
    cout <<	"1. Find a movie" << endl;
    cout <<	"2. Rent a movie"	<< endl;
    cout <<	"3. Print the inventory" << endl;
    cout <<	"4. Delete a movie" << endl;
    cout <<	"5. Count the movies" << endl;
    cout <<	"6. Quit" << endl;

    getline(cin,input);

    return input;
}


int main(int argc, char* argv[]) {

    //instantiate class object
    MovieTree mt;
    char* filename = argv[1];

    //read all data from txt file
    mt.readDataFile(filename);

    //relevant variables
    bool quit = false;
    string userInput;
    string title;

    //change string input to integers for COG
    map <string, int> input;
    input ["1"] = 1;
    input ["2"] = 2;
    input ["3"] = 3;
    input ["4"] = 4;
    input ["5"] = 5;
    input ["6"] = 6;


    while(quit != true) { //reprints the menu until the user chooses to quit
        userInput = printMenu(); //prints menu and recieves user input

        switch(input[userInput]) {
            case 1:
                cout << "Enter title:" << endl;
                getline(cin, title);
                mt.findMovie(title);
                break;
            case 2:
                cout << "Enter title:" << endl;
                getline(cin, title);
                mt.rentMovie(title);
                break;
            case 3:
                mt.printMovieInventory();
                break;
            case 4:
                cout << "Enter title:" << endl;
                getline(cin, title);
                mt.deleteMovieNode(title);
                break;
            case 5:
                mt.countMovieNodes();
                break;
            case 6:
                quit = true;
                break;
        }//end switch

    }//end while

    cout <<	"Goodbye!" << endl;


    return 0;
}//end main
