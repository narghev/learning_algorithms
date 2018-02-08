#include <iostream>
#include <algorithm>
#include<climits>

using namespace std;

int sort_and_return_median(int array[], int range){
  sort(array, array+range);
  return array[range/2];
}

int kth_smallest_element(int array[], int left, int right, int k){
  int number_of_elements = right-left+1;

  if (k<0 || k>=number_of_elements){
    return INT_MAX;
  }

  int number_of_medians = (number_of_elements/5) + (int)(number_of_elements%5!=0);
  int medians[number_of_medians];
  for (int i=0; i<number_of_medians; i++){
    medians[i] = sort_and_return_median(array+left+i*5,
      i==number_of_medians-1 ? number_of_elements%5 : 5);
  }

  return 0;
}

int main(){
  int array[] = {3,2,1,5,89,6,7,33,123,77,44};
  int size = sizeof(array)/sizeof(array[0]);
  kth_smallest_element(array, 0, size-1, 1);

  return 0;
}