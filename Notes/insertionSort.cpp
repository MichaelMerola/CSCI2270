void sortByCounts(item *arr, int index) {
  int v;
  item placeHolder;

  for(int i = 0; i < index; i++) {
    v = i;
    while(v > 0 && arr[v].count > arr[v-1].count) {
      placeHolder = arr[v];
      arr[v] = arr[v-1];
      arr[v-1] = placeHolder;
      v--;
    }
  }
}
