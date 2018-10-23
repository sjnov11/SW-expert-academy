#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int N;
int board[101][101];
int sx, sy;
int cx, cy, cd;
vector<pair<int, int>> worm_hole[5];

bool onBoard(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}

int crash(int &x, int &y, int &dir, int type) {
	if (type == 1) {
		if (dir == UP) dir = DOWN;
		else if (dir == DOWN) dir = RIGHT;
		else if (dir == LEFT) dir = UP;
		else if (dir == RIGHT) dir = LEFT;
		return 1;
	}
	else if (type == 2) {
		if (dir == UP) dir = RIGHT;
		else if (dir == DOWN) dir = UP;
		else if (dir == LEFT) dir = DOWN;
		else if (dir == RIGHT) dir = LEFT;
		return 1;
	}
	else if (type == 3) {
		if (dir == UP) dir = LEFT;
		else if (dir == DOWN) dir = UP;
		else if (dir == LEFT) dir = RIGHT;
		else if (dir == RIGHT) dir = DOWN;
		return 1;
	}
	else if (type == 4) {
		if (dir == UP) dir = DOWN;
		else if (dir == DOWN) dir = LEFT;
		else if (dir == LEFT) dir = RIGHT;
		else if (dir == RIGHT) dir = UP;
		return 1;
	}
	else if (type == 5) {
		if (dir == UP) dir = DOWN;
		else if (dir == DOWN) dir = UP;
		else if (dir == LEFT) dir = RIGHT;
		else if (dir == RIGHT) dir = LEFT;
		return 1;
	}
	return 0;
}

bool move(int &x, int &y, int &dir) {
	if (dir == UP) { 
		x -= 1; 
		if (!onBoard(x, y)) { x += 1; return false; }
		return true;
	}
	if (dir == DOWN) {
		x += 1;
		if (!onBoard(x, y)) { x -= 1; return false; }
		return true;
	}
	if (dir == LEFT) {
		y -= 1;
		if (!onBoard(x, y)) { y += 1; return false; }
		return true;
	}
	if (dir == RIGHT) {
		y += 1;
		if (!onBoard(x, y)) { y -= 1; return false; }
		return true;
	}
}

int simulate(int sx, int sy, int d) {
	int cx = sx, cy = sy, cd = d;
	int crash_cnt = 0;
	while (true) {
		// 경계 충돌
		if (!move(cx, cy, cd)) {
			crash_cnt += crash(cx, cy, cd, 5);
			crash_cnt += crash(cx, cy, cd, board[cx][cy]);
		}
		else {			
			crash_cnt += crash(cx, cy, cd, board[cx][cy]);			
		}
		if ((cx == sx && cy == sy) || (board[cx][cy] == -1))
			return crash_cnt;
		if (board[cx][cy] >= 6 && board[cx][cy] <= 10) {
			auto w1 = worm_hole[board[cx][cy] - 6][0];
			auto w2 = worm_hole[board[cx][cy] - 6][1];
			if (cx == w1.first && cy == w1.second)
				cx = w2.first, cy = w2.second;
			else
				cx = w1.first, cy = w1.second;
		}
	}
}

int go() {
	int answer = 0;
	for (int sx = 0; sx < N; sx++) {
		for (int sy = 0; sy < N; sy++) {
			if (board[sx][sy] != 0) continue;
			for (int d = 0; d < 4; d++) {
				answer = max(answer, simulate(sx, sy, d));
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
		cin >> N;
		for (int i = 0; i < 5; i++) {
			worm_hole[i].clear();
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
				if (board[i][j] >= 6)
					worm_hole[board[i][j] - 6].push_back({ i,j });
			}
		}

		cout << "#" << tc << " " << go() << endl;
		//cout << simulate(0, 2, LEFT);
	}

}