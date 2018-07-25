#include <bits/stdc++.h>
using namespace std;

/*
* QuadTree 2D
* Space: O(N^2)
*/
#define lnode(p) (p << 1)
#define rnode(p) (p << 1 | 1)
#define mid(l, r) (l + r >> 1)
const int MAXN = 1e3 + 5;
int st[MAXN << 2][MAXN << 2];
int lz[MAXN << 2][MAXN << 2];

int inside(int L1, int R1, int L2, int R2, int l1, int r1, int l2, int r2) {
    return l1 <= L1 && R1 <= r1 && l2 <= L2 && R2 <= r2;
}
int insect(int L1, int R1, int L2, int R2, int l1, int r1, int l2, int r2) {
    if (R1 < l1 || r1 < L1) return 0;
    if (R2 < l2 || r2 < L2) return 0;
    return 1;
}
void pushdown(int px, int py, int L1, int R1, int L2, int R2) {
    if (lz[px][py]) {
        st[px][py] = max(st[px][py], lz[px][py]);
        if (L1 < R1 || L2 < R2) {
            int npx = px, npy = py;
            if (L1 < R1) npx = lnode(px);
            if (L2 < R2) npy = lnode(py);
            lz[npx][npy] = max(lz[npx][npy], lz[px][py]);
        }
        if (L2 < R2) {
            int npx = px, npy = py;
            if (L1 < R1) npx = lnode(px);
            if (L2 < R2) npy = rnode(py);
            lz[npx][npy] = max(lz[npx][npy], lz[px][py]);
        }
        if (L1 < R1) {
            int npx = px, npy = py;
            if (L1 < R1) npx = rnode(px);
            if (L2 < R2) npy = lnode(py);
            lz[npx][npy] = max(lz[npx][npy], lz[px][py]);
        }
        if (L1 < R1 && L2 < R2) {
            int npx = px, npy = py;
            if (L1 < R1) npx = rnode(px);
            if (L2 < R2) npy = rnode(py);
            lz[npx][npy] = max(lz[npx][npy], lz[px][py]);
        }
        lz[px][py] = 0;
    }
}
void upd(int px, int py, int l1, int r1, int l2, int r2, int L1, int R1, int L2, int R2, int val) {
    pushdown(px, py, L1, R1, L2, R2);
    if (!insect(L1, R1, L2, R2, l1, r1, l2, r2)) return;
    if (inside(L1, R1, L2, R2, l1, r1, l2, r2)) {
        lz[px][py] = val;
        pushdown(px, py, L1, R1, L2, R2);
        return;
    }
    int mx = 0;
    if (L1 < R1 || L2 < R2) {
        int npx = px, npy = py;
        if (L1 < R1) npx = lnode(px);
        if (L2 < R2) npy = lnode(py);
        upd(npx, npy, l1, r1, l2, r2, L1, mid(L1, R1), L2, mid(L2, R2), val);
        mx = max(mx, st[npx][npy]);
    }
    if (L2 < R2) {
        int npx = px, npy = py;
        if (L1 < R1) npx = lnode(px);
        if (L2 < R2) npy = rnode(py);
        upd(npx, npy, l1, r1, l2, r2, L1, mid(L1, R1), mid(L2, R2) + 1, R2, val);
        mx = max(mx, st[npx][npy]);
    }
    if (L1 < R1) {
        int npx = px, npy = py;
        if (L1 < R1) npx = rnode(px);
        if (L2 < R2) npy = lnode(py);
        upd(npx, npy, l1, r1, l2, r2, mid(L1, R1) + 1, R1, L2, mid(L2, R2), val);
        mx = max(mx, st[npx][npy]);
    }
    if (L1 < R1 && L2 < R2) {
        int npx = px, npy = py;
        if (L1 < R1) npx = rnode(px);
        if (L2 < R2) npy = rnode(py);
        upd(npx, npy, l1, r1, l2, r2, mid(L1, R1) + 1, R1, mid(L2, R2) + 1, R2, val);
        mx = max(mx, st[npx][npy]);
    }
    if (mx) st[px][py] = mx;
}
int query(int px, int py, int l1, int r1, int l2, int r2, int L1, int R1, int L2, int R2) {
    pushdown(px, py, L1, R1, L2, R2);
    if (!insect(L1, R1, L2, R2, l1, r1, l2, r2)) return 0;
    if (inside(L1, R1, L2, R2, l1, r1, l2, r2)) return st[px][py];
    int res = 0;
    if (L1 < R1 || L2 < R2) {
        int npx = px, npy = py;
        if (L1 < R1) npx = lnode(px);
        if (L2 < R2) npy = lnode(py);
        res = max(res, query(npx, npy, l1, r1, l2, r2, L1, mid(L1, R1), L2, mid(L2, R2)));
    }
    if (L2 < R2) {
        int npx = px, npy = py;
        if (L1 < R1) npx = lnode(px);
        if (L2 < R2) npy = rnode(py);
        res = max(res, query(npx, npy, l1, r1, l2, r2, L1, mid(L1, R1), mid(L2, R2) + 1, R2));
    }
    if (L1 < R1) {
        int npx = px, npy = py;
        if (L1 < R1) npx = rnode(px);
        if (L2 < R2) npy = lnode(py);
        res = max(res, query(npx, npy, l1, r1, l2, r2, mid(L1, R1) + 1, R1, L2, mid(L2, R2)));
    }
    if (L1 < R1 && L2 < R2) {
        int npx = px, npy = py;
        if (L1 < R1) npx = rnode(px);
        if (L2 < R2) npy = rnode(py);
        res = max(res, query(npx, npy, l1, r1, l2, r2, mid(L1, R1) + 1, R1, mid(L2, R2) + 1, R2));
    }
    return res;
}

int n, m, q;
int a[MAXN][MAXN];

int main() {
    srand(time(NULL));
    n = m = q = 1000;
    while (q--) {
        if (rand() % 2) {
            int l1 = abs(rand() * rand()) % n, r1 = abs(rand() * rand()) % n, l2 = abs(rand() * rand()) % m, r2 = abs(rand() * rand()) % m;
            if (l1 > r1) swap(l1, r1);
            if (l2 > r2) swap(l2, r2);
            int val = abs(rand() * rand());
            upd(1, 1, l1, r1, l2, r2, 0, n - 1, 0, m - 1, val);
            for (int i = l1; i <= r1; i++) {
                for (int j = l2; j <= r2; j++) {
                    a[i][j] = max(a[i][j], val);
                }
            }
        }
        else {
            int l1 = abs(rand() * rand()) % n, r1 = abs(rand() * rand()) % n, l2 = abs(rand() * rand()) % m, r2 = abs(rand() * rand()) % m;
            if (l1 > r1) swap(l1, r1);
            if (l2 > r2) swap(l2, r2);
            int ans = 0;
            for (int i = l1; i <= r1; i++) {
                for (int j = l2; j <= r2; j++) {
                    ans = max(ans, a[i][j]);
                }
            }
            cerr << ans << " " << query(1, 1, l1, r1, l2, r2, 0, n - 1, 0, m - 1) << "\n";
            assert(ans == query(1, 1, l1, r1, l2, r2, 0, n - 1, 0, m - 1));
        }
    }
    return 0;
}
