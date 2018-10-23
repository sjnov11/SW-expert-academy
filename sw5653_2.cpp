#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

struct Cell {
	int x;
	int y;
	int val;
	int time;
	int state;	//  0비활성, 1 활성, -1사망
};

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<Cell> cell_list;

bool cmp(const Cell &a, const Cell &b) {
	return a.val > b.val;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, M, K;
		cin >> N >> M >> K;

		queue<Cell> q;
		set<pair<int, int>> checked;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				int val;
				cin >> val;
				if (val == 0) continue;
				q.push({ i,j,val,0,0 });
				checked.insert({ i,j });
			}
		}

		for (int k = 0; k < K; k++) {
			// 갈수록 셀의 크기가 점점 커진다..
			vector<Cell> cell_list;
			vector<Cell> new_cell_list;

			while (!q.empty()) {
				Cell cell = q.front();
				q.pop();
				++cell.time;

				// 비활성-> 활성
				if (cell.state == 0 && cell.time == cell.val) {
					cell.state = 1;
				}
				// 활성 + 1시간 번식
				else if (cell.state == 1 && cell.time == cell.val + 1) {
					for (int d = 0; d < 4; d++) {
						int nx = cell.x + dir[d][0], ny = cell.y + dir[d][1];
						new_cell_list.push_back({ nx, ny, cell.val, 0, 0 });						
					}
				}

				// 활성-> 사망
				if (cell.state == 1 && cell.time == cell.val * 2) continue;
				cell_list.push_back(cell);				
			}	
			// 기존 cell q에추가
			for (auto cell : cell_list) {
				q.push(cell);
			}

			sort(new_cell_list.begin(), new_cell_list.end(), cmp);
			for (auto new_cell : new_cell_list) {
				if (checked.insert({ new_cell.x, new_cell.y }).second == false) continue;
				q.push(new_cell);
			}			
		}		

		cout <<"#" <<tc << " "<< q.size() << endl;
	}

}