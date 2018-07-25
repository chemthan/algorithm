#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(logN)
 * Necessary and sufficient condition: Two functions have at most one common point
 * Problem:
 * 1. http://vn.spoj.com/problems/VOMARIO/Problems
 */
template<class T, const T oo> struct MagicTree {
    struct func_t {
        T a, b;
        func_t(T a = 0, T b = oo) : a(a), b(b) {}
        T query(T x) {return a * x + b;}
    };

    static const int maxn = 1e5 + 5;
    func_t st[maxn << 2];

    void init(int n = maxn) {
        fill_n(st, n << 2, func_t());
    }
    void upd(int p, int l, int r, int L, int R, func_t f) {
        int M = L + R >> 1;
        if (l > R || r < L) return;
        if (l <= L && r >= R) {
            int fl = f.query(L) >= st[p].query(L);
            int fr = f.query(R) >= st[p].query(R);
            int fm1 = f.query(M) >= st[p].query(M);
            int fm2 = f.query(M + 1) >= st[p].query(M + 1);
            if (fl && fr) return;
            if (!fl && !fr) {
                st[p] = f;
                return;
            }
            if (fl && fm1) {
                upd(p << 1 | 1, l, r, M + 1, R, f);
                return;
            }
            if (!fl && !fm1) {
                upd(p << 1 | 1, l, r, M + 1, R, st[p]);
                st[p] = f;
                return;
            }
            if (fm2 && fr) {
                upd(p << 1, l, r, L, M, f);
                return;
            }
            if (!fm2 && !fr) {
                upd(p << 1, l, r, L, M, st[p]);
                st[p] = f;
                return;
            }
            assert(0);
        }
        else if (L < R) {
            upd(p << 1, l, r, L, L + R >> 1, f);
            upd(p << 1 | 1, l, r, (L + R >> 1) + 1, R, f);
        }
    }
    void upd(int p, int l, int r, int L, int R, T a, T b) {
        upd(p, l, r, L, R, func_t(a, b));
    }
    T query(int p, int i, int L, int R) {
        if (i < L || i > R) return oo;
        T res = st[p].query(i);
        if (L < R) {
            res = min(res, query(p << 1, i, L, L + R >> 1));
            res = min(res, query(p << 1 | 1, i, (L + R >> 1) + 1, R));
        }
        return res;
    }
};
MagicTree<int, (int) 1e9> mgtree;

int main() {
    return 0;
}
