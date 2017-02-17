void shiftArray (arr[], int index, int length) {
    for (int j = index; j < length - 1; j++) {
        shiftCounter++;
        arr[j] = arr[j + 1];
    }//end shift
}
