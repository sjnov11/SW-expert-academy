#include <iostream>
#include <queue>
using namespace std;

char map[1001][1001];
int dir[4][2] = { {-1, 0}, {1, 0} , {0, -1}, {0, 1} };

struct Node {
	int x;
	int y;
	int cnt;
	vector<pair<int, int>> n_block;
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int R, C;
		cin >> R >> C;
		for (int i = 0; i < R; i++) {
			cin >> map[i];
		}
		int sr, sc;
		cin >> sr >> sc;
		int er, ec;
		cin >> er >> ec;

		int answer = -1;
		queue<Node> q;
		Node start;
		start.x = sr - 1;
		start.y = sc - 1;
		start.cnt = 0;
		
		q.push(start);

		while (!q.empty()) {
			Node cur = q.front();
			q.pop();
			/*if (cur.x == er - 1 && cur.y == ec - 1) {
				answer = cur.cnt;
				break;
			}*/

			char cur_map[1001][1001];
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					cur_map[i][j] = map[i][j];
				}
			}
			for (auto pos : cur.n_block) {
				cur_map[pos.first][pos.second] = '#';
			}
			
			for (int i = 0; i < 4; i++) {
				int nx = cur.x;
				int ny = cur.y;
				int dx = dir[i][0];
				int dy = dir[i][1];
				if (cur_map[nx + dx][ny + dy] == '#') continue;
				while (cur_map[nx + dx][ny + dy] != '#') {
					nx += dx;
					ny += dy;
				}
				Node next;
				next.x = nx;
				next.y = ny;
				next.cnt = cur.cnt + 1;
				for (auto pos : cur.n_block) {
					next.n_block.push_back(pos);
				}
				next.n_block.push_back({ cur.x, cur.y });
				q.push(next);
			}
		}
		cout << "#" << tc << " " <<  answer << endl;
	}
}