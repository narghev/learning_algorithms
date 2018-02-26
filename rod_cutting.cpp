#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

int price[1000];
int income[1000];
int cut_location[1000];
int cutPrice;
int N;

void fill() {
	for (int i = 1; i <= N; ++i) {
		income[i] = price[i];// do not cut.
		cut_location[i] = 0;
		for (int k = 1; k <= i / 2; ++k) { // Cut location
			if (income[i] < income[k] + income[i - k] - cutPrice) {
				income[i] = income[k] + income[i - k] - cutPrice;
				cut_location[i] = k;
			}
		}
	}
}

void print(int rod_length) {
	if (cut_location[rod_length] == 0) {
		// sell as is.
		cout << rod_length << " ";
		return;
	}
	print(cut_location[rod_length]);
	print(rod_length - cut_location[rod_length]);
}

int main() {
	cin >> N >> cutPrice;
	for (int i = 1; i <= N; ++i) {
		cin >> price[i];
	}
	fill();
	cout << "Maximal income = " << income[N] << endl;
	print(N);
	return 0;
}
/*
7 1
1 3 4 1 2 1 2
*/