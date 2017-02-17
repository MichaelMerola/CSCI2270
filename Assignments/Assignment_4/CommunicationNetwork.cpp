#include "CommunicationNetwork.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

CommunicationNetwork::CommunicationNetwork () {
    //head = NULL;
    //tail = NULL;

}//end constructor

CommunicationNetwork::~CommunicationNetwork () {}

void CommunicationNetwork::addCity (string cityNew, string cityPrevious) {

    City *temp;
    City *right;
    City *add;
    bool flag = false;

    temp = head;
    add = new City(cityNew, NULL, "");

    while (flag != true) {
        if (temp->cityName == cityPrevious && temp == tail) {
            temp->next = add;
            tail = add;
            flag = true;
        }
        else if (temp->cityName == cityPrevious){
            right = temp->next;
            temp->next = add;
            add->next = right;
            flag = true;
        }
        else {
            temp = temp->next;
        }
    }//end while

}//end addCity

void CommunicationNetwork::buildNetwork () {

    City *bos = new City("Boston", NULL, "");
    City *ny = new City("New York", bos, "");
    City *dc = new City("Washington, D.C.", ny, "");
    City *atl = new City("Atlanta", dc, "");
    City *chi = new City("Chicago", atl, "");
    City *stl = new City("St. Louis", chi, "");
    City *dal = new City("Dallas", stl, "");
    City *den = new City("Denver", dal, "");
    City *pho = new City("Phoenix", den, "");
    City *la = new City("Los Angeles", pho, "");

    head = la;
    tail = bos;
    City *temp = head;

    //print path
    cout << "===CURRENT PATH===" << endl;
    while (temp != NULL) {
        cout << temp->cityName << " -> " ;
        temp = temp->next;
        if (temp == NULL)
            cout << "NULL" << endl;
    }
    cout << "==================" <<	endl;

}//end buildNetwork

void CommunicationNetwork::send (string word) {

    City *send;
    City *recv;

    if (head != NULL) {
        send = head;
        send->message = word;
    }
    else {
        send = NULL;
        cout << "Empty list" << endl;
    }

    while (send != NULL) {
        if (send == tail) {
            cout << send->cityName << " received " << send->message << endl;
            recv = NULL;
            send = NULL;
        }
        else {
            recv = send->next;
            cout << send->cityName << " received " << send->message << endl;
            recv->message = send->message;
            send = send->next;
        }
    }//end while

}//end send

void CommunicationNetwork::transmitMsg (char * fname) {

    ifstream msg;
    string filename = fname; //**build command line argument

    msg.open(filename, ifstream::in); //open the file

    if (msg.fail()) {
        cout << "something went wrong.." << endl; // check if file opens successfully
    }
    else {
        string line;
        int j = 0;

        while (getline(msg, line)) {//run through all lines of data

            stringstream ss(line);
            string word;

            while (getline(ss, word, ' ')) { //check through each element (word) in the line

                //**send each word from the file from LA through Boston
                send(word);

            }//end while
        }//end outer while
    }//end else
}//end transmitMsg

void CommunicationNetwork::printNetwork () {
    City *temp = head;

    cout << "===CURRENT PATH===" << endl;
    while (temp != NULL) {
        cout << temp->cityName << " -> " ;
        temp = temp->next;
        if (temp == NULL)
            cout << "NULL" << endl;
    }
    cout << "==================" <<	endl;
}//end printNetwork
