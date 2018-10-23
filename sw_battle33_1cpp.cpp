#include <cstdio>
using namespace std;

int m_day[12] = { 31, 29, 31, 30, 31, 30,
				31, 31, 30, 31, 30, 31 };

int main() {
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		int answer = 4;
		int m, n;
		scanf("%d %d", &m, &n);
		int days = 0;
		for (int i = 0; i < m - 1; i++) {
			days += m_day[i];
		}
		days += n;
		days = days % 7;
		answer = (answer + (days - 1)) % 7;
		printf("#%d %d\n",tc, answer);
	}
}