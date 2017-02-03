// Michael Merola
// Assignment 2
// Hoenigman

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct word { // creates struct for a word object

    string txt;
    int counter;

    word()
    {
        txt = "";
        counter = 0;
    }
};

bool spaceCheck(int counter, int length) { //check for space left in array

    if (counter == length-1) {
        return true; //returns NO space left in array
    }
    else {
        return false; //returns YES space left in array
    }

}//end spaceCheck

bool isUncommon(string word) { //checks if a word is common or not

    string commonWords[51] = {"the", "be", "to", "of", "and", "a", "in", "that",
                            "have", "i", "it", "for", "not", "on", "with", "he",
                            "as", "you", "do", "at", "this", "but", "his", "by",
                            "from", "they", "we", "say", "her", "she", "or", "an",
                            "will", "my", "one", "all", "would", "there", "their",
                            "what", "so", "up", "out", "if", "about", "who",
                            "get", "which", "go", "me", ""};

    for (int i = 0; i < 51; i++) {
        if (word == commonWords[i]) {
            return false;
        }
        else {
            continue;
        }
    }//end for

    return true;

}//end isCommon

int isUniq(word **arr, string word, int length) { //checks if a word is already in array
    int index = 0;

    for (int i = 0; i < length; i++) {
        if (word == (*arr)[i].txt) {
            return i; //if word is in array, returns index
        }
    }//end for

    return -1; //otherwise, return invalid

}//end isUniq

void doubleArray (word **oldArr, int length) { //array doubling algorithm

    //create a new array that is double the length of first array
    word *newArray = new word[length*2];

    for(int i = 0; i < length; i++){
    newArray[i].txt = (*oldArr)[i].txt;
    newArray[i].counter = (*oldArr)[i].counter;
    }

    delete [] (*oldArr);
    (*oldArr) = newArray;

}//end doubleArray

int main(int argc, char *argv[]) {

    // initiate variables
    string filename;
    int uniqCounter = 0;
    int totalCounter = 0;
    int doubleCounter = 0;
    int n;

    word *allWords = new word[100]; //create array of word structs
    int arrLength = 100;

    ifstream booktxt;

    //assign values from command line
    filename = argv[1];
    n = stoi(argv[2]);

    booktxt.open(filename, ifstream::in); //open the file

    if (booktxt.fail())
    {
        cout << "Something bad happened" << endl; // check if file opens successfully
    }
    else
    {
        string line;
        int j = 0;

        while (getline(booktxt, line))//run through all lines of data
        {
            stringstream ss(line);
            string c;

            while (getline(ss, c, ' ')) //check through each element (c) in the line
            {
                if (spaceCheck(j, arrLength)) { //checks if there is space left in array

                    doubleArray(&allWords, arrLength);
                    doubleCounter++;
                    arrLength = arrLength*2;//track exact length
                }

                if (isUncommon(c)) { //checks if word is not on common list

                    totalCounter++;
                    int uniqIndex = isUniq(&allWords, c, arrLength); //checks if word exists already in array

                    if (uniqIndex == -1) { // -1 : word is unique to array
                        allWords[j].txt = c;
                        allWords[j].counter += 1;
                        uniqCounter++;
                        j++;

                    }
                    else { // otherwise, the number is the index where the word is found in the array
                        allWords[uniqIndex].counter += 1;

                    }

                } //end uncommon word
                else {
                    continue;
                } //end common word

            }//end while

        }//end data
    }//end else

    //algorithm to find top words in array n number of times
    int topCount = 0;
    int topIndex = 0;

    for (int j = 0; j < n; j++) {

        topCount = 0;
        topIndex = 0;

        for (int i = 0; i < arrLength; i++) {

                if (allWords[i].counter >= topCount) { //check if the count is bigger than current
                    topIndex = i;
                    topCount = allWords[i].counter;

                }
                else {
                    continue;
                }//end if
        }//end inner for
        cout << allWords[topIndex].counter << " - " << allWords[topIndex].txt << endl;
        allWords[topIndex].counter = 0; //delete values at biggest index so new loop finds next biggest

    }//end outer for


    cout << "#" << endl;
    cout<<"Array doubled: "<<doubleCounter<<endl;
    cout << "#" << endl;
    cout<<"Unique non-common words: "<<uniqCounter<<endl;
    cout << "#" << endl;
    cout<<"Total non-common words:"<<totalCounter<<endl;




    return 0;

}//end main()
