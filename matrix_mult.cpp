#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

class Matrix {
  Matrix(int n, int m){}
  void set_value(int i, int j, int value){
    M[i][j] = value;
  }
  void print() const {

  }
  Matrix operator+(const Matrix& m1) const { //O(n^2)

  }
  Matrix operator*(const Matrix& m1) const { //O(n^log(2,7))

  }
}