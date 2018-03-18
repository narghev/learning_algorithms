#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

int D[1000][1000];
int A[1000];
int M, N;

void fill_D() {// O(n*m)
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < A[i]; ++j) {
			D[i][j] = D[i - 1][j];
		}
		for (int j = A[i]; j <= M; ++j) {
			D[i][j] = max(D[i - 1][j], D[i - 1][j - A[i]] + A[i]);
		}
	}
}
void print(int i, int j) { // O(??)
	if (i == 0)
		return;
	if (D[i][j] == D[i - 1][j]) {
		print(i - 1, j);
	}
	else {
		print(i - 1, j - A[i]);
		cout << " " << A[i];
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
7 17
2 4 6 8 10 12 14
*/