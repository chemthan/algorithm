#include <bits/stdc++.h>
using namespace std;

template<const int n, const int mod>
struct Matrix {
    int x[n][n];

    Matrix() {
        memset(x, 0, sizeof(x));
    }
    int* operator [] (int r) {
        return x[r];
    }
    static Matrix unit() {
        Matrix res;
        for (int i = 0; i < n; i++) res[i][i] = 1;
        return res;
    }
    friend Matrix operator + (Matrix A, Matrix B) {
        Matrix res;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            res[i][j] = A[i][j] + B[i][j];
            if (res[i][j] >= mod) res[i][j] -= mod;
        }
        return res;
    }
    friend Matrix operator * (Matrix A, Matrix B) {
        Matrix res;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            long long SQmod = (long long) mod * mod;
            long long sum = 0;
            for (int k = 0; k < n; k++) {
                sum += (long long) A[i][k] * B[k][j];
                if (sum >= SQmod) sum -= SQmod;
            }
            res[i][j] = sum % mod;
        }
        return res;
    }
    friend Matrix operator ^ (Matrix A, long long k) {
        if (k == 0) return unit();
        Matrix res, tmp;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
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
    srand(time(0));
    Matrix<100, (int) 1e9 + 7> mat;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            mat[i][j] = rand();
        }
    }
    mat = mat ^ ((long long) 1e18);
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
