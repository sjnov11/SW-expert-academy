#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int score[21];
int cal[21];
int cache[21][10001] = { -1 };


int dp(int n, int w) {
	if (cache[n][w] != -1) {
		return cache[n][w];
	}
	if (n == 0 || w == 0) {
		return cache[n][w] = 0;
	}
	

	if (w - cal[n] < 0)
		cache[n][w] = dp(n - 1, w);
	else 
		cache[n][w] = max(dp(n - 1, w - cal[n]) + score[n], dp(n - 1, w));
	return cache[n][w];
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, L;
		cin >> N >> L;

		for (int i = 1; i <= N; i++) {
			cin >> score[i] >> cal[i];
		}

		memset(cache, -1, sizeof(int) * 21 * 10001);
		
		cout << "#" << tc << " " << dp(N, L) << endl;
	}
}