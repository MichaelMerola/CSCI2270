#include "CommunicationNetwork.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>

using namespace std;

string printMenu() {
    string input;

    cout <<	"======Main Menu======"	<< endl;
    cout <<	"1. Build Network" << endl;
    cout <<	"2. Print Network Path"	<< endl;
    cout <<	"3. Transmit Message Coast-To-Coast-To-Coast" << endl;
    cout <<	"4. Add City" << endl;
    cout <<	"5. Delete City" << endl;
    cout <<	"6. Clear Network" << endl;
    cout <<	"7. Quit" << endl;

    getline(cin,input);

    return input;
}

int main(int argc, char* argv[]) {
    //instantiate class object
    CommunicationNetwork CN;

    //relevant variables
    bool quit = false;
    string userInput;
    char* filename = argv[1];
    string cityNew;
    string cityPrevious;
    string cityDel;

    map <string, int> input;
    input ["1"] = 1;
    input ["2"] = 2;
    input ["3"] = 3;
    input ["4"] = 4;
    input ["5"] = 5;
    input ["6"] = 6;
    input ["7"] = 7;


    while(quit != true) { //reprints the menu until the user chooses to quit
        userInput = printMenu(); //prints menu and recieves user input

        switch(input[userInput]) {
            case 1:
                CN.buildNetwork();
                break;
            case 2:
                CN.printNetwork();
                break;
            case 3:
                CN.transmitMsg(filename);
                break;
            case 4:
                cout << "Enter a city name: " << endl;
                getline(cin,cityNew);

                cout <<	"Enter a previous city name: " << endl;
                getline(cin,cityPrevious);

                CN.addCity(cityNew, cityPrevious);
                break;
            case 5:
                cout << "Enter a city name: " << endl;
                getline(cin,cityDel);

                CN.deleteCity(cityDel);
                break;
            case 6:
                CN.clearNetwork();
                break;
            case 7:
                quit = true;
                break;
        }//end switch

    }//end while

    cout <<	"Goodbye!" << endl;
    CN.clearNetwork();

    return 0;
}//end main
