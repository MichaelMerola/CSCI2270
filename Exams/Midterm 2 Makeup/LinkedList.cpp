#include <iostream>

using namespace std;

struct Node{
	int key;
	Node *next;
	Node *previous;
	Node(int k, Node *n, Node *p){
		key = k;
		next = n;
		previous = p;
	}
};

class LinkedList{
	private:
		Node *head;
		Node *search(int value){
			Node *x = head;
			while(x != NULL){
				if(x->key == value){
					break;
				}else{
					x = x->next;
				}
			}
			return x;
		}

	public:

		LinkedList(){head = NULL;};
		void addNode(int value, int newVal){
            //your code here
        }

		void printList(Node *h){
			Node *x = h;
			while(x != NULL){
				cout<<x->key<<endl;
				x = x->next;
			}
		}
    Node *getHead(){
        return head;
    }
};