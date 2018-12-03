#include <iostream>
#include <string.h>
using namespace std;

long long **cache;

long long combination(int n, int k) {
	/*if (k > n / 2) {
		k = n - k;
	}
	if (k == 0) {
		cache[n][k] = 1;
	}

	if (n == k) {
		cache[n][k] = 1;
	}

	if (cache[n][k] > 0)
		return cache[n][k];
	cache[n][k] = (combination(n - 1, k - 1) + combination(n - 1, k));
	return cache[n][k];*/
	
	for (int i = 1; i <= n; i++) {
		cache[i][0] = 1;
		cache[i][i] = 1;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 1; (j < i && j <= k); j++) {
			cache[i][j] = cache[i - 1][j - 1] + cache[i - 1][j];
			cout << i << " comb " << j << " : " << cache[i][j] << endl;
		}
	}

	return cache[n][k];
}


int main() {

	while (true) {
		int N, K;
		cin >> N >> K;
		if (N == 0 && K == 0)
			return 0;
		cache = new long long*[N + 1];
		for (int i = 0; i < N + 1; i++) {
			cache[i] = new long long[K + 1];			
			memset(cache[i], (long long)0, sizeof(long) *(K+1));
		}
		
		cout << combination(N, K) << endl;
		
		for (int i = 0; i < N + 1; i++) {
			delete [] cache[i];
		}
		delete [] cache;
	}
	
}