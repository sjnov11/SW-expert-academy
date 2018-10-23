#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

struct Atom {
	double x;
	double y;
	int dir;
	int energy;
	bool end;
};


double delta[4][2] = { { 0, 0.5 },{ 0, -0.5 },{ -0.5, 0 },{ 0.5, 0 } };
int collision[4001][4001];

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		vector<Atom> atom_list;
		int N;
		cin >> N;
		atom_list.resize(N);
		for (int i = 0; i < N; i++) {
			double x, y;
			int dir, energy;
			cin >> x >> y >> dir >> energy;
			atom_list[i] = { x,y,dir, energy, false };
		}

		int answer = 0;
		for (int simulation = 0; simulation < 2000; simulation++) {
			printf("%d\n", simulation);
			for (int i = 0; i < atom_list.size(); i++) {
				if (atom_list[i].end) continue;
				atom_list[i].x += delta[atom_list[i].dir][0];
				atom_list[i].y += delta[atom_list[i].dir][1];

			}

			for (int i = 0; i < 4001; i++) {
				for (int j = 0; j < 4001; j++) {
					collision[i][j] = -1;
				}
			}
			if (atom_list[0].x == -500.0) {
				printf("d\n");
			}
			for (int i = 0; i < atom_list.size(); i++) {
				if (atom_list[i].end) continue;
				int m = (atom_list[i].x + 1000) * 2;
				int n = (atom_list[i].y + 1000) * 2;
				if (collision[m][n] != -1) {
					atom_list[i].end = true;
					atom_list[collision[m][n]].end = true;
				}
				else {
					collision[m][n] = i;
				}
			}
		}
			/*map<pair<double, double>, int> m;
			for (int i = 0; i < atom_list.size(); i++) {
				if (atom_list[i].end) continue;
				auto it = m.find({ atom_list[i].x, atom_list[i].y });
				if (it == m.end()) {
					m[{atom_list[i].x, atom_list[i].y}] = i;
				}
				else {
					atom_list[it->second].end = true;
					atom_list[i].end = true;
				}
			}
		}*/

		for (int i = 0; i < atom_list.size(); i++) {
			if (atom_list[i].end)
				answer += atom_list[i].energy;
		}

			cout << "#" << tc << " " << answer << endl;
		
	}
}