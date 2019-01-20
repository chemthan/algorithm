#include <bits/stdc++.h>
using namespace std;

/*
 * SegmentTree 2D
 * Update single element, if not accumulated (min, max, gcd, ...) update an element only once
 * Comlexity: O(log(N)^2) per query
 * Space: O(N^2)
 */
#define lnode(p) (p << 1)
#define rnode(p) (p << 1 | 1)
#define mid(l, r) ((l + r) >> 1)
#define df 0
template<class num_t>
struct SegmentTree2D {
    int n, m;
    num_t* st;

    inline int inside(int L1, int R1, int L2, int R2, int l1, int r1, int l2, int r2) {
        return l1 <= L1 && R1 <= r1 && l2 <= L2 && R2 <= r2;
    }
    inline int insect(int L1, int R1, int L2, int R2, int l1, int r1, int l2, int r2) {
        if (R1 < l1 || r1 < L1) return 0;
        if (R2 < l2 || r2 < L2) return 0;
        return 1;
    }

    function<void(num_t&, const num_t&)> upd_e;

    SegmentTree2D(int _n, int _m, function<void(num_t&, const num_t&)> _upd_e) {
        n = _n, m = _m, upd_e = _upd_e;
        st = (num_t*) malloc(sizeof(num_t*) * (n * m << 4));
        fill_n(st, n * m << 4, df);
    }
    ~SegmentTree2D() {
        if (n * m) {
            free(st);
        }
    }

    void clear() {
        for (int i = 0; i < (n << 2); i++) {
            fill_n(st[i], m << 2, df);
        }
    }
    void upd(int px, int py, int i1, int i2, int L1, int R1, int L2, int R2, num_t val, int flag_x = 1) {
        if (R1 < i1 || i1 < L1) return;
        if (R2 < i2 || i2 < L2) return;
        upd_e(st[px * (m << 2) + py], val);
        if (flag_x && L1 < R1) {
            int npx = lnode(px), npy = py;
            upd(npx, npy, i1, i2, L1, mid(L1, R1), L2, R2, val, 1);

            npx = rnode(px);
            upd(npx, npy, i1, i2, mid(L1, R1) + 1, R1, L2, R2, val, 1);
        }
        if (L2 < R2) {
            int npx = px, npy = lnode(py);
            upd(npx, npy, i1, i2, L1, R1, L2, mid(L2, R2), val, 0);

            npy = rnode(py);
            upd(npx, npy, i1, i2, L1, R1, mid(L2, R2) + 1, R2, val, 0);
        }
    }
    void upd(int i1, int i2, num_t val) {
        upd(1, 1, i1, i2, 0, n - 1, 0, m - 1, val);
    }
    num_t query(int px, int py, int l1, int r1, int l2, int r2, int L1, int R1, int L2, int R2) {
        if (!insect(L1, R1, L2, R2, l1, r1, l2, r2)) return df;
        if (inside(L1, R1, L2, R2, l1, r1, l2, r2)) return st[px * (m << 2) + py];
        num_t res = df;
        if (l1 <= L1 && R1 <= r1) {
            upd_e(res, query(px, lnode(py), l1, r1, l2, r2, L1, R1, L2, mid(L2, R2)));
            upd_e(res, query(px, rnode(py), l1, r1, l2, r2, L1, R1, mid(L2, R2) + 1, R2));
        }
        else {
            upd_e(res, query(lnode(px), py, l1, r1, l2, r2, L1, mid(L1, R1), L2, R2));
            upd_e(res, query(rnode(px), py, l1, r1, l2, r2, mid(L1, R1) + 1, R1, L2, R2));
        }
        return res;
    }
    num_t query(int l1, int r1, int l2, int r2) {
        return query(1, 1, l1, r1, l2, r2, 0, n - 1, 0, m - 1);
    }
};

const int maxn = 1000 + 5;
int n, m, q;
int a[maxn][maxn];

void upd_e(int&x, const int& val){
    x += val;
}
SegmentTree2D<int> seg(maxn, maxn, upd_e);

int main() {
    srand(time(NULL));
    n = m = 100, q = 1000;
    while (q--) {
        if (rand() % 2) {
            int i1 = abs(rand() * rand()) % n, i2 = abs(rand() * rand()) % m;
            int val = abs(rand() * rand());
            seg.upd(1, 1, i1, i2, 0, n - 1, 0, m - 1, -a[i1][i2]);
            seg.upd(1, 1, i1, i2, 0, n - 1, 0, m - 1, val);
            a[i1][i2] = val;
        }
        else {
            int l1 = abs(rand() * rand()) % n, r1 = abs(rand() * rand()) % n, l2 = abs(rand() * rand()) % m, r2 = abs(rand() * rand()) % m;
            if (l1 > r1) swap(l1, r1);
            if (l2 > r2) swap(l2, r2);
            int ans = 0;
            for (int i = l1; i <= r1; i++) {
                for (int j = l2; j <= r2; j++) {
                    ans += a[i][j];
                }
            }
            assert(ans == seg.query(1, 1, l1, r1, l2, r2, 0, n - 1, 0, m - 1));
        }
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
