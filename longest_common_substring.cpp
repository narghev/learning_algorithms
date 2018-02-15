#include <string>
#include <iostream>

using namespace std;

int D[1000][1000];
string s1, s2;

void fill_LCS(){
  for (int i=1; i<=s1.size(); i++){
    for (int j=1; j<=s2.size(); j++){
      if (s1[i-1] == s2[j-1]){
        D[i][j] = D[i-1][j-1]+1;
      }
      else {
        D[i][j] = max(D[i-1][j], D[i][j-1]);
      }
    }
  }
}

string print(int i, int j){
  if (i == 0 || j == 0)
    return "";
  if (s1[i-1] == s2[j-1]){
    return print(i-1, j-1) + s1[i-1];
  }
  else {
    if (D[i][j] == D[i-1][j]){
      return print(i-1, j);
    }
    else {
      return print(i, j-1);
    }
  }
}

int main(){
  cin>>s1>>s2;
  fill_LCS();
  cout<< print(s1.size(), s2.size()) <<endl;
  return 0;
}

/*
TEST CASE: 

  ababcdf
  adboappbwew
*/