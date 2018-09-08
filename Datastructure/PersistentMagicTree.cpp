#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(logN)
 * Memory: O(QlogN)
 * Necessary and sufficient condition: Two functions have at most one common point
 * Problem:
 * 1. http://vn.spoj.com/problems/VOMARIO/Problems
 */
typedef int num_t;
const num_t oo = (num_t) 1e9;
struct func_t {
    num_t a, b;
    func_t(num_t a = 0, num_t b = oo) : a(a), b(b) {}
    num_t query(num_t x) {return a * x + b;}
};
struct node_t {
    node_t *l, *r;
    func_t f;
    node_t(node_t* l = 0, node_t* r = 0, func_t f = func_t()) : l(l), r(r), f(f) {}
    num_t query(num_t x) {return f.query(x);}
};
node_t* upd(node_t* p, int l, int r, int L, int R, func_t f) {
    if (l > R || r < L) return p;
    int M = L + (R - L >> 1);
    node_t* res = p ? new node_t(p->l, p->r, p->f) : new node_t();
    if (l <= L && r >= R) {
        int fl = f.query(L) >= (p ? p->query(L) : oo);
        int fr = f.query(R) >= (p ? p->query(R) : oo);
        if (fl && fr) return res;
        if (!fl && !fr) {
            res->f = f;
            return res;
        }
        int fm1 = f.query(M) >= (p ? p->query(M) : oo);
        if (fl && fm1) {
            res->r = upd(res->r, l, r, M + 1, R, f);
            return res;
        }
        if (!fl && !fm1) {
            res->r = upd(res->r, l, r, M + 1, R, res->f);
            res->f = f;
            return res;
        }
        int fm2 = f.query(M + 1) >= (p ? p->query(M + 1) : oo);
        if (fm2 && fr) {
            res->l = upd(res->l, l, r, L, M, f);
            return res;
        }
        if (!fm2 && !fr) {
            res->l = upd(res->l, l, r, L, M, res->f);
            res->f = f;
            return res;
        }
        assert(0);
    }
    res->l = upd(res->l, l, r, L, M, f);
    res->r = upd(res->r, l, r, M + 1, R, f);
    return res;
}
node_t* upd(node_t* p, int l, int r, int L, int R, num_t a, num_t b) {
    return upd(p, l, r, L, R, func_t(a, b));
}
num_t query(node_t* p, int i, int L, int R) {
    if (!p) return oo;
    if (i < L || i > R) return oo;
    num_t res = p->query(i);
    if (L < R) {
        res = min(res, query(p->l, i, L, L + R >> 1));
        res = min(res, query(p->r, i, (L + R >> 1) + 1, R));
    }
    return res;
}

int main() {
    return 0;
}
