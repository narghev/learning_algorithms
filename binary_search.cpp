#include <iostream>
#include <vector>

using namespace std;

// Needs to return the largest number
// from a[st:end] which is less than num
int bin_search(const vector<long long>& a,int start, int end, int num){
  if (end - start == 1){
    return a[start];
  }
  int mid = (end+start)/2;
  if (a[mid] > num){
    return bin_search(a, start, mid, num);
  }
  else {
    return bin_search(a, mid, end, num);
  }
}

int main(){
  vector<long long> a;
  for (long long i=0; i<1000000; ++i){
    a.push_back(i*i);
  }
  cout<<bin_search(a, 0, 1000000, 56953)<<endl;
  return 0;
}