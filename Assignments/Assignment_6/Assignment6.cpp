#include "Queue.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

string printMenu() {
    string input;

    cout <<	"======Main Menu======"	<< endl;
    cout <<	"1. Enqueue word" << endl;
    cout <<	"2. Dequeue word"	<< endl;
    cout <<	"3. Print queue" << endl;
    cout <<	"4. Enqueue sentence" << endl;
    cout <<	"5. Quit" << endl;

    getline(cin,input);

    return input;
}


int main(int argc, char* argv[]) {

    //instantiate class object
    Queue Q(8);

    //relevant variables
    bool quit = false;
    string userInput;
    char* filename = argv[1];
    string word;
    string sentence;

    //change string input to integers for COG
    map <string, int> input;
    input ["1"] = 1;
    input ["2"] = 2;
    input ["3"] = 3;
    input ["4"] = 4;
    input ["5"] = 5;


    while(quit != true) { //reprints the menu until the user chooses to quit
        userInput = printMenu(); //prints menu and recieves user input

        switch(input[userInput]) {
            case 1:
                cout << "word: ";
                getline(cin, word);
                Q.enqueue(word);
                break;
            case 2:
                Q.dequeue();
                break;
            case 3:
                Q.printQueue();
                break;
            case 4:
                cout << "sentence: ";
                getline(cin, sentence);
                Q.enqSent(sentence);
                break;
            case 5:
                quit = true;
                break;
        }//end switch

    }//end while

    cout <<	"Goodbye!" << endl;


    return 0;
}//end main
