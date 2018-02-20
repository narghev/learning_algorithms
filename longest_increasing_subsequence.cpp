#include <iostream>
#include <vector>

using namespace std;

void print_lis(int array[], int l){
  vector<vector<int> > increasing_subsequences(l);
  increasing_subsequences[0].push_back(array[0]);

  for (int i=1; i<l; i++){
    for (int j=0; j<i; j++){
      if (array[i]>array[j] && increasing_subsequences[j].size() >= increasing_subsequences[i].size())
        increasing_subsequences[i] = increasing_subsequences[j];
    }
    increasing_subsequences[i].push_back(array[i]);
  }

  vector<int> LIS = increasing_subsequences[0];

  for (int i=1; i<increasing_subsequences.size(); i++){
    if (increasing_subsequences[i].size() > LIS.size())
      LIS = increasing_subsequences[i];
  }

  // PRINT
  cout<<"Length of the lis "<<LIS.size()<<endl;

  for (int i=0; i<LIS.size(); i++)
    cout<<LIS[i]<<" ";
  cout<<endl;
}

int main(){
  
  int test_array[] = {1,2,5,7,3,1,23,2,6,4,234,6,2,34,213,5,3,1234,6,57,5,2,32};
  int size = sizeof(test_array)/sizeof(test_array[0]);
  print_lis(test_array, size);
  
  return 0;
}