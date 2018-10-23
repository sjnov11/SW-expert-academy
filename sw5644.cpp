#include <iostream>
#include <cmath>
using namespace std;

struct Charger {
	int x;
	int y;
	int c;
	int p;
};
struct Chargers {
	Charger* c1;
	Charger* c2;
};

struct Person {
	int x;
	int y; 
};

int M, A;
int move_info[2][100];
Charger charger_info[8];
int delta[5][2] = { {0, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

bool inArea(int charger_num, Person p) {
	int cx = charger_info[charger_num].x;
	int cy = charger_info[charger_num].y;
	int cc = charger_info[charger_num].c;

	if (abs(p.x - cx) + abs(p.y - cy) <= cc)
		return true;
	return false;
}

struct Chargers selectTwo(Person p) {
	Charger* first = NULL;
	Charger* second = NULL;
	Chargers ret;
	for (int charger = 0; charger < A; charger++) {
		if (inArea(charger, p)) {
			if (first == NULL || first->p < charger_info[charger].p) {
				second = first;
				first = &charger_info[charger];
			}
			else {
				if (second == NULL || second->p < charger_info[charger].p) {
					second = &charger_info[charger];
				}
			}
		}
	}
	ret.c1 = first;
	ret.c2 = second;

	return ret;
}

int getBest(Chargers p1_c, Chargers p2_c) {
	int answer = 0;
	Charger *p1_first, *p1_second, *p2_first, *p2_second;
	p1_first = p1_c.c1, p1_second = p1_c.c2;
	p2_first = p2_c.c1, p2_second = p2_c.c2;

	if (p1_first == NULL || p2_first == NULL) {
		answer += p1_first == NULL ? 0 : p1_first->p;
		answer += p2_first == NULL ? 0 : p2_first->p;
	}
	else if (p1_first != p2_first) {
		answer += p1_first->p + p2_first->p;
	}
	else {
		if (p1_second == NULL && p2_second == NULL) {
			answer += p1_first->p;
		}
		else if (p1_second == NULL) {
			answer += p1_first->p + p2_second->p;
		}
		else if (p2_second == NULL) {
			answer += p1_second->p + p2_first->p;
		}
		else {
			if (p1_second->p > p2_second->p) {
				answer += p1_second->p + p2_first->p;
			}
			else {
				answer += p1_first->p + p2_second->p;
			}
		}
	}
	return answer;
}


int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> M >> A;
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < M; i++) {
				cin >> move_info[j][i];
			}
		}
		for (int i = 0; i < A; i++) {
			cin >> charger_info[i].x;
			cin >> charger_info[i].y;
			cin >> charger_info[i].c;
			cin >> charger_info[i].p;
		}

		Person p1 = { 1,1 };
		Person p2 = { 10,10 };

		int answer = 0;
		for (int m = 0; m < M; m++) {			
			Chargers p1_chargers = selectTwo(p1);
			Chargers p2_chargers = selectTwo(p2);
			answer += getBest(p1_chargers, p2_chargers);

			// 이동
			p1.x += delta[move_info[0][m]][0];
			p1.y += delta[move_info[0][m]][1];
			p2.x += delta[move_info[1][m]][0];
			p2.y += delta[move_info[1][m]][1];
		}
		// 마지막 이동		
		// 처음 포지션
		Chargers p1_chargers = selectTwo(p1);
		Chargers p2_chargers = selectTwo(p2);
		answer += getBest(p1_chargers, p2_chargers);
		

		cout << "#" << tc << " " << answer << endl;
	}

}