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
    bool full;

    careerData() {}

    careerData(int y, string t, string l, int s) {
        year = y;
        team = t;
        league = l;
        salary = s;

        full = false;
    }
};

struct player {

    string firstName;
    string lastName;
    string playerID;
    int yearBorn;
    string countryBorn;
    int weight;
    int height;
    string bats;
    string throws;

    vector <careerData*> career;
    int carIndex;
    player* next; //chaining implementation

    player() {
        next = NULL;
        carIndex = 0;
        career.resize(1);
    }
};

class HashTable {

    public:
        HashTable(int size);
        HashTable();
        ~HashTable();

        void readDataFileChain(char* filename);
        void readDataFileOpen(char* filename);

        void queryHashTable(string firstName, string lastName, int birthYear);


    protected:
    private:
        int tableSize;
        vector<player*> playerDataChain;
        vector<player*> playerDataOpen;

        int hashFunction(player* p);

};


#endif //HASHTABLE_H
