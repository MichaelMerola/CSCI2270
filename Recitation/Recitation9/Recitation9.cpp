// Michael Merola
// counting swaps in algorithms
// quickSort seems to be fastest in the smaller arrays
/* I'm surprised to see how inefficient both insertion and bubble sort are,
   with selection sort being only slightly more effecient, and quick sort
   being the most efficient by more than 50% difference between the operations
   of selection and quickSort. I would conclude that the 'divide and conquer'
   method of sorting is the best way to sort massive datasets.
*/

#include <iostream>
using namespace std;

int quickSort(int arr[], int left, int right) {
    int count = 0;

    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
            count++;//counter
        }
    };

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);

    return count;
}//end quickSort

int selectSort(int arr[], int n) {
  int count = 0;

  int index_min_value;
  int temp;
  for (int i=0; i<n-1; i++) {
  // outer loop tracks the sorted portion of the list
    index_min_value = i; //set index_min_value to the current index of array
    for (int j=i+1; j < n; j++) // inner loop finds the next smallest value
    {
      if (arr[j] < arr[index_min_value])
        index_min_value = j;

    }
    if (index_min_value != i) {
      temp = arr[i];
      arr[i] = arr[index_min_value];
      arr[index_min_value] = temp;
      count++;//counter
    }
  }

  return count;
}//end selectSort

int insertionSort (int arr[], int length) {
  int count = 0;

  int j, temp;
  for (int i = 0; i < length; i++)  {
      j = i;
      while (j > 0 && arr[j] < arr[j-1])
      { // move elements over until find the position for next element
        temp = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = temp;
        j--;
        count++;//counter
      }
  }

  return count;
}//end insertionSort

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int bubbleSort(int arr[], int n) {
  int count = 0;

  int i, j;
  for (i = 0; i < n-1; i++) {// Last i elements are already in place
    for (j = 0; j < n-i-1; j++){
      if (arr[j] > arr[j+1]){
        swap(&arr[j], &arr[j+1]);
        count++;//counter
      }
    }
  }

  return count;
}//end bubbleSort


void printList(int arr[], int length){
  for (int i = 0; i<length; i++){
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}

int main(){
  //HINT: You should place a counter into each algorithm to see how many time each of them run. Then you can compare them easier.
  //You should use the given print statements for better organization.

  int myArray1[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray2[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray3[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray4[] = {12, 13, 5, 4, 7, 18, 9 };

  cout << endl;
  cout << " ======== Small array ======= " << endl;
  cout << endl;

  cout<<"My original small array is: "<<endl;
  printList(myArray1,7);

  //selectSort
  int selectCount = selectSort(myArray1,7);
  cout<<"When ordered with selectSort, after " << selectCount << " operations the result is: "<<endl;
  printList(myArray1,7);

  //insertionSort
  int insertCount = insertionSort(myArray2,7);
  cout<<"When ordered with insertionSort, after " << insertCount << " operations the result is: "<<endl;
  printList(myArray2,7);

  //bubbleSort
  int bubbleCount = bubbleSort(myArray3,7);
  cout<<"When ordered with bubbleSort, after " << bubbleCount << " operations the result is: "<<endl;
  printList(myArray3,7);

  //quickSort
  int quickCount = quickSort(myArray4,0,6);
  cout<<"When ordered with quickSort, after " << quickCount << " operations the result is: "<<endl;
  printList(myArray4,7);

  cout << endl;
  cout << " ======== Large array ======= " << endl;
  cout << endl;

  //generate large arrays
  int size = 1000;

  int lArray1[size];

  for (int i = 0; i < size; i++) {
      lArray1[i] = (1 + rand() % 100); //random in from 1-100
  }

  int lArray2[size];
  int lArray3[size];
  int lArray4[size];

  for (int i = 0; i < size; i++) {
      lArray2[i] = lArray1[i];
  }
  for (int i = 0; i < size; i++) {
      lArray3[i] = lArray1[i];
  }
  for (int i = 0; i < size; i++) {
      lArray4[i] = lArray1[i];
  }

  //Begin with large arrays; test with each case and use the same print statements.
  cout<<"My original large array is: "<<endl;
  printList(lArray1, size);

  //selectSort
  selectCount = selectSort(lArray1, size);
  cout<<"When ordered with selectSort, after " << selectCount << " operations the result is: "<<endl;
  printList(lArray1, size);

  //insertionSort
  insertCount = insertionSort(lArray2, size);
  cout<<"When ordered with insertionSort, after " << insertCount << " operations the result is: "<<endl;
  printList(lArray2, size);

  //bubbleSort
  bubbleCount = bubbleSort(lArray3, size);
  cout<<"When ordered with bubbleSort, after " << bubbleCount << " operations the result is: "<<endl;
  printList(lArray3, size);

  //quickSort
  quickCount = quickSort(lArray4, 0, 999);
  cout<<"When ordered with quickSort, after " << quickCount << " operations the result is: "<<endl;
  printList(lArray4, size);

  return 0;
}
