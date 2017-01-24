#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string filename;
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

    message Board[100]; //create array of message structs

    fstream boardData;

    cout << "What is the name of your file: " ;
    cin >> filename;

    boardData.open(filename); //open the file

    if (boardData.fail())
    {
        cout << "Something bad happened" << endl; // check if file opens successfully
    }
    else
    {
        string line;
        int i = 0;
        int j = 0;
        while (getline(boardData, line))//run through all lines of data
        {
            stringstream ss(line);
            string c;
            j = 0;

            while (getline(ss, c, ',')) //check through each c value
            {
                switch (j)
                {
                    case 0:
                        Board[i].type = c;
                        j++;
                        break;

                    case 1:
                        if (c == " for sale") {
                            Board[i].sale = true;
                        }
                        else if (c == " wanted") {
                            Board[i].sale = false;
                        }
                        j++;
                        break;

                    case 2:
                        Board[i].price = stoi(c);
                        j++;
                        break;

                    default:
                        break;

                }//end switch

            }//end while
            i++;
        }
    }

    for (int i = 99; i >= 0; i--)
    {
        cout << Board[i].type << Board[i].sale << Board[i].price << endl;
    }

    return 0;

}//end main
