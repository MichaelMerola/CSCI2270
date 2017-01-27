#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct message {

    string type;
    bool sale; //true=="for sale" , false=="wanted"
    int price;

    message()
    {
        type = "";
        sale = false;
        price = 0;
    }
};

void printMessageBoard (int index, message Board[]) {
    string sale;

    for (int i = 0; i < index; i++) {
        if (Board[i].sale == true) {
            sale = "for sale";
        }
        else {
            sale = "wanted";
        }
        cout << Board[i].type << ", " << sale << ", " << Board[i].price << endl;
    }

}//end printMessageBoard

int main() {
    string filename;
    int fileCounter = 0;
    int searchCounter = 0;
    int shiftCounter = 0;
    int index;

    message Board[100]; //create array of message structs

    ifstream boardData;

    cin >> filename;

    boardData.open(filename, ifstream::in); //open the file

    if (boardData.fail())
    {
        cout << "Something bad happened" << endl; // check if file opens successfully
    }
    else
    {
        string line;
        index = 0;
        int j = 0;

        while (getline(boardData, line))//run through all lines of data
        {
            stringstream ss(line);
            string c;
            message item;
            j = 0;

            fileCounter++;

            while (getline(ss, c, ',')) //check through each element (c) in the line
            {
                switch (j)
                {
                    case 0:
                        item.type = c;
                        j++;
                        break;

                    case 1:
                        if (c.erase(0,1) == "for sale") {
                            item.sale = true;
                        }
                        else if (c.erase(0,1) == "wanted") {
                            item.sale = false;
                        }
                        j++;
                        break;

                    case 2:
                        item.price = stoi(c.erase(0,1));
                        j++;
                        break;

                    default:
                        break;

                }//end switch

            }//end while

            if (index == 0){
                Board[0] = item;
                index = 1;
            }
            else { //search for match in array
                bool addItem = true;

                for (int i = 0; i < index; i++){
                    searchCounter++;

                    if (item.type == Board[i].type && item.sale != Board[i].sale) {
                        //check if the two items are compatible

                        if (item.sale == false && item.price >= Board[i].price) {
                            cout << Board[i].type << " " << Board[i].price << endl;
                            addItem = false;
                            for (int j = i; j < index - 1; j++) {
                                shiftCounter++;
                                Board[j] = Board[j + 1];
                            }//end shift

                            index--;
                            break;
                        }
                        else if (item.sale == true && item.price <= Board[i].price) {
                            cout << item.type << " " << item.price << endl;
                            addItem = false;
                            for (int j = i; j < index - 1; j++) {
                                shiftCounter++;
                                Board[j] = Board[j + 1];
                            }//end shift
                            index--;
                            break;
                        }

                    }//end compatibility check
                }//end for
                if (addItem == true) {
                    Board[index] = item;
                    index++;
                }

            }//end match search

        }//end data
    }//end else

    cout << "#" << endl;

    printMessageBoard(index, Board);

    cout << "#" << endl;

    cout<<"file read:"<<fileCounter<<endl;
    cout<<"search array:"<<searchCounter<<endl;
    cout<<"shift array:"<<shiftCounter<<endl;

    return 0;

}//end main
