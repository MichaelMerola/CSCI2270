#include "HashTable.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

HashTable::HashTable(int size) {

    tableSize = size;

}//end constructor

HashTable::~HashTable() {}

//
////functions
//

int HashTable::hashFunction (player p) {

    int firstSum = 1;
    int lastSum = 1;
    int dataSum = 1;

    int total = 0;
    int index;

    for (char& c : p.firstName) { //multiply all of the ASCII values of first name
        firstSum = firstSum*c;
    }
    for (char& c : p.lastName) { //multiply all of the ASCII values of last name
        lastSum = lastSum*c;
    }

    dataSum = p.yearBorn * (p.weight + p.height);
    total = firstSum + lastSum + dataSum;

    index = total % tableSize;
    return index;

}//end hashFunction

void HashTable::readDataFileChain(char* filename) {

    ifstream playerData;
    playerData.open(filename, ifstream::in); //open the file

    if (playerData.fail()) {
        cout << "Could not open file" << endl; // check if file opens successfully
    }
    else {
        //relevant variables
        string line; //holds string of line
        string c; //holds each element of line

        player newPlayer;

        int row = 0; //line counter
        int index; //word counter

        while (getline(playerData, line)) { //run through all lines of data

            stringstream ss(line);
            index = 0;

            while (getline(ss, c, ',')) { //check through each element (c) in the line
                if (row != 0) {



                    switch (index) {

                        case 0: //year
                            //TODO: career data
                            break;

                        case 1: //teamID
                            //TODO: career data
                            break;

                        case 2: //leagueID
                            //TODO: career data
                            break;

                        case 3: //playerID
                            newPlayer.playerID = stoi(c);
                            break;

                        case 4: //salary
                            //TODO: career data
                            break;

                        case 5: //firstName
                            newPlayer.firstName = c;
                            break;

                        case 6: //lastName
                            newPlayer.lastName = c;
                            break;

                        case 7: //birthYear
                            newPlayer.birthYear = stoi(c);
                            break;

                        case 8: //birthCountry
                            newPlayer.birthCountry = c;
                            break;

                        case 9: //weight
                            newPlayer.weight = stoi(c);
                            break;

                        case 10: //height
                            newPlayer.height = stoi(c);
                            break;

                        case 11: //bats
                            newPlayer.bats = c;
                            break;

                        case 12: //throws
                            newPlayer.throws = c;
                            break;

                        default:
                            break;

                    }//end switch



                }//end row check
            }//end while inner

            row++; //move to next row
        }//end while
    }//end else

}//end readDataFile for Chaining
