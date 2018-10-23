#include <iostream>
using namespace std;

struct Cell {
	int life;
	int time;
};

Cell map[2][351][351];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 0; i < 351; i++) {
			for (int j = 0; j < 351; j++) {
				map[0][i][j].life = 0;
				map[1][i][j].life = 0;
			}
		}

		int N, M, K;
		cin >> N >> M >> K;
		for (int i = 150; i < 150 + N; i++) {
			for (int j = 150; j < 150 + M; j++) {
				int life;
				cin >> life;
				map[0][i][j] = { life, 0 };
			}
		}

		int cur = 0;
		for (int k = 0; k < K; k++) {
			for (int i = 0; i < 351; i++) {
				for (int j = 0; j < 351; j++) {
					Cell cell = map[cur][i][j];

					// 죽거나, 빈 셀
					if (cell.life <= 0) continue;
					// 번식
					if (cell.time == cell.life) {
						for (int d = 0; d < 4; d++) {
							int nx = i + dir[d][0];
							int ny = j + dir[d][1];
							// 현재 상태를 보고 번식 가능여부 체크
							if (map[cur][nx][ny].life != 0) continue;
							if (map[1 - cur][nx][ny].life < map[cur][i][j].life) {
								map[1 - cur][nx][ny] = { map[cur][i][j].life, 0 };
							}
						}
					}
					cell.time++;
					// 주금
					if (cell.time == cell.life * 2) {
						map[cur][i][j] = { -1, 0 };
						map[1 - cur][i][j] = { -1, 0 };
					}
					else {
						map[cur][i][j] = cell;
						map[1 - cur][i][j] = cell;
					}
				}
			}
			cur = 1 - cur;
		}
		int answer = 0;
		for (int i = 0; i < 351; i++) {
			for (int j = 0; j < 351; j++) {
				if (map[cur][i][j].life > 0) answer++;
			}
		}
		cout << "#" << tc << " " <<  answer << endl;
	}
}