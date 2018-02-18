#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Matrix {
public:
  Matrix(unsigned long n, unsigned long m) {
    row_count = n;
    column_count = m;
    for(int i = 0; i < n; i++) {
      vector<int> tempVector;
      tempVector.reserve(static_cast<unsigned long>(m));
      for(int j = 0; j < m; j++) {
        tempVector.push_back(0);
      }
      M.push_back(tempVector);
    }
  }

  void set_value(unsigned long i, unsigned long j, unsigned long value) {
    M[i][j] = value;
  }

  int get_value(unsigned long i, unsigned long j) const {
    return M[i][j];
  }

  unsigned long get_column_count() const {
    return column_count;
  }

  Matrix fill() const {
    // We need to fill with 0's till we have 2^n x 2^n matrix.
    // Check Wikipedia for more info
    // https://en.wikipedia.org/wiki/Strassen_algorithm
    auto fill_amount = static_cast<unsigned  long>(pow(2, ceil(log2(max(row_count, column_count)))));
    Matrix result(fill_amount, fill_amount);
    for(int i = 0; i < fill_amount; i++) {
      for(int j = 0; j < fill_amount; j++) {
        if (i < row_count && j < column_count) {
          result.set_value(i, j, M[i][j]);
        } else {
          result.set_value(i, j, 0);
        }
      }
    }
    return result;
  }

  Matrix trim(unsigned long rows, unsigned long columns) const {
    // For bringing back after fill
    Matrix result(rows, columns);
    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < columns; j++) {
        result.set_value(i, j, M[i][j]);
      }
    }
    return result;
  }

  Matrix part(unsigned long row_start, unsigned long row_end, unsigned long col_start, unsigned long col_end) const {
    unsigned long length = row_end - row_start;
    Matrix result(length, length);
    for(unsigned long i = row_start; i < row_end; i++) {
      for(unsigned long j = col_start; j < col_end; j++) {
        result.set_value(i - row_start, j - col_start, M[i][j]);
      }
    }
    return result;
  }

  void print() const {
    for (const auto &i : M) {
      for(int j = 0; j < M[0].size(); j++) {
        cout << setw(5) << i[j];
      }
      cout << endl << endl;
    }
  }

  Matrix operator+(const Matrix& M1) const { // O(N^2)
    auto rowsCount = M.size(), columnsCount = M[0].size();
    Matrix result(static_cast<int>(rowsCount), static_cast<int>(columnsCount));
    for(int i = 0; i < M.size(); i++) {
      for(int j = 0; j < M[0].size(); j++) {
        int value = M[i][j] + M1.get_value(i, j);
        result.set_value(i, j, value);
      }
    }
    return result;
  }

  Matrix operator-(const Matrix& M1) const { // O(N^2)
    auto rowsCount = M.size(), columnsCount = M[0].size();
    Matrix result(static_cast<int>(rowsCount), static_cast<int>(columnsCount));
    for(int i = 0; i < M.size(); i++) {
      for(int j = 0; j < M[0].size(); j++) {
        int value = M[i][j] - M1.get_value(i, j);
        result.set_value(i, j, value);
      }
    }
    return result;
  }

  Matrix operator*(const Matrix& m1) const { // O(N^log(2,7))
    unsigned long result_row_count = row_count;
    unsigned long result_col_count = m1.get_column_count();
    Matrix first_multiplier = this->fill(), second_multiplier = m1.fill();
    unsigned long N = first_multiplier.M.size();
    Matrix result_container = Matrix(N, N);
    if(N == 1) {
      result_container.set_value(0, 0, M[0][0] * m1.get_value(0, 0));
      return result_container;
    }
    Matrix A11 = first_multiplier.part(0, N/2, 0, N/2),
          A12 = first_multiplier.part(0, N/2, N/2, N),
          A21 = first_multiplier.part(N/2, N, 0, N/2),
          A22 = first_multiplier.part(N/2, N, N/2, N),
          B11 = second_multiplier.part(0, N/2, 0, N/2),
          B12 = second_multiplier.part(0, N/2, N/2, N),
          B21 = second_multiplier.part(N/2, N, 0, N/2),
          B22 = second_multiplier.part(N/2, N, N/2, N),
          M1 = (A11 + A22) * (B11 + B22),
          M2 = (A21 + A22) * B11,
          M3 = A11 * (B12 - B22),
          M4 = A22 * (B21 - B11),
          M5 = (A11 + A12) * B22,
          M6 = (A21 - A11) * (B11 + B12),
          M7 = (A12 - A22) * (B21 + B22),
          C11 = M1 + M4 - M5 + M7,
          C12 = M3 + M5,
          C21 = M2 + M4,
          C22 = M1 - M2 + M3 + M6;

    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        if(i < N/2 && j < N/2) {
          result_container.set_value(i, j, C11.get_value(i, j));
        } else if (i < N/2 && j < N) {
          result_container.set_value(i, j, C12.get_value(i, j - N/2));
        } else if (i < N && j < N/2) {
          result_container.set_value(i, j, C21.get_value(i - N/2, j));
        } else {
          result_container.set_value(i, j, C22.get_value(i - N/2, j - N/2));
        }
      }
    }

      Matrix result = result_container.trim(result_row_count, result_col_count);


      return result;
    }

private:
  unsigned long row_count;
  unsigned long column_count;
  vector<vector<int>> M;
};

int main() {
  Matrix a = Matrix(3, 4), b = Matrix(4, 3);
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 4; j++) {
      a.set_value(i, j, i + j);
    }
  }
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      b.set_value(i, j, i * 2 + j - 1);
    }
  }
  a.print();
  cout << endl << endl;
  b.print();
  cout << endl << endl;
  Matrix c = a * b;
  c.print();
  cout << endl << endl;
  return 0;
}