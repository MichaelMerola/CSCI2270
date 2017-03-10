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

		}

	public:

		LinkedList(){head = NULL;};

		void getName()
		   {
			cout<<"Michael Merola";
		   }

		void addNode(int value, int newVal){

			if (head == NULL) {
				head = new Node(newVal, NULL, NULL);
			}
			else {
				Node *temp;
				temp = head;
				bool flag = false;

				while (temp != NULL) { //find node
					if (temp->key == value) {
						flag = true;
						break;
					}
					temp = temp->next;
				}

				cout << temp->key << endl;

				Node *right;
				right = temp->next;
				Node *n = new Node(newVal, NULL, NULL);

				if (flag == true) {
					n->next = head->next;
					head = n;
				}
				else if (temp->key == value && right == NULL) {
					temp->next = n;
	                n->previous = temp;

				}
				else if (temp->key == value) {
					temp->next = n;
	                n->previous = temp;

	                right->previous = n;
	                n->next = right;

				}
				else {
					n->next = head->next;
					head = n;
				}

			}


		}//end addNode


   Node *getHead()
      {
		return head;
      }


		void printList(){
			Node *x = head;
			while(x != NULL){
				cout<<x->key<<endl;
				x = x->next;
			}
		}
};
