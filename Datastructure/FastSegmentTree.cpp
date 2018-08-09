#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
*/
template<class T> struct FastSegmentTree {
    static const int MAXN = 1e5 + 5;
    static const int LOGN = 20;
    int n;
    T st[MAXN << 1];
    T lz[MAXN];
    int sz[MAXN << 1];
    void build(int n) {
        this->n = n;
        fill_n(sz + n, n, 1);
        for (int i = n - 1; i > 0; i--) {
            sz[i] = sz[i << 1] + sz[i << 1 | 1];
            st[i] = st[i << 1] + st[i << 1 | 1];
        }
    }
    void apply(int p, T val) {
        st[p] += val * sz[p];
        if (p < n) lz[p] += val;
    }
    void pushup(int p) {
        while (p > 1) p >>= 1, st[p] = st[p << 1] + st[p << 1 | 1] + lz[p] * sz[p];
    }
    void pushdown(int p) {
        for (int i = LOGN; i > 0; i--) {
            int q = p >> i;
            if (lz[q]) {
                apply(q << 1, lz[q]);
                apply(q << 1 | 1, lz[q]);
                lz[q] = 0;
            }
        }
    }
    void upd(int l, int r, T val) {
        l += n, r += n + 1;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, val);
            if (r & 1) apply(--r, val);
        }
        pushup(l0); pushup(r0 - 1);
    }
    T query(int l, int r) {
        l += n, r += n + 1;
        pushdown(l), pushdown(r - 1);
        T res = 0;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += st[l++];
            if (r & 1) res += st[--r];
        }
        return res;
    }
};
FastSegmentTree<int> seg;

const int maxn = 1e5 + 5;
int a[maxn];

int main() {
    srand(time(NULL));
    int n = 10000, q = 10000;
    for (int i = 0; i < n; i++) {
        a[i] = seg.st[i + n] = rand() % 123;
    }
    seg.build(n);
    while (q--) {
        int op = rand() & 1;
        if (op) {
            int l = rand() % n, r = rand() % n, val = rand() % 123;
            if (l > r) swap(l, r);
            seg.upd(l, r, val);
            for (int i = l; i <= r; i++) {
                a[i] += val;
            }
        }
        else {
            int l = rand() % n, r = rand() % n;
            if (l > r) swap(l, r);
            int ans = 0;
            for (int i = l; i <= r; i++) {
                ans += a[i];
            }
            assert(ans == seg.query(l, r));
        }
    }
    cout << "Correct!\n";
    return 0;
}
