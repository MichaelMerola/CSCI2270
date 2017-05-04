#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<vector>
#include<iostream>

using namespace std;

struct careerData {
    int year;
    string team;
    string league;
    int salary;
    bool empty = false;
}

struct player {

    string firstName;
    string lastName;
    int playerID;
    int yearBorn;
    string countryBorn;
    int weight;
    int height;
    string bats;
    string throws;

    careerData career[100];
};

class HashTable
{
    public:
        HashTable(int size);
        HashTable();
        ~HashTable();

        void readDataFileChain(char* filename);
        void readDataFileOpen(char* filename);


    protected:
    private:
        int tableSize;
        vector<player> playerDataChain;
        vector<player> playerDataOpen;

        int hashFunction(player p);

};


#endif //HASHTABLE_H
