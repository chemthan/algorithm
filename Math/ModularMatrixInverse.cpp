#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N^3)
*/
typedef vector<int> ROW;
typedef vector<ROW> MATRIX;
int fpow(int n, int k, int p) {
    int r = 1;
    for (; k; k >>= 1) {
        if (k & 1) r = (long long) r * n % p;
        n = (long long) n * n % p;
    }
    return r;
}
int inv(int n, int p) {
    return fpow(n, p - 2, p);
}
MATRIX MatrixInverse(MATRIX matrix, int mod) {
    MATRIX res;
    int i, j, k, n = matrix.size();
    res.resize(n);
    for (i = 0; i < n; i++) {
        res[i].resize(n);
        for (j = 0; j < n; j++) res[i][j] = 0;
        res[i][i] = 1 % mod;
    }
    for (i = 0; i < n; i++) {
        if (matrix[i][i] == 0) {
            for (j = i + 1; j < n; j++) {
                if (matrix[j][i] != 0) {
                    for (k = 0; k < n; k++) {
                        matrix[i][k] += matrix[j][k];
                        if (matrix[i][k] >= mod) matrix[i][k] -= mod;
                        res[i][k] += res[j][k];
                        if (res[i][k] >= mod) res[i][k] -= mod;
                    }
                    break;
                }
            }
            if (j == n) {
                res.clear();
                return res;
            }
        }
        int tmp = inv(matrix[i][i], mod);
        for (k = 0; k < n; k++) {
            matrix[i][k] = (long long) matrix[i][k] * tmp % mod;
            res[i][k] = (long long) res[i][k] * tmp % mod;
        }
        for (j = 0; j < n; j++) {
            if (j == i) continue;
            tmp = matrix[j][i];
            for (k = 0; k < n; k++) {
                matrix[j][k] -= (long long) matrix[i][k] * tmp % mod;
                if (matrix[j][k] < 0) matrix[j][k] += mod;
                res[j][k] -= (long long )res[i][k] * tmp % mod;
                if (res[j][k] < 0) res[j][k] += mod;
            }
        }
    }
    return res;
}

int main() {
    srand(time(NULL));
    int n = 100, mod = (int) 1e9 + 7;
    MATRIX a(n, ROW(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % mod;
        }
    }
    MATRIX ia = MatrixInverse(a, mod);
    MATRIX b(n, ROW(n, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = (b[i][j] + (long long) a[i][k] * ia[k][j]) % mod;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (b[i][i] != 1) {
            cout << "Wrong!\n";
            return 0;
        }
        for (int j = 0; j < n; j++) {
            if (i != j && b[i][j]) {
                cout << "Wrong!\n";
                return 0;
            }
        }
    }
    cout << "Correct!\n";
    return 0;
}
