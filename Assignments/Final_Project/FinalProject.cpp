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
    char* filename = argv[1];
    string tableSize = argv[2];

    //read all data from txt file
    HashTable ht(stoi(tableSize));
    ht.readDataFileChain(filename);
    ht.readDataFileOpen(filename);

    //relevant variables
    bool quit = false;
    string firstName;
    string lastName;
    string birthYear;

    //change string input to integers for COG
    map <string, int> input;
    input ["1"] = 1;
    input ["2"] = 2;

    while(quit != true) { //reprints the menu until the user chooses to quit
        string userInput = printMenu(); //prints menu and recieves user input

        switch(input[userInput]) {
            case 1:
                cout << "Enter first name: ";
                getline(cin, firstName);
                cout << "Enter last name: ";
                getline(cin, lastName);
                cout << "Enter birth year: ";
                getline(cin, birthYear);

                ht.queryHashTable(firstName, lastName, stoi(birthYear));
                break;
            case 2:
                quit = true;
                break;
        }//end switch

    }//end while

    cout <<	"Goodbye!" << endl;

    return 0;
}//end main
