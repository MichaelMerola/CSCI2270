#include "WordAnalysis.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

WordAnalysis::WordAnalysis(int size) {
    words = new word[size];
    index = 0;
    wordCount = 0;
    timesDoubled = 0;
}

WordAnalysis::~WordAnalysis() {}

void WordAnalysis::sortData() {

}

void WordAnalysis::doubleArrayAndAdd(string c) {

    int length = 100*(pow(2, timesDoubled));

    if (index == length-1) { //NO space left in array
      //double array
      word *newArray = new word[length*2];

      for(int i = 0; i < length; i++) {
      newArray[i].w = words[i].w;
      newArray[i].count = words[i].count;
      }

      delete [] words;
      words = newArray;

      timesDoubled++;
    }
    words[index].w = c;
    words[index].count += 1;
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

bool WordAnalysis::readDataFile(char* filename) {

    ifstream booktxt;
    int length;

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
                length = 100*(pow(2, timesDoubled));
                if (checkIfCommonWord(c)) {
                    wordCount++;
                    int uniqIndex;

                    for (int i = 0; i < length; i++) {
                        if (c == words[i].w) {
                            uniqIndex = i; //if word is in array, returns index
                            break;
                        }
                        uniqIndex = -1; //otherwise, return invalid
                    }//end for

                    if (uniqIndex == -1) { // -1 : word is unique to array
                        doubleArrayAndAdd(c);
                    }
                    else { // otherwise, the number is the index where the word is found in the array
                        words[uniqIndex].count += 1;
                    }
                }//end if
                else {
                    continue;
                }

            }//end while

        }//end data
    }//end else

}//end readDataFile

void WordAnalysis::printCommonWords(int n) {
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
    }
}

int WordAnalysis::getWordCount() {
    delete words;

    return wordCount;
}
int WordAnalysis::getUniqueWordCount() {
    return index;
}
int WordAnalysis::getArrayDoubling() {
    return timesDoubled;
}
