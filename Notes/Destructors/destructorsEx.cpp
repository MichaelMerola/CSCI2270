#include <iostream>

using namespace std;

struct node {
    int key;
    node *next;
    node (int k, node *n) { //constructor
        key = k;
        next = n;
    }
    ~node () {
        cout << "deleting " << key << endl;
    }
}; //end struct

class myClass {
    private:
        node *head;
    public:
        myClass() {
            head = new node (1, NULL);
            cout << "constructor called" << endl;
        }
        ~myClass() {
            cout << "destructor called" << endl;
            delete head;
        }
}; //end class

int main() {

    node *a = new node (1, NULL);
    cout << a << endl;
    node *head = new node (2, NULL);
    cout << head << endl;
    head = a; // memory leak
    cout << head << endl;
    node *head2 = a; //not a memory leak
    cout << head2 << endl;
    node *current = NULL;

    int i = 10;
    while (i < 19) {
        current = new node(i, NULL);
        head->next = current;
        head = current;
        i++;

    }

    cout << endl;

    myClass mc; //destructor is called implicitly

    myClass *mc2 = new myClass();
    delete mc2; //runs destructor for a class

    return 0;

}//end main
