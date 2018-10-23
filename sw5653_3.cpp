#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int board[400][400];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
struct Cell {
	int x, y;
	int life;
	int time;
};

bool operator <(const Cell &a, const Cell &b) {
	return a.life > b.life;
}

bool cmp(const Cell &a, const Cell &b) {
	return a.life > b.life;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, M, K;
		cin >> N >> M >> K;
		queue<Cell> alive_cell_queue;
		for (int i = 0; i < 400; i++) {
			for (int j = 0; j < 400; j++) {
				board[i][j] = 0;
			}
		}
		for (int i = 150; i < 150 + N; i++) {
			for (int j = 150; j < 150 + M; j++) {
				cin >> board[i][j];
				if (board[i][j] > 0) alive_cell_queue.push({ i,j,board[i][j],0 });
			}
		}
		for (int k = 0; k < K; k++) {
			vector<Cell> next_cell_list;

			while (!alive_cell_queue.empty()) {
				Cell cell = alive_cell_queue.front();
				alive_cell_queue.pop();
				// spread
				if (cell.time == cell.life) {
					for (int d = 0; d < 4; d++) {
						int nx = cell.x + dir[d][0];
						int ny = cell.y + dir[d][1];
						if (board[nx][ny] != 0) continue;
						next_cell_list.push_back({ nx,ny,cell.life,0 });
					}
				}
				cell.time++;
				if (cell.time == cell.life * 2) {
					board[cell.x][cell.y] = -1;
				}
				else {
					next_cell_list.push_back(cell);
				}
			}
			sort(next_cell_list.begin(), next_cell_list.end());
			for (auto cell : next_cell_list) {
				if (cell.time > 0) alive_cell_queue.push(cell);
				else {
					if (board[cell.x][cell.y] == 0) {
						board[cell.x][cell.y] = cell.life;
						alive_cell_queue.push(cell);
					}
				}
			}
		}
		int answer = 0;
		for (int i = 0; i < 400; i++) {
			for (int j = 0; j < 400; j++) {
				if (board[i][j] > 0) answer++;
			}

		}
		cout << "#" << tc << " " << answer << endl;
	}
}