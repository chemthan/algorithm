#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(logN)
 * Problems:
 * 1. https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=596&page=show_problem&problem=4454
 */
template<typename num_t>
struct RangeFenwick {
    int n;
    vector<num_t> fen[2];
    RangeFenwick(int n) {
        this->n = n;
        fen[0].resize(n + 1);
        fen[1].resize(n + 1);
    }
    void upd(int p, num_t val) {
        p++;
        assert(0 < p);
        for (int pp = p; pp <= n; pp += pp & -pp) {
            fen[0][pp] += val;
            fen[1][pp] += val * p;
        }
    }
    void upd(int l, int r, num_t val) {
        upd(l, +val), upd(r + 1, -val);
    }
    num_t query(int p) {
        p++;
        assert(p <= n);
        num_t res = 0;
        for (int pp = p; pp > 0; pp -= pp & -pp) {
            res += fen[0][pp] * (p + 1);
            res -= fen[1][pp];
        }
        return res;
    }
    num_t query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

const int maxn = 1e5 + 5;
int n, q;
int a[maxn];

int main() {
    srand(time(0));
    for (int it = 0; it < 10; it++) {
        n = rand() % 1000 + 1;
        q = rand() % 1000 + 1;
        fill_n(a, n, 0);
        RangeFenwick<int> rf(n);
        while (q--) {
            if (rand() % 2 == 0) {
                int l = rand() % n, r = rand() % n, val = rand() % 1000;
                if (l > r) swap(l, r);
                rf.upd(l, r, val);
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
                assert(rf.query(l, r) == ans);
            }
        }
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
