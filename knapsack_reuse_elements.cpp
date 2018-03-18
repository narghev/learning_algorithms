#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

int D[10][10000000];
int A[10];
int M, N;

void fill_D() {// O(n*m)
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < A[i]; ++j) {
			D[i][j] = D[i - 1][j];
		}
		for (int j = A[i]; j <= M; ++j) {
			D[i][j] = max(D[i - 1][j], D[i][j - A[i]] + A[i]);
		}
	}
}
int print(int i, int j) { // O(N+M)
	if (i == 0 || j == 0)
		return 0;
	if (D[i][j] == D[i - 1][j]) {
		return print(i-1, j);
	}
	else {
		cout << " " << A[i];
		return print(i, j - A[i]);
	}
}
int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
	}
	fill_D();
	cout << "Closest value to " << M 
		<< " is "<< D[N][M] << endl;
	print(N, M);
	return 0;
}

/*
1 1700000
1
*/