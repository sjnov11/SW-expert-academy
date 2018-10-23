#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int N;
int map[101][101];
int dp[101][101][4];
int delta[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
vector<pair<int, int>> warmhole[5];
int crash(int dir, int b_type) {
	if (b_type == 1) {
		if (dir == UP) {
			return DOWN;
		}
		if (dir == DOWN) {
			return RIGHT;
		}
		if (dir == LEFT) {
			return UP;
		}
		if (dir == RIGHT) {
			return LEFT;
		}
	}
	else if (b_type == 2) {
		if (dir == UP) {
			return RIGHT;
		}
		if (dir == DOWN) {
			return UP;
		}
		if (dir == LEFT) {
			return DOWN;
		}
		if (dir == RIGHT) {
			return LEFT;
		}
	}
	else if (b_type == 3) {
		if (dir == UP) {
			return LEFT;
		}
		if (dir == DOWN) {
			return UP;
		}
		if (dir == LEFT) {
			return RIGHT;
		}
		if (dir == RIGHT) {
			return DOWN;
		}
	}
	else if (b_type == 4) {
		if (dir == UP) {
			return DOWN;
		}
		if (dir == DOWN) {
			return LEFT;
		}
		if (dir == LEFT) {
			return RIGHT;
		}
		if (dir == RIGHT) {
			return UP;
		}
	}
	else {
		if (dir == UP) {
			return DOWN;
		}
		if (dir == DOWN) {
			return UP;
		}
		if (dir == LEFT) {
			return RIGHT;
		}
		if (dir == RIGHT) {
			return LEFT;
		}
	}
}




void go(int &x, int &y, int &dir, int &score) {
	int dx = delta[dir][0];
	int dy = delta[dir][1];

	x += dx;
	y += dy;
	if (x < 0 || x >= N || y < 0 || y >= N) {
		dir = crash(dir, 5);
		score++;
		x -= dx;
		y -= dy;
	}
	
}

int simulate(int x, int y, int dir) {
	int score = 0;
	int cx = x, cy = y, cdir = dir;
	while (true) {		
		go(cx, cy, cdir, score);
		
		if (cx == x && cy == y) break;
		if (dp[cx][cy][cdir] != 0) {
			score += dp[cx][cy][cdir];
			break;
		}
		
		
		if (map[cx][cy] >= 1 && map[cx][cy] <= 5) {
			cdir = crash(cdir, map[cx][cy]);
			score++;
		}
		else if (map[cx][cy] == -1) 			
			break;		
		else if (map[cx][cy] >=6 && map[cx][cy] <= 10) {
			int nx = warmhole[map[cx][cy]-6][0].first;
			int ny = warmhole[map[cx][cy]-6][0].second;
			if (nx == cx && ny == cy) {
				nx = warmhole[map[cx][cy]-6][1].first;
				ny = warmhole[map[cx][cy]-6][1].second;
			}
			cx = nx;
			cy = ny;
		}
	}
	dp[x][y][dir] = score;
	return score;
}


int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 0; i < 5; i++) {
			warmhole[i].clear();
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < 4; k++) {
					dp[i][j][k] = 0;
				}
			}
		}
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] >= 6 && map[i][j] <= 10) {
					int n = map[i][j] - 6;
					warmhole[n].push_back({ i, j });
				}
			}
		}

		int answer = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] != 0) continue;
				if (i == 8 && j == 15) {
					printf("break\n");
				}
				answer = max(answer, simulate(i, j, UP));
				answer = max(answer, simulate(i, j, DOWN));
				answer = max(answer, simulate(i, j, LEFT));
				answer = max(answer, simulate(i, j, RIGHT));
			}
		}
		cout << "#" << tc << " "<< answer << endl;
	}
}