#include <iostream>

using namespace std;

struct item{
  int count;
  string name;
};
int main(){
  int length = 10;
  //create an array of length 10
  item *itemArray = new item[length];

  //write some stuff to array
  for(int i = 0; i < length; i++){
    itemArray[i].count = i;
    itemArray[i].name = "name";
  }

  //verify array values
  for(int i = 0; i < length; i++){
    cout<<itemArray[i].count<<" "<<itemArray[i].name<<endl;
  }

  length = length * 2;
  //create a new array that is double the length of first array
  item *itemArray2 = new item[length];
  //copy values to new array. You only need length/2 because that's the length of original array
  for(int i = 0; i < length/2; i++){
    itemArray2[i].count = itemArray[i].count;
    itemArray2[i].name = itemArray[i].name;

  }
  //free the memory for old array
  delete []itemArray;
  //update the pointer to point to new array
  itemArray = itemArray2;
  //verify array contents
  for(int i = 0; i < length; i++){
    cout<<itemArray[i].count<<" "<<itemArray[i].name<<endl;
  }

}
