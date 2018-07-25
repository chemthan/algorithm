#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    static const int MAXN = 100;
    static const int MOD = (int) 1e9 + 7;
    int x[MAXN][MAXN];
    
    Matrix() {
        memset(x, 0, sizeof(x));
    }
    int* operator [] (int r) {
        return x[r];
    }
    static Matrix unit() {
        Matrix res;
        for (int i = 0; i < MAXN; i++) res[i][i] = 1;
        return res;
    }
    friend Matrix operator + (Matrix A, Matrix B) {
        Matrix res;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res[i][j] = A[i][j] + B[i][j];
            if (res[i][j] >= MOD) res[i][j] -= MOD;
        }
        return res;
    }
    friend Matrix operator * (Matrix A, Matrix B) {
        Matrix res;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            long long SQMOD = (long long) MOD * MOD;
            long long sum = 0;
            for (int k = 0; k < MAXN; k++) {
                sum += (long long) A[i][k] * B[k][j];
                if (sum >= SQMOD) sum -= SQMOD;
            }
            res[i][j] = sum % MOD;
        }
        return res;
    }
    friend Matrix operator ^ (Matrix A, long long k) {
        if (k == 0) return unit();
        Matrix res, tmp;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res[i][j] = tmp[i][j] = A[i][j];
        }
        k--;
        while (k) {
            if (k & 1) res = res * tmp;
            tmp = tmp * tmp;
            k >>= 1;
        }
        return res;
    }
    //Calculate geometric series: A^0 + A^1 + ... + A^k
    friend Matrix geometricseries(Matrix A, long long k) {
        if (k == 0) return unit();
        if (k == 1) return A + unit();
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
