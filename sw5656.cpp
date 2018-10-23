#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;


int block[16][13];
int N, W, H;
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int answer = 9999999;

void broken(int w, int cur_block[16][13]) {
	int h = -1;
	for (int i = 0; i < H; i++) {
		if (cur_block[i][w] != 0) {
			h = i;
			break;
		}
	}
	if (h == -1) return;
	
	queue<pair<int, int>> q;
	q.push({ h, w });
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		int x = cur.first;
		int y = cur.second;
		int num = cur_block[x][y];
		for (int i = 0; i < 4; i++) {
			int dx = dir[i][0];
			int dy = dir[i][1];
			for (int j = 1; j < num; j++) {
				int nx = x + dx * j;
				int ny = y + dy * j;
				if (nx >= 0 && nx < H && ny >= 0 && ny < W && block[nx][ny] != 0) {
					q.push({nx, ny});
				}
			}
		}
		cur_block[x][y] = 0;
	}
	return;
}

void go_down(int cur_block[16][13]) {
	int ret[16][13];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 13; j++) {
			ret[i][j] = 0;
		}
	}
	for (int i = 0; i < W; i++) {
		int cnt = 0;
		for (int j = 0 ; j < H; j++) {
			if (cur_block[j][i] == 0) continue;
			ret[cnt][i] = cur_block[j][i];
			cnt++;
		}
		for (int j = 0; j < H; j++) {
			cur_block[j][i] = 0;
		}
		for (int j = 0; j < H; j++) {
			
			if (j + H - cnt >= 0 && j + H - cnt < H)
				cur_block[j + H - cnt][i] = ret[j][i];
		}
	}

	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {
	//		cur_block[i][j] = ret[i][j];
	//	}
	//}	
}

int count(int cur_block[16][13]) {
	int ret = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (cur_block[i][j] != 0) {
				ret++;
			}
		}
	}
	return ret;
}


void go(int cnt, int cur_block[16][13]) {
	// All selected
	if (cnt == N) {
		int remain = count(cur_block);
		answer = min(answer, remain);
		return;
	}
	int temp[16][13];
	

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			for (int k = 0; k < W; k++) {
				temp[j][k] = cur_block[j][k];
			}
		}
		broken(i, temp);
		go_down(temp);
		go(cnt + 1, temp);
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
				cin >> block[i][j];
			}
		}
		go(0, block);
		cout << "#" << tc << " " <<  answer << endl;
	}
	////broken(2, block);
	////go_down(block);
	////cout << "-==========" << endl;
	////for (int i = 0; i < H; i++) {
	////	for (int j = 0; j < W; j++) {
	////		cout << block[i][j] << " ";
	////	}
	////	cout << endl;
	////}
	////broken(2, block);
	////go_down(block);
	////cout << "-==========" << endl;
	////for (int i = 0; i < H; i++) {
	////	for (int j = 0; j < W; j++) {
	////		cout << block[i][j] << " ";
	////	}
	////	cout << endl;
	////}
	////broken(6, block);
	////go_down(block);
	////cout << "-==========" << endl;
	////for (int i = 0; i < H; i++) {
	////	for (int j = 0; j < W; j++) {
	////		cout << block[i][j] << " ";
	////	}
	////	cout << endl;
	////}
	////cout << count(block) << endl;
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {
	//		cout << block[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << "-==========" << endl;
	//go_down(block);
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {
	//		cout << block[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}