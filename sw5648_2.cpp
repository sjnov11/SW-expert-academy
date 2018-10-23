#include <iostream>
#include <vector>
using namespace std;

struct Atom {
	int x, y, dir, energy;
};

int main() {
	vector<Atom> atom_list;
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, d, e;
		cin >> x >> y >> d >> e;
		atom_list.push_back({ x,y,d,e });
	}


}