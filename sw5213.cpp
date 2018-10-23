#include <iostream>
#include <cmath>
using namespace std;


long long dp[1000001];
long long sum[1000001];


int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	dp[1] = 1;
	sum[1] = 1;
	for (int i = 2; i <= 1000000; i++) {
		if (dp[i] != 0) continue;
		else {
			if (i % 2 == 1) {
				for (int j = 1; j <= sqrt(i); j += 2) {
					if (i % j == 0) {
						dp[i] += j;
						if (j != i / j)
							dp[i] += i / j;
					}
				}
			}
			else {
				dp[i] = dp[i / 2];
			}
			sum[i] = sum[i - 1] + dp[i];
		}
	}

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int L, R;
		cin >> L >> R;
		

		/*for (int i = 1; i <= R; i++) {
			cout << dp[i] << " ";
		}
		cout << endl;*/
		long long answer = 0;
		answer = sum[R] - sum[L - 1];
		cout << "#"<< tc << " " << answer << "\n";
	}
}