#include <iostream>
#include <vector>

using namespace std;

int sort_and_median(int array[], int range){
  cout<<array<<endl;
  sort(array, array+range);
  return array[range/2];
} 

int kth_smallest_element(int array[], int length){
  int medians[length/5];
  for (int i=0; i<length/5; i++){
    medians[i] = sort_and_median(array+i, 5);
    cout<<"median"<<medians[i]<<endl;
  }
}

int main(){
  int array[] = {3,2,1,5,5,6,7,33,123,77};
  kth_smallest_element(array, array.length());
}