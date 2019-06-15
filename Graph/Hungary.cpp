#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(n^3)
 * Indexing from 1
 */
template<class T, T oo> struct Hungary {
    static const int MAXN = 1000 + 5;
    static const int MAXM = 1000 + 5;
    int nx, ny, maty[MAXM], frm[MAXM], used[MAXM];
    T cst[MAXN][MAXM], fx[MAXN], fy[MAXM], dst[MAXM];
    void init(int nx, int ny) {
        this->nx = nx, this->ny = ny;
        fill_n(fx, nx + 1, 0), fill_n(fy, ny + 1, 0);
        fill_n(maty, nx + 1, 0);
        for (int i = 0; i <= nx; i++) {
            fill_n(cst[i], ny + 1, oo);
        }
    }
    void add(int x, int y, int c) {
        cst[x][y] = c;
    }
    T mincost() {
        for (int x = 1; x <= nx; x++) {
            int y0 = 0;
            maty[0] = x;
            for (int y = 0; y <= ny; y++) {
                dst[y] = oo + 1;
                used[y] = 0;
            }
            do {
                used[y0] = 1;
                int x0 = maty[y0], y1;
                T delta = oo + 1;
                for (int y = 1; y <= ny; y++) if (!used[y]) {
                    T curdst = cst[x0][y] - fx[x0] - fy[y];
                    if (dst[y] > curdst) {
                        dst[y] = curdst;
                        frm[y] = y0;
                    }
                    if (delta > dst[y]) {
                        delta = dst[y];
                        y1 = y;
                    }
                }
                for (int y = 0; y <= ny; y++) if (used[y]) {
                    fx[maty[y]] += delta;
                    fy[y] -= delta;
                }
                else {
                    dst[y] -= delta;
                }
                y0 = y1;
            }
            while (maty[y0] != 0);
            do {
                int y1 = frm[y0];
                maty[y0] = maty[y1];
                y0 = y1;
            }
            while (y0);
        }
        T res = 0;
        for (int y = 1; y <= ny; y++) {
            int x = maty[y];
            if (cst[x][y] < oo) res += cst[x][y];
        }
        return res;
    }
};
Hungary<int, (int) 1e9> hungary;

int main() {
    hungary.init(3, 3);
    hungary.add(1, 2, 3);
    hungary.add(1, 2, 1);
    cout << hungary.mincost() << "\n";
    return 0;
}
