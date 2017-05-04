#include "HashTable.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

HashTable::HashTable(int size) {

    tableSize = size;
    playerDataChain.resize(tableSize);
    playerDataOpen.resize(tableSize);

}//end constructor

HashTable::~HashTable() {}

//
////functions
//

int HashTable::hashFunction (player* p) {

    int firstSum = 1;
    int lastSum = 1;
    int year = p->yearBorn;

    int total = 0;
    int index;

    for (char& c : p->firstName) { //multiply all of the ASCII values of first name
        firstSum = firstSum*c;
    }
    for (char& c : p->lastName) { //multiply all of the ASCII values of last name
        lastSum = lastSum*c;
    }

    total = firstSum + lastSum + year;

    index = total % tableSize;
    return abs(index);

}//end hashFunction

void HashTable::queryHashTable(string firstName, string lastName, int birthYear) {

    bool found = false;

    player* query = new player;
    query->firstName = firstName;
    query->lastName = lastName;
    query->yearBorn = birthYear;

    int hashKey = hashFunction(query);

    player* temp = playerDataChain[hashKey];

    if (playerDataChain[hashKey] != NULL) {
        while (temp->next != NULL) {

            if (temp->firstName == firstName && temp->lastName == lastName && temp->yearBorn == birthYear) {
                cout << "==== PLAYER DATA ====" << endl;
                cout << "First Name: " << firstName << endl;
                cout << "Last Name: " << lastName << endl;
                cout << "Birth Year: " << birthYear << endl;
                cout << "Birth Country: " << temp->countryBorn << endl;
                cout << "Weight: " << temp->weight << endl;
                cout << "Height: " << temp->height << endl;
                cout << "Bats: " << temp->bats << endl;
                cout << "Throws: " << temp->throws << endl;
                cout << endl;

                cout << "==== CAREER ====" << endl;
                for (size_t i = 0; i != (temp->career.size()); i++) {
                    cout << temp->career[i]->year << ", ";
                    cout << temp->career[i]->team << ", ";
                    cout << temp->career[i]->league << ", ";
                    cout << temp->career[i]->salary << endl;
                }

                found = true;
            }

            temp = temp->next;
        }
    }//end if
    if (found == false) {
        cout << "Could not find player" << endl;
    }
}//end queryHashTable


void HashTable::readDataFileChain(char* filename) {

    //counters
    int chainColls = 0;
    int chainSearchOps = 0;

    ifstream playerData;
    playerData.open(filename, ifstream::in); //open the file

    if (playerData.fail()) {
        cout << "Could not open file" << endl; // check if file opens successfully
    }
    else {
        //relevant variables
        string line; //holds string of line
        string c; //holds each element of line
        int hashKey;

        int year;
        string team;
        string league;
        int salary;

        int row = 0; //line counter
        int index; //word counter

        while (getline(playerData, line)) { //run through all lines of data

            stringstream ss(line);
            index = 0;
            player* newPlayer = new player;

            while (getline(ss, c, ',')) { //check through each element (c) in the line
                if (row != 0) {

                    switch (index) {

                        case 0: //year
                            year = stoi(c);
                            break;

                        case 1: //teamID
                            team = c;
                            break;

                        case 2: //leagueID
                            league = c;
                            break;

                        case 3: //playerID
                            newPlayer->playerID = c;
                            break;

                        case 4: //salary
                            salary = stoi(c);
                            break;

                        case 5: //firstName
                            newPlayer->firstName = c;
                            break;

                        case 6: //lastName
                            newPlayer->lastName = c;
                            break;

                        case 7: //birthYear
                            newPlayer->yearBorn = stoi(c);
                            break;

                        case 8: //birthCountry
                            newPlayer->countryBorn = c;
                            break;

                        case 9: //weight
                            newPlayer->weight = stoi(c);
                            break;

                        case 10: //height
                            newPlayer->height = stoi(c);
                            break;

                        case 11: //bats
                            newPlayer->bats = c;
                            break;

                        case 12: //throws
                            newPlayer->throws = c;
                            break;

                        default:
                            break;

                    }//end switch

                }//end row check
                index++;
            }//end while inner

            if (row != 0) {

                hashKey = hashFunction(newPlayer); //?? possible pointer error

                if (playerDataChain[hashKey] == NULL) {

                    playerDataChain[hashKey] = newPlayer;

                    playerDataChain[hashKey]->career[0] = new careerData(year, team, league, salary);
                    playerDataChain[hashKey]->carIndex += 1;
                }
                else { //CHAINING IMPLEMENTATION
                    chainColls++;

                    bool found = false;
                    player* temp = playerDataChain[hashKey];

                    if (temp->playerID == newPlayer->playerID && temp->yearBorn == newPlayer->yearBorn) {
                        //check if the player already exists at this hashKey
                        //cout << "already exists" << endl;
                        found = true;
                    }
                    else {
                        while (temp->next != NULL) {
                            if (temp->playerID == newPlayer->playerID && temp->yearBorn == newPlayer->yearBorn) {
                                found = true;
                                break;
                            }
                            temp = temp->next;
                            chainSearchOps++;
                        }//end while
                    }

                    //cout << found << endl;

                    if (found == true) { //clone player

                        temp->career[newPlayer->carIndex] = new careerData(year, team, league, salary);
                        temp->carIndex += 1;
                    }
                    else { //unique player
                        temp->next = newPlayer;

                        newPlayer->career[newPlayer->carIndex] = new careerData(year, team, league, salary);
                        newPlayer->carIndex += 1;
                    }


                }//end CHAINING IMPLEMENTATION
            }//end row check

            row++; //move to next row
        }//end while
    }//end else

    cout << "Hash Table Size: " << tableSize << endl;
    cout << "Collisions using chaining: " << chainColls << endl;
    cout << "Search operations using chaining: " << chainSearchOps << endl;


}//end readDataFile for Chaining

void HashTable::readDataFileOpen(char* filename) {

    //counters
    int openColls = 0;
    int openSearchOps = 0;

    ifstream playerData;
    playerData.open(filename, ifstream::in); //open the file

    if (playerData.fail()) {
        cout << "Could not open file" << endl; // check if file opens successfully
    }
    else {
        //relevant variables
        string line; //holds string of line
        string c; //holds each element of line
        int hashKey;

        int year;
        string team;
        string league;
        int salary;

        int row = 0; //line counter
        int index; //word counter

        while (getline(playerData, line)) { //run through all lines of data

            stringstream ss(line);
            index = 0;
            player* newPlayer = new player;

            while (getline(ss, c, ',')) { //check through each element (c) in the line
                if (row != 0) {

                    switch (index) {

                        case 0: //year
                            year = stoi(c);
                            break;

                        case 1: //teamID
                            team = c;
                            break;

                        case 2: //leagueID
                            league = c;
                            break;

                        case 3: //playerID
                            newPlayer->playerID = c;
                            break;

                        case 4: //salary
                            salary = stoi(c);
                            break;

                        case 5: //firstName
                            newPlayer->firstName = c;
                            break;

                        case 6: //lastName
                            newPlayer->lastName = c;
                            break;

                        case 7: //birthYear
                            newPlayer->yearBorn = stoi(c);
                            break;

                        case 8: //birthCountry
                            newPlayer->countryBorn = c;
                            break;

                        case 9: //weight
                            newPlayer->weight = stoi(c);
                            break;

                        case 10: //height
                            newPlayer->height = stoi(c);
                            break;

                        case 11: //bats
                            newPlayer->bats = c;
                            break;

                        case 12: //throws
                            newPlayer->throws = c;
                            break;

                        default:
                            break;

                    }//end switch

                }//end row check
                index++;
            }//end while inner

            if (row != 0) {

                hashKey = hashFunction(newPlayer); //?? possible pointer error

                if (playerDataOpen[hashKey] == NULL) {

                    playerDataOpen[hashKey] = newPlayer;

                    playerDataOpen[hashKey]->career[0] = new careerData(year, team, league, salary);
                    playerDataOpen[hashKey]->carIndex += 1;
                }
                else { //OPEN IMPLEMENTATION
                    openColls++;
                    bool openSpotFound = false;

                    for (int k = hashKey + 1; k < tableSize and !openSpotFound; k++) {
                        if (playerDataOpen[k] == NULL) {
                            playerDataOpen[k] = newPlayer;
                            playerDataOpen[k]->career[0] = new careerData(year, team, league, salary);
                            playerDataOpen[k]->carIndex += 1;
                            openSpotFound = true;
                        }
                        openSearchOps++;
                    }

                    if (!openSpotFound) {
                        for (int j = 0; j < hashKey and !openSpotFound; j++) {
                            if (playerDataOpen[j] == NULL) {
                                playerDataOpen[j] = newPlayer;
                                playerDataOpen[j]->career[0] = new careerData(year, team, league, salary);
                                playerDataOpen[j]->carIndex += 1;
                                openSpotFound = true;
                            }
                            openSearchOps++;
                        }
                    }
                }//end OPEN IMPLEMENTATION
            }//end row check

            row++; //move to next row
        }//end while
    }//end else
    
    cout << "Collisions using open addressing: " << openColls << endl;
    cout << "Search operations using open addressing: " << openSearchOps << endl;


}
