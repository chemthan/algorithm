#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N^2M)
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
MATRIX ModularGauss(MATRIX a, int mod) {
    int n = a.size(), m = a[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = (a[i][j] % mod + mod) % mod;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        pair<int, int> best;
        for (int j = i; j < n; j++) {
            best = max(best, make_pair(a[j][i], j));
        }
        if (!best.first) continue;
        int idx = best.second;
        swap(a[i], a[idx]);
        for (int j = i + 1; j < n; j++) {
            for (int k = i + 1; k < m; k++) {
                a[j][k] = (long long) a[j][k] * a[i][i] % mod - (long long) a[j][i] * a[i][k] % mod;
                if (a[j][k] < 0) a[j][k] += mod;
            }
            a[j][i] = 0;
        }
    }
    for (int i = 0; i < n; i++) if (a[i][i]) {
        for (int j = i + 1; j < m; j++) {
            a[i][j] = (long long) a[i][j] * inv(a[i][i], mod) % mod;
        }
        a[i][i] = 1;
    }
    return a;
}

int main() {
    srand(time(NULL));
    int n = 3, m = 4, mod = (int) 1e9 + 7;
    MATRIX a(n, ROW(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = rand() % mod;
        }
    }
    a = ModularGauss(a, mod);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " \n"[j == m - 1];
        }
    }
    return 0;
}
