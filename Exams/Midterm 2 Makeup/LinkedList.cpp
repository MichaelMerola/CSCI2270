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
					return x; //changed
				}else{
					x = x->next;
				}
			}
			return NULL;//changed
		}

	public:

		LinkedList(){head = NULL;};
		void addNode(int value, int newVal){

			Node *place; //node that will be previous to new
		    Node *right;
			Node *add; //new node

			place = search(value);
			if (place != NULL) {
		    	right = place->next;
			}

		    add = new Node(newVal, NULL, NULL);

		    if (head == NULL) { //check if head is NULL
		        head = add;
		        head->next = NULL;
		        head->previous = NULL;
		    }//end if
			else if (place == NULL) { //value isn't found
				add->next = head;
				head->previous = add;
				head = add;
			}
		    else { //place is valid and list has head

	            if (place->next == NULL) { //check if place is tail
	                place->next = add;
					add->previous = place;
	            }
	            else {
					place->next = add;
					add->next = right;

					right->previous = add;
					add->previous = place;
	            }

		    }//end else
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
