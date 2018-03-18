#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

int A[10];
int M, N;
int closest = 0;
int current_sum = 0;

void rec(int i) {
	if (i == N + 1) {
		if (current_sum <= M && current_sum > closest) {
			closest = current_sum;
		}
		return;
	}
	if (current_sum > M)
		return;
	rec(i+1); // Do not use A[i].
	current_sum += A[i];
	rec(i + 1); // DO use A[i].
	current_sum -= A[i];
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
	}
	rec(0);
	cout << "Closest value to " << M 
		<< " is " << closest << endl;
	return 0;
}

/*
5 17
2 4 6 8 10
*/