#include <iostream>

using namespace std;

int price[1000];
int income[1000];
int cutPrice;
int N;

void fill(){
  for (int i=0; i<N; i++){
    income[i] = price[i];
    for (int k=1; k<i/2; k++){
      if(income[i]<income[k] + income[i-k] - cutPrice){
        income[i] = income[k] + income[i-k] - cutPrice;
      }
    }
  }
}

int main(){
  cin>>N>>cutPrice;
  for (int i=0; i<N; i++){
    cin>>price[i];
  }
  fill();

}