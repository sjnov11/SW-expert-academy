#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, K;
		cin >> N >> K;
		string s;
		cin >> s;

		set<int> num_list;
		for (int c = 0; c < N/4; c++) {
			// 0, 3, 6, 9, ... 12 일때 /4 = 3
			// N일때는 /4 
			// 0 , N/4 , N/4 * 2
			for (int i = 0; i < 4; i++) {
				string n = s.substr(0 + i * N / 4, N / 4);
				int num = stoi(n, nullptr, 16);
				//cout << n << " : " <<  num << endl;
				num_list.insert(num);
			}
			char end = s[s.size() - 1];
			s = end + s.substr(0, s.size() - 1);
		}
		auto it = num_list.end();
		for (int i = 0; i < K; i++) {
			it--;

		}
		cout << "#" << tc << " " << *it <<"\n";
	}
	
}