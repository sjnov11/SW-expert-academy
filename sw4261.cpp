#include <iostream>
#include <string>
#include <vector>
using namespace std;

char keypad[26] = { '2','2','2',
					'3','3','3',
					'4','4','4',
					'5','5','5',
					'6','6','6',
					'7','7','7','7',
					'8','8','8',
					'9','9','9','9' };
int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		string S;
		int N;
		cin >> S >> N;
		int answer = 0;
		for (int i = 0; i < N; i++) {
			string word;
			cin >> word;
			bool flag = true;
			for (int j = 0; j < word.size(); j++) {
				if (S[j] != keypad[word[j] - 'a']) {
					flag = false;
					break;
				}
			}
			if (flag) answer++;
		}
		cout << "#" << tc << " " << answer << "\n";
	}
}