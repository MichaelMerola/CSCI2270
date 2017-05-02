#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

string printMenu() {
    string input;

    cout <<	"======Main Menu======"	<< endl;
    cout <<	"1. Query Hash Table" << endl;
    cout <<	"2. Quit" << endl;

    getline(cin,input);

    return input;
}

int main(int argc, char* argv[]) {

    //instantiate class object
    //TODO: Graph<string> gt;
    char* filename = argv[1];

    //read all data from txt file
    //TODO:gt.readDataFile(filename);

    //relevant variables
    bool quit = false;

    //change string input to integers for COG
    map <string, int> input;
    input ["1"] = 1;
    input ["2"] = 2;

    while(quit != true) { //reprints the menu until the user chooses to quit
        userInput = printMenu(); //prints menu and recieves user input

        switch(input[userInput]) {
            case 1:

                break;
            case 2:
                quit = true;
                break;
        }//end switch

    }//end while

    cout <<	"Goodbye!" << endl;

    return 0;
}//end main
