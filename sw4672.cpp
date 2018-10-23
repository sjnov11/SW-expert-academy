#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

int dp[11][11];

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		memset(dp, 0, sizeof(int) * 11 * 11);
		string s;
		cin >> s;
		vector<int> si;

		for (int i = 0; i < s.size(); i++) {
			si.push_back(s[i] - 'a');
		}

		sort(si.begin(), si.end());
		string t;
		for (auto i : si)
			t.push_back('a' + i);

		for (int i = 0; i < t.size(); i++) {
			dp[i][i] = 1;
		}
		for (int i = 0; i < t.size() - 1; i++) {
			if (t[i] == t[i + 1])
				dp[i][i + 1] = 1;
		}

		for (int l = 2; l < t.size(); l++) {
			for (int i = 0; i < t.size() - l; i++) {
				int j = i + l;
				if (t[i] == t[j])
					dp[i][j] = dp[i + 1][j - 1];
			}
		}
		int answer = 0;
		for (int i = 0; i < t.size(); i++) {
			for (int j = i; j < t.size(); j++) {
				if (dp[i][j] == 1) answer++;
			}
		}
		cout << "#" << tc << " " << answer << endl;
	}
}