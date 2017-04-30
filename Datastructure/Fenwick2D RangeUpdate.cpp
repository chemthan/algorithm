#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN^2)
* Problems:
1. http://codeforces.com/contest/341/problem/D
*/
template<class T> struct RangeFenwick2D {
    int n, m;
    vector<vector<T> > fen[4];
    
    RangeFenwick2D(int n, int m) {
        this->n = n, this->m = m;
        for (int i = 0; i < 4; i++) {
            fen[i].resize(n + 1, vector<T>(m + 1));
        }
    }
    void upd(int x, int y, T val) {
        assert(x > 0 && y > 0);
        for (int xx = x; xx <= n; xx += xx & -xx) {
            for (int yy = y; yy <= m; yy += yy & -yy) {
                fen[0][xx][yy] += val;
                fen[1][xx][yy] += x * val;
                fen[2][xx][yy] += y * val;
                fen[3][xx][yy] += x * y * val;
            }
        }
    }
    void upd(int x, int y, int z, int t, T val) {
        upd(x, y, +val);
        upd(x, t + 1, -val);
        upd(z + 1, y, -val);
        upd(z + 1, t + 1, +val);
    }
    T query(int x, int y) {
        assert(x <= n && y <= m);
        T res = 0;
        for (int xx = x; xx > 0; xx -= xx & -xx) {
            for (int yy = y; yy > 0; yy -= yy & -yy) {
                res += (x + 1) * (y + 1) * fen[0][xx][yy];
                res -= (y + 1) * fen[1][xx][yy];
                res -= (x + 1) * fen[2][xx][yy];
                res += fen[3][xx][yy];
            }
        }
        return res;
    }
    T query(int x, int y, int z, int t) {
        return query(z, t) - query(x - 1, t) - query(z, y - 1) + query(x - 1, y - 1);
    }
};

const int maxn = 1e3 + 5;
int n, m, q;
int a[maxn][maxn];

int main() {
    srand(time(NULL));
    for (int it = 0; it < 10; it++) {
        n = rand() % 1000 + 1, m = rand() % 1000 + 1, q = rand() % 1000 + 1;
        RangeFenwick2D<long long> rf2d(n, m);
        for (int i = 0; i <= n; i++) fill_n(a[i], m + 1, 0);
        while (q--) {
            if (rand() % 2 == 0) {
                int x = rand() % n, y = rand() % m, z = rand() % n, t = rand() % m, val = rand() % 100;
                if (x > z) swap(x, z);
                if (y > t) swap(y, t);
                rf2d.upd(x + 1, y + 1, z + 1, t + 1, val);
                for (int i = x; i <= z; i++) {
                    for (int j = y; j <= t; j++) {
                        a[i][j] += val;
                    }
                }
            }
            else {
                int x = rand() % n, y = rand() % m, z = rand() % n, t = rand() % m;
                if (x > z) swap(x, z);
                if (y > t) swap(y, t);
                long long ans = 0;
                for (int i = x; i <= z; i++) {
                    for (int j = y; j <= t; j++) {
                        ans += a[i][j];
                    }
                }
                assert(rf2d.query(x + 1, y + 1, z + 1, t + 1) == ans);
            }
        }
    }
    cout << "Correct!\n";
    return 0;
}
