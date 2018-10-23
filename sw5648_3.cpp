#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

struct Atom {
	int x, y, d;
	int energy;
	int state;
	int time;
};

struct cheker {
	int idx;
	int time;
	int state;
};


void move(Atom &a) {
	if (a.d == UP) a.y += 1;
	if (a.d == DOWN) a.y -= 1;
	if (a.d == LEFT) a.x -= 1;
	if (a.d == RIGHT) a.x += 1;
}

bool onBoard(Atom a) {
	return a.x >= 0 && a.x < 4001 && a.y >= 0 && a.y < 4001;
}


int N;
//cheker board[4001][4001];
int visited[4001][4001];
bool collide[4001][4001];
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		vector<Atom> atom_list;
		for (int i = 0; i < N; i++) {
			int x, y, d, e;
			cin >> x >> y >> d >> e;
			atom_list.push_back({ (x + 1000) * 2 ,(y + 1000) * 2,d,e,1, 0 });
			visited[(x + 1000) * 2][(y + 1000) * 2]++;
		}
		/*cheker init = { -1,-1, 0 };
		for (int i = 0; i < 4001; i++) {
			for (int j = 0; j < 4001; j++) {
				board[i][j] = init;
			}
		}*/
		int answer = 0;
		for (int s = 0; s < 4001; s++) {
			// 이동
			for (int i = 0; i < atom_list.size(); i++) {
				Atom &atom = atom_list[i];
				if (atom.state == -1) continue;
				visited[atom.x][atom.y]--;
				if (visited[atom.x][atom.y] == 1)
					collide[atom.x][atom.y] = false;
				move(atom);				
				if (!onBoard(atom)) atom.state = -1;
				else {
					if (++visited[atom.x][atom.y] >= 2) collide[atom.x][atom.y] = true;
				}
			}

			// 충돌 체크
			for (int i = 0; i < atom_list.size(); i++) {
				Atom &atom = atom_list[i];
				if (atom.state == -1) continue;
				if (collide[atom.x][atom.y]) {
					answer += atom.energy;
					atom.state = -1;
					if (visited[atom.x][atom.y] == 1)
						collide[atom.x][atom.y] = false;
					visited[atom.x][atom.y]--;
				}
				//if (atom.state == -1) continue;
				//// 누가 있다
				//if (board[atom.x][atom.y].time == tc*4000 +s) {
				//	if (board[atom.x][atom.y].state != -1) {
				//		atom_list[board[atom.x][atom.y].idx].state = -1;
				//		answer += atom_list[board[atom.x][atom.y].idx].energy;
				//		board[atom.x][atom.y].state = -1;
				//	}
				//	atom.state = -1;
				//	answer += atom.energy;
				//}
				//else {
				//	board[atom.x][atom.y] = { i, tc*4000 + s, 1 };					
				//}
			}
		}
		cout << "#"<< tc << " " << answer << endl;
	}
}
