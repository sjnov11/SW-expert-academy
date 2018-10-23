#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

struct Cell {
	int x;
	int y;
	int time;
	int state;
	int passed_time;
};

bool operator < (Cell a, Cell b) {
	return a.time < b.time;
}

bool cmp(Cell a, Cell b) {
	return a.time > b.time;
}

int dir[4][2] = { {-1, 0}, {1, 0}, {0 , -1}, {0, 1} };

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, M, K;
		cin >> N >> M >> K;

		priority_queue<Cell> pq;
		set<pair<int, int>> checked;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				int time;
				cin >> time;
				if (time != 0) {
					pq.push({ i, j, time, 0, 0 });
					checked.insert({ i, j });
				}
			}
		}

		for (int i = 0; i < K; i++) {
			vector<Cell> new_pos;
			vector<Cell> pos;

			while (!pq.empty()) {
				Cell c = pq.top();
				pq.pop();
				//if (c.state == -1) continue;
				if (c.state == 0) {
					c.passed_time++;
					if (c.passed_time == c.time) {
						c.state = 1;	//activate
						c.passed_time = 0;
					}
					pos.push_back(c);
				}
				else if (c.state == 1) {
					c.passed_time++;
					if (c.passed_time == 1) {
						for (int i = 0; i < 4; i++) {
							int nx = c.x + dir[i][0];
							int ny = c.y + dir[i][1];
							//if (checked.insert({ nx, ny }).second) continue;
							new_pos.push_back({ nx, ny, c.time, 0, 0 });
						}
					}
					if (c.passed_time != c.time) {
						pos.push_back(c);
					}
				}
			}
			for (int i = 0; i < pos.size(); i++) {
				Cell c = pos[i];
				pq.push(c);
			}
			sort(new_pos.begin(), new_pos.end(), cmp);
			for (int i = 0; i < new_pos.size(); i++) {
				Cell c = new_pos[i];
				if (checked.insert({ c.x, c.y }).second) {
					pq.push(c);
				}
			}
		}

		cout << "#" << tc << " " << pq.size() << endl;
	}


}