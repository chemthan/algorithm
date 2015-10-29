#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
const int mod = 1000000007;
struct matrix {
	long long x[maxn][maxn];
	matrix() {
		memset(x, 0, sizeof(x));
	}
	matrix unit() {
		matrix res;
		for (int i = 0; i < maxn; i++) res.x[i][i] = 1;
		return res;
	}
	matrix operator + (matrix A) {
		matrix res;
		for (int i = 0; i < maxn; i++) for (int j = 0; j < maxn; j++) {
				res.x[i][j] = (x[i][j] + A.x[i][j]) % mod;
			}
		return res;
	}
	matrix operator * (matrix A) {
		matrix res;
		for (int i = 0; i < maxn; i++) for (int j = 0; j < maxn; j++) {
				for (int k = 0; k < maxn; k++) res.x[i][j] = (res.x[i][j] + x[i][k] * A.x[k][j]) % mod;
			}
		return res;
	}
	matrix operator ^ (long long k) {
		matrix res, tmp;
		for (int i = 0; i < maxn; i++) for (int j = 0; j < maxn; j++) {
				res.x[i][j] = tmp.x[i][j] = x[i][j];
			}
		k--;
		while (k) {
			if (k & 1) res = res * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return res;
	}
	friend matrix cal(matrix A, long long k) {
		if (k == 1) return A;
		if (k & 1) return (A ^ k) + cal(A, k - 1);
		k >>= 1;
		matrix tmp = cal(A, k);
		return tmp + (tmp * (A ^ k));
	}
};

int main() {
	return 0;
}

