#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ----------------------------------------------------------------------
class customVector{
public:
    vector <int> intVec;
    void printVector();
    void reverseVector();
    void removeAll();
    void removeElement(int n);

};
// ----------------------------------------------------------------------
void customVector::printVector(){
    cout << "Elements of Integer Vector: " << endl;

    for (int i = 0; i < intVec.size(); i++) {
        cout << intVec[i] << endl;
    }
}

void customVector::reverseVector(){
    reverse(intVec.begin(), intVec.end());
}

void customVector::removeAll(){
  cout << "Removing all elements from the vector: " << endl;
  intVec.clear();
}

void customVector::removeElement(int n) {
    int index;

    for (int i = 0; i < intVec.size(); i++) {
        if (intVec[i] == n) {
            index = i;
        }
    }
    intVec.erase(intVec.begin() + index);
}

// ----------------------------------------------------------------------
int main(){
  customVector vec1;
  auto numbers = {1,2,3,4,5,6,7,8};
  for (auto num : numbers){
    vec1.intVec.push_back(num);
  }

  vec1.printVector();

  vec1.reverseVector();
  vec1.printVector();

  vec1.removeElement(4);
  vec1.printVector();

  vec1.removeAll();
  vec1.printVector();

  return 0;
}
