#include <iostream>
#include <vector>

using namespace std;

void merge_sort(vector<long long>& a, int start, int end){
  if (end - start == 1)
    return;
  int mid = (start+end)/2;
  merge_sort(a, start, mid);
  merge_sort(a, mid, end);

  vector<long long> b;
  b.reserve(end - start);
  int i = start, j = mid;

  while(i != mid && j != end){
    if (a[i] < a[j]){
      b.push_back(a[i]);
      i++;
    }
    else {
      b.push_back(a[j]);
      j++;
    }
  }
  while(i != mid){
    b.push_back(a[i]);
    i++;
  }
  while(j != end){
    b.push_back(a[j]);
    j++;
  }
  for(int i = start; i<end; i++){
    a[i] = b[i-start];
  }
}

int main(){
  return 0;
}