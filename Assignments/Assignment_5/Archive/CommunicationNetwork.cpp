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
    right = temp->next;

    add = new City(cityNew, NULL, NULL, "");

    if (cityPrevious == "First") { //check if user adds city to head of list
        head = add;
        head->next = temp;
        temp->previous = head;
    }//end if
    else {
        while (flag != true) {
            if (temp->cityName == cityPrevious && temp == tail) { //check if city is tail
                temp->next = add;
                add->previous = temp;

                tail = add;
                flag = true;
            }
            else if (temp->cityName == cityPrevious){ //found city
                temp->next = add;
                add->previous = temp;

                right->previous = add;
                add->next = right;

                flag = true;
            }
            else {
                temp = temp->next;
                right = right->next;
            }

        }//end while
    }//end else

}//end addCity

void CommunicationNetwork::buildNetwork () {
    //initializes variables and sets next values
    City *bos = new City("Boston", NULL, NULL, "");
    City *ny = new City("New York", bos, NULL, "");
    City *dc = new City("Washington, D.C.", ny, NULL, "");
    City *atl = new City("Atlanta", dc, NULL, "");
    City *chi = new City("Chicago", atl, NULL, "");
    City *stl = new City("St. Louis", chi, NULL, "");
    City *dal = new City("Dallas", stl, NULL, "");
    City *den = new City("Denver", dal, NULL, "");
    City *pho = new City("Phoenix", den, NULL, "");
    City *la = new City("Los Angeles", pho, NULL, "");

    head = la;
    tail = bos;
    City *temp = head;
    City *last;

    //set all network previous values
    while (temp != NULL) {

        if (temp == head) {
            temp->previous = NULL;
            last = temp;
            temp = temp->next;
        }
        else {
            temp->previous = last;
            last = temp;
            temp = temp->next;
        }
    }//end while


    //print path
    printNetwork();

}//end buildNetwork

void CommunicationNetwork::send (string word) {

    City *send;
    City *recv;

    //check for empty linked list
    if (head != NULL) {
        send = head;
        send->message = word;
    }
    else {
        send = NULL;
    }

    //send message to coast
    while (send != NULL) {
        if (send == tail) { //checks if message reached the tail
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

    //send message back
    send = tail;
    recv = tail->previous;

    while (recv != NULL) {
        if (recv == head) {//checks if message reached the head
            recv->message = send->message;
            cout << recv->cityName << " received " << recv->message << endl;
            recv = NULL;
            send = NULL;
        }
        else {
            recv->message = send->message;
            cout << recv->cityName << " received " << recv->message << endl;
            recv = recv->previous;
            send = send->previous;
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
    else if (head == NULL) {
        cout << "Empty list" << endl;
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

    if (head != NULL) {
        City *temp = head;
        bool flag = false;
        cout << "===CURRENT PATH===" << endl;
        cout << "NULL <- " ;
        while (flag != true) {
            if (temp == tail) {
                cout << temp->cityName << " -> NULL" << endl;
                flag = true;
            }
            else {
                cout << temp->cityName << " <-> " ;
                temp = temp->next;
            }
        }//end while
        cout << "==================" <<	endl;
    }
    else {
        cout << "===CURRENT PATH===" << endl;
        cout << "NULL" << endl;
        cout << "==================" <<	endl;

    }

}//end printNetwork

void CommunicationNetwork::deleteCity(string cityName) {

    City *temp;
    City *right;
    City *del;

    temp = head;
    del = NULL;

    while (temp != NULL) { //find city to delete
        if (temp->cityName == cityName) {
            del = temp;
            break;
        }
        temp = temp->next;
    }

    if (del == head) { //delete head value
        head = head->next;
        head->previous = NULL;
        delete del;
    }
    else if (del == tail){ //delete tail value
        tail = tail->previous;
        tail->next = NULL;
        delete del;
    }
    else if (del == NULL) { //city did not exist
        cout << cityName <<"not found" << endl;
    }
    else { //delete middle value
        del->previous->next = del->next;
        del->next->previous = del->previous;
        delete del;
    }

}//end deleteCity

void CommunicationNetwork::clearNetwork() {

    City *temp;
    City *right;

    temp = head;
    right = NULL;

    while (temp != NULL) {
        right = temp->next;
        cout << "deleting " << temp->cityName << endl;
        delete temp;
        temp = right;
    }

    head = NULL;
    tail = NULL;

}//end deleteNetwork
