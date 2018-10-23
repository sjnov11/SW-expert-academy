#include <iostream>
#include <math.h>
using namespace std;

int comb(int n, int k) {
	if (n - k < k) {
		k = n - k;
	}
	int answer = 1;
	
	for (int i = 1; i <= k; i++) {
		answer *= n - i + 1;
		answer /= i;
	}

	return answer;
}


int numLength(long long n) {
	int cnt = 0;
	while (n != 0) {
		n /= 10;
		cnt++;
	}

	return cnt;
}
// nlen 자릿수에서 4가 들어가는 수의 갯수
long long caseCnt(int nlen) {
	long long answer = 0;
	for (int k = 1; k <= nlen; k++) {
		answer += pow(-1, k - 1)*comb(nlen, k)*pow(10, nlen - k);
	}
	//cout << "nlen: " << nlen << " / " << answer << endl;
	return answer;
}

long long totalUp(long long N) {
	if (N < 0) N *= -1;
	long long answer = 0;
	int nlen = numLength(N);
	//cout << "nlen:" << nlen << endl;
	long long temp = pow(10, nlen - 1);
	long long N_temp = N;
	while (nlen != 1) {		
		int pos_num = N_temp / temp;
		if (pos_num <= 4) {
			answer += caseCnt(nlen - 1) * (N_temp / temp);
		}
		else {
			answer += caseCnt(nlen - 1) * (N_temp / temp - 1);
		}		
		//cout << "h:" << answer << endl;
		if (N_temp / temp > 4) {
			answer += pow(10, nlen - 1);
		}
		else if (N_temp / temp == 4) {
			answer += N_temp % temp;
			break;
		}
		
		N_temp = N_temp % temp;
		temp /= 10;
		nlen--;
	}
	if (N % 10 >= 4)
		answer++;
	//cout << "? : " << answer << endl;
	return N -answer - 1;
}



int main() {
	int T;
	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++) {
		long long A, B;
		cin >> A >> B;
		long long ta, tb;
		ta = totalUp(A);
		tb = totalUp(B);
		//cout << ta << "/ " << tb << endl;
		cout << "#" << test_case << " ";
		if (A < 0 && B < 0) {
			cout <<  ta - tb << endl;
		}
		else if (A > 0 && B > 0) {
			cout << tb - ta << endl;
		}
		else if ((A < 0 && B > 0)) {
			cout << tb + ta + 1 << endl;
		}
	}
	
	//cout << totalUp(-5) << endl;
}