#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int board[16][13];
//bool visited[16][13];
int N, W, H;
int dir[4][2] = { {-1,0}, {1,0},{0,-1}, {0,1} };
int answer = 99999999;

bool onBoard(pair<int, int> pos) {
	int x = pos.first, y = pos.second;
	return x >= 0 && x < H && y >= 0 && y < W;
}

void removeOnBoard(set<pair<int, int>> remove_list) {
	for (auto pos : remove_list) {
		board[pos.first][pos.second] = 0;
	}
}
void swap(int *a, int *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

void moveDownBlocks() {
	for (int w = 0; w < W; w++) {
		for (int h = H - 1; h >= 0; h--) {
			if (board[h][w] != 0)  continue;
			int empty_h = h;
			int fill_h = empty_h - 1;
			for (fill_h = empty_h - 1; fill_h >= 0; fill_h--) {
				if (board[fill_h][w] == 0) continue;
				swap(&board[empty_h][w], &board[fill_h][w]);
				break;
			}
			if (fill_h == H) break;
		}
	}
}
//
//void dropBall(int w) {
//	// 벽돌 시작점
//	int h;
//	for (h = 0; h < H; h++) {
//		if (board[h][w] != 0) break;
//	}
//	if (h == H) return;	// 벽돌이 없어
//	queue<pair<int, int>> q;
//	//set<pair<int, int>> remove_list;
//
//	q.push({ h,w });
//	//visited[h][w] = true;
//
//	while (!q.empty()) {
//		auto block = q.front();
//		q.pop();
//		int bx = block.first, by = block.second;
//
//		//remove_list.insert(block);
//
//		int boom = board[block.first][block.second];
//		
//		for (int d = 0; d < 4; d++) {
//			for (int i = 1; i < boom; i++) {				
//				int nx = bx + dir[d][0] * i;
//				int ny = by + dir[d][1] * i;
//				//if (!onBoard({ nx, ny }) || visited[nx][ny] || board[nx][ny] == 0) continue;
//				//visited[nx][ny] = true;
//				if (!onBoard({ nx, ny }) || board[nx][ny] == 0) continue;				
//				q.push({ nx, ny });
//			}
//		}
//		board[bx][by] = 0;
//	}
//	//removeOnBoard(remove_list);
//	moveDownBlocks();
//}

void breakBlock(int x, int y) {
	int bomb = board[x][y];
	board[x][y] = 0;
	
	for (int d = 0; d < 4; d++) {
		for (int i = 1; i < bomb; i++) {
			int nx = x + dir[d][0]* i, ny = y + dir[d][1] * i;
			if (!onBoard({ nx, ny }) || board[nx][ny] == 0) continue;
			breakBlock(nx, ny);
		}
	}
	return;
}

void dropBall(int w) {
	//벽돌 시작점
	int h;
	for (h = 0; h < H; h++) {
		if (board[h][w] != 0) break;
	}
	if (h == H) return;	// 벽돌이 없어
	breakBlock(h, w);
	moveDownBlocks();
}
void go(int cnt) {
	if (cnt == N) {
		int block_cnt = 0;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (board[i][j] != 0) block_cnt++;
			}
		}
		answer = min(answer, block_cnt);
		return;
	}
	int temp[16][13];
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			temp[i][j] = board[i][j];			
		}
	}

	for (int w = 0; w < W; w++) {
		/*for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				visited[i][j] = false;
			}
		}*/
		dropBall(w);		
		go(cnt + 1);
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				board[i][j] = temp[i][j];
			}
		}
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		answer = 99999999;
		cin >> N >> W >> H;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> board[i][j];
			}
		}
		go(0);
		/*printf("=============\n");
		dropBall(2);
		moveDownBlocks();
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
		printf("=============\n");
		dropBall(2);
		moveDownBlocks();
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}*/
		/*printf("=============\n");
		dropBall(6);
		moveDownBlocks();
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}*/

		cout << "#" << tc << " " << answer << endl;
	}
}