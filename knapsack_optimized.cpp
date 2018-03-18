#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int arr[10];
int length, sack;
vector<int> v[2];
int current_weight = 0;

void ks(int start, int end) {
  if (start == end) {
      if (current_weight <= sack) {
          int index = (end - length / 2) / (length / 2);
          v[index].push_back(current_weight);
      }
      return;
  }
  if (current_weight > sack) return;

  // use
  ks(start + 1, end);
  current_weight += arr[start];

  // not use
  ks(start + 1, end);
  current_weight -= arr[start];
}

int result(int res, int diff, int left, int right){
  if (left == v[0].size() || right == 0)
    return res;
  int cur_value = v[0][left] + v[1][right];
  if (abs(sack - cur_value) < diff){
    diff = abs(sack - cur_value);
    res = v[0][left] + v[1][right];
  }
  if (cur_value > sack)
    return result(res, diff, left, right-1);
  else if (cur_value < sack)
    return result(res, diff, left+1, right);
  else
    return res;
}

int main() {
  cin >> length >> sack;
  for (int i = 1; i <= length; ++i) {
      cin >> arr[i];
  }

  ks(0, length / 2);
  ks(length / 2 + 1, length);

  sort(v[0].begin(), v[0].end());
  sort(v[1].begin(), v[1].end());

  int p = result(v[0][0] + v[1][v[1].size()-1],
    abs(sack-(v[0][0] + v[1][v[1].size()-1])),
    1, v[1].size()-1);

  cout << "closest value to " << sack << " is " << p << endl;
    return 0;
}

/*
5 17
2 4 6 8 10
*/