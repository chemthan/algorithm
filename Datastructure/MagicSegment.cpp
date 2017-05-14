#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
* Necessary and sufficient condition: Two functions have at most one common point
* Problem:
* 1. http://vn.spoj.com/problems/VOMARIO/Problems
*/
template<class T, const T oo> struct MagicSegmentTree {
    struct Function {
        T a, b;
        Function() {a = 0, b = oo;}
        Function(T a, T b) : a(a), b(b) {}
        T query(T x) {
            return a * x + b;
        }
    };
    
    static const int MAXN = 1e5 + 5;
    Function st[MAXN << 2];
    
    void init(int n = MAXN) {
        fill_n(st, n << 2, Function());
    }
    void upd(int p, int l, int r, int L, int R, Function fun) {
        int M = L + R >> 1;
        if (l > R || r < L) return;
        if (l <= L && r >= R) {
            if (fun.query(L) >= st[p].query(L) && fun.query(R) >= st[p].query(R)) {
                return;
            }
            if (fun.query(L) <= st[p].query(L) && fun.query(R) <= st[p].query(R)) {
                st[p] = fun;
                return;
            }
            if (fun.query(L) >= st[p].query(L) && fun.query(M) >= st[p].query(M)) {
                upd(p << 1 | 1, l, r, M + 1, R, fun);
                return;
            }
            if (fun.query(L) <= st[p].query(L) && fun.query(M) <= st[p].query(M)) {
                upd(p << 1 | 1, l, r, M + 1, R, st[p]);
                st[p] = fun;
                return;
            }
            if (fun.query(M + 1) >= st[p].query(M + 1) && fun.query(R) >= st[p].query(R)) {
                upd(p << 1, l, r, L, M, fun);
                return;
            }
            if (fun.query(M + 1) <= st[p].query(M + 1) && fun.query(R) <= st[p].query(R)) {
                upd(p << 1, l, r, L, M, st[p]);
                st[p] = fun;
                return;
            }
        }
        else if (L < R) {
            upd(p << 1, l, r, L, L + R >> 1, fun);
            upd(p << 1 | 1, l, r, (L + R >> 1) + 1, R, fun);
        }
    }
    void upd(int p, int l, int r, int L, int R, T a, T b) {
        upd(p, l, r, L, R, Function(a, b));
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
MagicSegmentTree<int, (int) 1e9> mseg;

int main() {
    return 0;
}
