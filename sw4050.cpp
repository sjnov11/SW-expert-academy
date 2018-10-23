#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(const int& a, const int& b) {
	return a > b;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N;
		int price[100000];
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> price[i];
		}
		sort(price, price + N, cmp);

		int answer = 0;
		for (int i = 0; i < N; i++) {
			if ((i + 1) % 3 == 0) continue;
			answer += price[i];
		}
		cout << "#" << tc << " " << answer << "\n";
	}

}