#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(N)
 * f[j] = min(b[i][j] = d[i] + w[i][j]), 0 <= i < j
 * d[i] is computed from f[i] in constant time
 * Sufficient condition: w[a][c] + w[b][d] <= w[b][c] + w[a][d], a <= b <= c <= d
 * Problem:
 * 1. http://codeforces.com/problemset/problem/319/C
 */

const int ar[9][18] = {
    {25, 21, 13, 10, 20, 13, 19, 35, 37, 41, 58, 66, 82, 99, 124, 133, 156, 178},
    {42, 35, 26, 20, 29, 21, 25, 37, 36, 39, 56, 64, 76, 91, 116, 125, 146, 164},
    {57, 48, 35, 28, 33, 24, 28, 40, 37, 37, 54, 61, 72, 83, 107, 113, 131, 146},
    {78, 65, 51, 42, 44, 35, 38, 48, 42, 42, 55, 61, 70, 80, 100, 106, 120, 135},
    {90, 76, 58, 48, 49, 39, 42, 48, 39, 35, 47, 51, 56, 63, 80, 86, 97, 110},
    {103, 85, 67, 56, 55, 44, 44, 49, 39, 33, 41, 44, 49, 56, 71, 75, 84, 96},
    {123, 105, 86, 75, 73, 59, 57, 62, 51, 44, 50, 52, 55, 59, 72, 74, 80, 92},
    {142, 123, 100, 86, 82, 65, 61, 62, 50, 43, 47, 45, 46, 46, 58, 59, 65, 73},
    {151, 130, 104, 88, 80, 59, 52, 49, 37, 29, 29, 24, 23, 20, 28, 25, 31, 39}
};

typedef int num_t;
const num_t oo = (num_t) 1e9;
namespace _1D1D {
    const int maxn = 1e5 + 5;
    const int logn = 20;
    int r, c;
    num_t f[maxn];
    num_t g[maxn];
    int h[maxn];
    int cols[logn][maxn];

    inline num_t D(int i) {return f[i];} //Need to modify
    inline num_t W(int i, int j) {return ar[i][j];} //Need to modify
    inline num_t B(int i, int j) {return D(i) + W(i, j);}
    inline num_t lookup(int j, int i) {if (!i) return g[j + c]; return B(i + r - 1, j + c);}

    void SMAWK(int n, int inc, int ncol, int row_minima[]) {
        int row_size = (n + inc - 1) / inc;
        int lev = __lg(inc);
        int* col = cols[lev];
        static int sub_col[maxn];
        int num = 0;
        for (int i = 0; i < ncol; i++) {
            while (num && lookup(inc * (num - 1), sub_col[num - 1]) >= lookup(inc * (num - 1), col[i]))
                num--;
            if (num < row_size) sub_col[num++] = col[i];
        }
        ncol = num, col = cols[lev + 1];
        for (int i = 0; i < ncol; i++) col[i] = sub_col[i];
        if (row_size == 1) {
            row_minima[0] = col[0];
            return;
        }
        SMAWK(n, inc << 1, ncol, row_minima);
        for (int i = inc, c = 0; i < n; i += 2 * inc) {
            int pre = row_minima[i - inc];
            int next = (i + inc < n) ? row_minima[i + inc] : col[ncol - 1];
            while (c < ncol && col[c] < pre) c++;
            int& res = row_minima[i];
            res = col[c];
            while (c < ncol && col[c] <= next) {
                if (lookup(i, col[c]) <= lookup(i, res)) res = col[c];
                c++;
            }
            c--;
        }
    }
    void SMAWK(int n, int m, int row_minima[]) {
        for (int i = 0; i < m; i++) cols[0][i] = i;
        SMAWK(n, 1, m, row_minima);
    }
    num_t solve(int n) {
        /*for (int a = 0; a < n; a++) {
            for (int b = a; b < n; b++) {
                for (int c = b; c < n; c++) {
                    for (int d = c; d < n; d++) {
                        assert(W(a, c) + W(b, d) <= W(a, d) + W(b, c));
                    }
                }
            }
        }*/
        r = 0, c = 1;
        f[0] = 0; //Need to modify
        fill_n(g, n, +oo);
        while (c < n) {
            int p = min(2 * c - r, n - 1);
            SMAWK(p - c + 1, c - r + 1, h + c);
            f[c] = lookup(c - c, h[c]);
            int j = 0;
            for (j = c + 1; j <= p; j++) {
                if (B(j - 1, j) < lookup(j - c, h[j])) {
                    f[j] = B(j - 1, j);
                    break;
                }
                else {
                    f[j] = lookup(j - c, h[j]);
                    if (B(j - 1, p) < lookup(p - c, h[p])) {
                        for (int k = j + 1; k <= p; k++) {
                            g[k] = lookup(k - c, h[k]);
                        }
                        break;
                    }
                }
            }
            if (j <= p) {
                c = j + 1;
                r = j - 1;
            }
            else {
                c = p + 1;
                if (h[p]) r += h[p] - 1;
            }
        }
        return f[n - 1];
    }
}

int main() {
    int n = 9;
    cout << _1D1D::solve(n) << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            assert(_1D1D::f[i] <= _1D1D::D(j) + _1D1D::W(j, i));
        }
        cout << _1D1D::f[i] << " \n"[i == n - 1];
    }
    return 0;
}
