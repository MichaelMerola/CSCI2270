#include <iostream>

using namespace std;

void bubbleSort (int A[], int length) {

    for (int i = 0; i < length-1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (A[j] > A[j+1]) {
                int swapp = A[j];
                A[j] = A[j+1];
                A[j+1] = swapp;

            }//end if
        }//end inner for
    }//end outer for
}//end bubbleSort

int main() {

    int A[4] = {45, 44, 32, 23};

    bubbleSort(A, 4);

    // Arrays in C++ are passes between functions as pointers; their address in memory remains the same



}//end main
