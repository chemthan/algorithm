#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    static const int MAXN = 100;
    static const int MOD = (int) 1e9 + 7;
    int x[MAXN][MAXN];
    
    Matrix() {
        memset(x, 0, sizeof(x));
    }
    static Matrix unit() {
        Matrix res;
        for (int i = 0; i < MAXN; i++) res.x[i][i] = 1;
        return res;
    }
    Matrix operator + (Matrix A) {
        Matrix res;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res.x[i][j] = x[i][j] + A.x[i][j];
            if (res.x[i][j] >= MOD) res.x[i][j] -= MOD;
        }
        return res;
    }
    Matrix operator * (Matrix A) {
        Matrix res;
        for (int i = 0; i < MAXN; i++) for (int k = 0; k < MAXN; k++) for (int j = 0; j < MAXN; j++) {
            res.x[i][j] = (res.x[i][j] + (long long) x[i][k] * A.x[k][j]) % MOD;
        }
        return res;
    }
    Matrix operator ^ (long long k) {
        if (k == 0) return unit();
        Matrix res, tmp;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
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
    //Caculate geometric series: A^0 + A^1 + ... + A^k
    friend Matrix geometricseries(Matrix A, long long k) {
        if (k == 0) return unit();
        if (k == 1) return A;
        vector<int> bit;
        while (k) {
            bit.push_back(k & 1);
            k >>= 1;
        }
        Matrix res = A, tmp = A;
        for (int i = bit.size() - 2; i >= 0; i--) {
            res = res + (res * tmp);
            tmp = tmp * tmp;
            if (bit[i] & 1) {
                tmp = tmp * A;
                res = res + tmp;
            }
        }
        res = res + unit();
        return res;
    }
};

int main() {
	return 0;
}
