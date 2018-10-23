#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, M;
		cin >> N >> M;

		vector<int> adj_list[501];
		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			adj_list[a].push_back(b);
			adj_list[b].push_back(a);
		}

		bool visited[501];
		for (int i = 1; i <= N; i++) {
			visited[i] = false;
		}

		queue<int> q;
		visited[1] = true;
		int answer = 0;

		for (auto next : adj_list[1]) {
			q.push(next);
			visited[next] = true;
			answer++;
		}

		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			for (auto next : adj_list[cur]) {
				if (visited[next]) continue;
				visited[next] = true;
				answer++;
			}
		}
		cout << "#" << tc << " " <<  answer << endl;
	}
}