#include "WordAnalysis.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

WordAnalysis::WordAnalysis(int size) {
    words = new word[size];
    index = 0;
    wordCount = size;
    timesDoubled = 0;
}

WordAnalysis::~WordAnalysis() {}

void WordAnalysis::sortData() {
    //int length = 100*(pow(2, timesDoubled));
    word hold;
    int v;

    for(int i = 0; i < index; i++) {
        v = i;
        while(v > 0 && words[v].count > words[v-1].count) {
            hold = words[v];
            words[v] = words[v-1];
            words[v-1] = hold;
            v--;
        }//end while
    }//end for
}//end insertion sort

void WordAnalysis::doubleArrayAndAdd(string c) {

    //int length = 100*(pow(2, timesDoubled));

    if (index == wordCount-1) { //NO space left in array
        //double array
        word *newArray = new word[wordCount*2];

        for (int i = 0; i < index; i++) {
            newArray[i].w = words[i].w;
            newArray[i].count = words[i].count;
        }

        delete [] words;
        words = newArray;

        wordCount = wordCount*2;
        timesDoubled++;
    }
    word newWord;
    newWord.w = c;
    newWord.count = 1;
    words[index] = newWord;
    index++;

}//end doubleArrayAndAdd

bool WordAnalysis::checkIfCommonWord(string word) {
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
}

void WordAnalysis::printCommonWords(int n) {


  //int length = 100*(pow(2, timesDoubled));

  for (int i = 0; i < n; i++) {
      cout << words[i].count << " - " << words[i].w << endl;
  }

  /*
    int topCount = 0;
    int topIndex = 0;
    int length = 100*(pow(2, timesDoubled));

    for (int j = 0; j < n; j++) {

        topCount = 0;
        topIndex = 0;

        for (int i = 0; i < length; i++) {

                if (words[i].count >= topCount) { //check if the count is bigger than current
                    topIndex = i;
                    topCount = words[i].count;

                }
                else {
                    continue;
                }//end if
        }//end inner for
        cout << words[topIndex].count << " - " << words[topIndex].w << endl;
        words[topIndex].count = 0; //delete values at biggest index so new loop finds next biggest
    } */
}

bool WordAnalysis::readDataFile(char* filename) {
    int totalCount = 0;
    ifstream booktxt;
    //int length;
    bool uniq;

    booktxt.open(filename, ifstream::in); //open the file

    if (booktxt.fail())
    {
        return false; // check if file opens successfully
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
                //length = 100*(pow(2, timesDoubled));
                if (checkIfCommonWord(c)) { // return true means that it is NOT a common word
                    totalCount++;
                    uniq = true;

                    for (int i = 0; i < index; i++) {
                        if (c == words[i].w) {
                            words[i].count = words[i].count + 1;
                            uniq = false;
                            break;
                        }
                    }//end for

                    if (uniq) { //word is unique to array
                        doubleArrayAndAdd(c);
                    }
                }//end if
                else {
                    continue;
                }

            }//end while

        }//end data
    }//end else
    wordCount = totalCount;
    sortData();
    //delete [] words;

}//end readDataFile

int WordAnalysis::getWordCount() {
    return wordCount;
}
int WordAnalysis::getUniqueWordCount() {
    return index;
}
int WordAnalysis::getArrayDoubling() {
    return timesDoubled;
}
