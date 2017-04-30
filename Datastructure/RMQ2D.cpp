#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN^2)
*/
template<class T, class cmp = less<T> > struct RMQ2D {
    static const int MAXN = 1e3 + 5;
    static const int MAXM = 1e3 + 5;
    static const int LOGN = 10 + 1;
    static const int LOGM = 10 + 1;
    int n, m;
    T a[MAXN][MAXM];
    T f[LOGM][MAXN][MAXM];
    T g[LOGM][LOGN][MAXM][MAXN];
    
    T best(T a, T b) {
        if (cmp()(a, b)) return a;
        return b;
    }
    void build() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= m; i++) {
                f[0][k][i] = a[k - 1][i - 1];
            }
            for (int j = 1; 1 << j <= m; j++) {
                for (int i = 0; i + (1 << j) - 1 <= m; i++) {
                    f[j][k][i] = best(f[j - 1][k][i], f[j - 1][k][i + (1 << (j - 1))]);
                }
            }
        }
        for (int k = 1; k <= m; k++) {
            for (int l = 0; k + (1 << l) - 1 <= m; l++) {
                for (int i = 1; i <= n; i++) {
                    g[l][0][k][i] = f[l][i][k];
                }
                for (int j = 1; 1 << j <= n; j++) {
                    for (int i = 0; i + (1 << j) - 1 <= n; i++) {
                        g[l][j][k][i] = best(g[l][j - 1][k][i], g[l][j - 1][k][i + (1 << (j - 1))]);
                    }
                }
            }
        }
    }
    T query(int x, int y, int z, int t) {
        x++, y++, z++, t++;
        int a = z - x + 1, b = t - y + 1;
        int lga = __lg(a);
        int lgb = __lg(b);
        int res = g[lgb][lga][y][x];
        res = best(res, g[lgb][lga][y + b - (1 << (lgb))][x + a - (1 << (lga))]);
        res = best(res, g[lgb][lga][y][x + a - (1 << (lga))]);
        res = best(res, g[lgb][lga][y + b - (1 << (lgb))][x]);
        return res;
    }
};

RMQ2D<int> rmq;

int main() {
    srand(time(NULL));
    for (int it = 0; it < 10; it++) {
        rmq.n = rmq.m = rand() % 1000 + 1;
        for (int i = 0; i < rmq.n; i++) {
            for (int j = 0; j < rmq.m; j++) {
                rmq.a[i][j] = rand();
            }
        }
        rmq.build();
        int q = rand() % 100;
        while (q--) {
            int u = rand() % rmq.n, v = rand() % rmq.m;
            int x = rand() % rmq.n, y = rand() % rmq.m;
            if (u > x) swap(u, x);
            if (v > y) swap(v, y);
            int r1 = rmq.query(u, v, x, y);
            int r2 = (int) 1e9;
            for (int i = u; i <= x; i++) {
                for (int j = v; j <= y; j++) {
                    r2 = min(r2, rmq.a[i][j]);
                }
            }
            assert(r1 == r2);
        }
    }
    cout << "Correct!\n";
    return 0;
}
