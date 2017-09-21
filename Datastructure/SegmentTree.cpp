#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
*/
template<class T> struct SegmenTree {
    static const int MAXN = 1e5 + 5;
    T st[MAXN << 2];
    T lz[MAXN << 2];
    void pushdown(int p, int L, int R) {
        if (lz[p]) {
            st[p] += (R - L + 1) * lz[p];
            if (L < R) {
                lz[p << 1] += lz[p];
                lz[p << 1 | 1] += lz[p];
            }
            lz[p] = 0;
        }
    }
    void upd(int p, int l, int r, int L, int R, T val) {
        pushdown(p, L, R);
        if (l > R || r < L) return;
        if (l <= L && r >= R) {
            lz[p] = val;
            pushdown(p, L, R);
            return;
        }
        upd(p << 1, l, r, L, L + R >> 1, val);
        upd(p << 1 | 1, l, r, (L + R >> 1) + 1, R, val);
        st[p] = st[p << 1] + st[p << 1 | 1];
    }
    T query(int p, int l, int r, int L, int R) {
        pushdown(p, L, R);
        if (l > R || r < L) return 0;
        if (l <= L && r >= R) return st[p];
        return query(p << 1, l, r, L, L + R >> 1) + query(p << 1 | 1, l, r, (L + R >> 1) + 1, R);
    }
};
SegmenTree<int> seg;

const int maxn = 1e5 + 5;
int n;
int a[maxn];

int main() {
    srand(time(NULL));
    n = 1000;
    for (int it = 0; it < 1000; it++) {
        int l = rand() % n;
        int r = rand() % n;
        if (l > r) swap(l, r);
        int v = rand() % 1000;
        for (int i = l; i <= r; i++) {
            a[i] += v;
        }
        seg.upd(1, l, r, 0, n - 1, v);
        l = rand() % n;
        r = rand() % n;
        if (l > r) swap(l, r);
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans += a[i];
        }
        assert(ans == seg.query(1, l, r, 0, n - 1));    
    }
    cout << "Correct!\n";
    return 0;
}
