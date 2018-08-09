#include <bits/stdc++.h>
using namespace std;

/*
* Recurrence formula: x[i] = c[k - 1] * x[i - 1] + c[k - 2] * x[i - 2] + ... + c[0] * x[i - k]
* x[0], x[1],..., x[2 * k - 1] are given
* Return c[0], c[1],..., c[k - 1]
*/
struct InvertRecurrence {
    static const int MOD = (int) 1e9 + 7;
    static const int MAXN = 1000 + 5;
    int k;
    int x[MAXN << 1];
    int c[MAXN];
    int a[MAXN][MAXN];
    
    int fpow(int n, int k, int p = MOD) {
        int r = 1;
        for (; k; k >>= 1) {
            if (k & 1) r = (long long) r * n % p;
            n = (long long) n * n % p;
        }
        return r;
    }
    void gauss() {
        int n = k, m = k + 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = (a[i][j] % MOD + MOD) % MOD;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            pair<int, int> best;
            for (int j = i; j < n; j++) {
                best = max(best, make_pair(a[j][i], j));
            }
            if (!best.first) return;
            int idx = best.second;
            for (int j = i; j < m; j++) {
                swap(a[i][j], a[idx][j]);
            }
            for (int j = i + 1; j < n; j++) {
                for (int k = i + 1; k < m; k++) {
                    a[j][k] = ((long long) a[j][k] * a[i][i] % MOD - (long long) a[j][i] * a[i][k] % MOD + MOD) % MOD;
                }
                a[j][i] = 0;
            }
        }
        for (int i = 0; i < n; i++) if (a[i][i]) {
            for (int j = i + 1; j < m; j++) {
                a[i][j] = (long long) a[i][j] * fpow(a[i][i], MOD - 2) % MOD;
            }
            a[i][i] = 1;
        }
    }
    void solve() {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                a[i][j] = x[i + j];
            }
            a[i][k] = x[i + k];
        }
        gauss();
        for (int i = k - 1; i >= 0; i--) {
            int t = 0;
            for (int j = i + 1; j < k; j++) {
                t = (t + (long long) a[i][j] * c[j]) % MOD;
            }
            c[i] = (a[i][k] - t + MOD) % MOD;
        }
    }
} ir;

const int MOD = (int) 1e9 + 7;

int main() {
    srand(time(NULL));
    ir.k = 10;
    for (int i = 0; i < ir.k; i++) {
        ir.x[i] = rand() % MOD;
        ir.c[i] = rand() % MOD;
    }
    for (int i = ir.k; i < (ir.k << 1); i++) {
        for (int j = 0; j < ir.k; j++) {
            ir.x[i] = (ir.x[i] + (long long) ir.c[ir.k - j - 1] * ir.x[i - j - 1]) % MOD;
        }
    }
    for (int i = 0; i < ir.k; i++) {
        cout << ir.c[i] << " \n"[i == ir.k - 1];
    }
    ir.solve();
    for (int i = 0; i < ir.k; i++) {
        cout << ir.c[i] << " \n"[i == ir.k - 1];
    }
    cout << "Correct!\n";
    return 0;
}
