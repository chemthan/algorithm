#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(logN)
 * Necessary and sufficient condition: Two functions have at most one common point
 * Problem:
 * 1. http://vn.spoj.com/problems/VOMARIO/Problems
 */
template<class T, const T oo> struct MagicTree {
    struct Func {
        T a, b;
        Func() {a = 0, b = oo;}
        Func(T a, T b) : a(a), b(b) {}
        T query(T x) {
            return a * x + b;
        }
    };

    static const int maxn = 1e5 + 5;
    Func st[maxn << 2];

    void init(int n = maxn) {
        fill_n(st, n << 2, Func());
    }
    void upd(int p, int l, int r, int L, int R, Func fun) {
        int M = L + R >> 1;
        if (l > R || r < L) return;
        if (l <= L && r >= R) {
            int fl = fun.query(L) >= st[p].query(L);
            int fr = fun.query(R) >= st[p].query(R);
            int fm1 = fun.query(M) >= st[p].query(M);
            int fm2 = fun.query(M + 1) >= st[p].query(M + 1);
            if (fl && fr) return;
            if (!fl && !fr) {
                st[p] = fun;
                return;
            }
            if (fl && fm1) {
                upd(p << 1 | 1, l, r, M + 1, R, fun);
                return;
            }
            if (!fl && !fm1) {
                upd(p << 1 | 1, l, r, M + 1, R, st[p]);
                st[p] = fun;
                return;
            }
            if (fm2 && fr) {
                upd(p << 1, l, r, L, M, fun);
                return;
            }
            if (!fm2 && !fr) {
                upd(p << 1, l, r, L, M, st[p]);
                st[p] = fun;
                return;
            }
            assert(0);
        }
        else if (L < R) {
            upd(p << 1, l, r, L, L + R >> 1, fun);
            upd(p << 1 | 1, l, r, (L + R >> 1) + 1, R, fun);
        }
    }
    void upd(int p, int l, int r, int L, int R, T a, T b) {
        upd(p, l, r, L, R, Func(a, b));
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
