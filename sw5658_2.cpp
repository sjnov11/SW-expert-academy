#include <iostream>
#include <set>
#include <deque>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

bool cmp(const int &a, const int &b) {
	return a > b;
}


int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, K;
		cin >> N >> K;
		string s;
		cin >> s;
		set<int> answer_set;
		for (int i = 0; i < N; i++) {
			string s_num = s.substr(0, N / 4);
			int num = stoi(s_num, 0, 16);
			answer_set.insert(num);

			s = s[s.size() - 1] + s.substr(0,s.size()-1);
		}
		auto end = answer_set.end();
		for (int i = 0; i < K; i++) {
			--end;
		}
	
		cout << "#" << tc << " " << *end << endl;
	}
}