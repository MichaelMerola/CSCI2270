#include "Graph.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

string printMenu() {
    string input;

    cout <<	"======Main Menu======"	<< endl;
    cout <<	"1. Print vertices" << endl;
    cout <<	"2. Find districts" << endl;
    cout <<	"3. Find shortest path" << endl;
    cout <<	"4. Quit" << endl;

    getline(cin,input);

    return input;
}

int main(int argc, char* argv[]) {

    //instantiate class object
    Graph<string> gt;
    char* filename = argv[1];

    //read all data from txt file
    gt.readDataFile(filename);

    //relevant variables
    bool quit = false;
    string userInput;

    //change string input to integers for COG
    map <string, int> input;
    input ["1"] = 1;
    input ["2"] = 2;
    input ["3"] = 3;
    input ["4"] = 4;

    while(quit != true) { //reprints the menu until the user chooses to quit
        userInput = printMenu(); //prints menu and recieves user input

        switch(input[userInput]) {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                quit = true;
                break;
        }//end switch

    }//end while

    cout <<	"Goodbye!" << endl;

    return 0;
}//end main
