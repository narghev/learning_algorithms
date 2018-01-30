#include <iostream>
#include <vector>

using namespace std;

// Needs to return the largest number
// from a[st:end] which is less than num
int bin_search(const vector<long long>& a,int start, int end, int num){
  if (end - start == 1){
    return start;
  }
  int mid = (end+start)/2;
  if (a[mid] == num){
    return mid;
  }
  if (a[mid] > num){
    return bin_search(a, start, mid, num);
  }
  else {
    return bin_search(a, mid, end, num);
  }
}

// a and b are sorted
pair<int,int>find_pair_n_logn(const vector<long long>& a, const vector<long long>& b, long long m){
  for (int i=0; i<a.size(); ++i){
    int b_i = bin_search(b, 0, b.size(), m-a[i]);
    if (a[i] + b[b_i] == m){
      return make_pair(i, b_i);
    }
  }
  return make_pair(-1, -1);
}

// a and b are sorted
pair<int, int> find_pair(const vector<long long>& a, const vector<long long>& b, long long m){
  int  i = 0, j = b.size() - 1;
  while (i != a.size() && j != 0){
    if (a[i] + b[j] == m){
      return make_pair(i, j);
    }
    if (a[i] + b[j] > m){
      j--;
    } else {
      i++;
    }
  }
  return make_pair(-1, -1);
}

int main(){
  vector<long long> a;
  int n = 1000000;
  a.reserve(n);
  for (long long i=0; i<n; ++i){
    a.push_back(i*i);
  }

  vector<long long> b;
  b.reserve(n);
  for (long long i=0; i<n; ++i){
    b.push_back(i*i + 1);
  }

  long long M = 45*45+47*47+1; // a[45]+b[47] = M
  pair<int, int> p = find_pair(a, b, M);
  cout<<p.first <<" "<<p.second<<endl;
  return 0;
}