#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

void swap(int *a, int *b){
  int temp_pointer = *a;
  *a=*b;
  *b=temp_pointer;
}

int partition(int array[], int left, int right, int pivot){
  int i = left;

  for (i; i<right; i++){
    if(array[i] == pivot){
      break;
    }
  }

  int pivot_index = i;
  swap(array[pivot_index], array[right]);

  i=left;
  for (int j=left; j<right; j++){
    if(array[j]<=array[right]){
      swap(array[j], array[i]);
      i++;
    }
  }
  swap(array[i], array[right]);
  return i;
}

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

  int median_of_medians = (number_of_medians == 1) ? medians[0] : kth_smallest_element(medians, 0,
    number_of_medians-1, number_of_medians/2);

  int position_of_med_of_meds = partition(array, left, right, median_of_medians);

  if (position_of_med_of_meds-left+1 == k){
    return array[position_of_med_of_meds];
  }
  else if (position_of_med_of_meds-left+1 < k){
    int new_k = k-position_of_med_of_meds+left-1;
    return kth_smallest_element(array, position_of_med_of_meds+1, right, new_k);
  }
  
  return kth_smallest_element(array, left, position_of_med_of_meds-1, k);
}

int main(){
  int array[] = {3,2,1,5,89,6,7,33,123,77,44};
  int size = sizeof(array)/sizeof(array[0]);
  cout<<kth_smallest_element(array, 0, size-1, 1)<<endl;

  sort(array, array+size);
  for(int i=0; i<size;i++)
    cout<<array[i]<<" ";
  cout<<endl;

  return 0;
}