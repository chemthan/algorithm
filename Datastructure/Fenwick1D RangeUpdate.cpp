#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
* Problems:
* 1. https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=596&page=show_problem&problem=4454
*/
template<class T> struct RangeFenwick {
    int n;
    vector<T> fen[2];
    RangeFenwick(int n) {
        this->n = n;
        fen[0].resize(n + 1);
        fen[1].resize(n + 1);
    }
    void upd(int p, T val) {
        assert(p > 0);
        for (int pp = p; pp <= n; pp += pp & -pp) {
            fen[0][pp] += val;
            fen[1][pp] += val * p;
        }
    }
    void upd(int l, int r, T val) {
        upd(l, +val), upd(r + 1, -val);
    }
    T query(int p) {
        assert(p <= n);
        T res = 0;
        for (int pp = p; pp > 0; pp -= pp & -pp) {
            res += fen[0][pp] * (p + 1);
            res -= fen[1][pp];
        }
        return res;
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

const int maxn = 1e5 + 5;
int n, q;
int a[maxn];

int main() {
    srand(time(NULL));
    for (int it = 0; it < 10; it++) {
        n = rand() % 1000 + 1;
        q = rand() % 1000 + 1;
        fill_n(a, n, 0);
        RangeFenwick<int> rf(n);
        while (q--) {
            if (rand() % 2 == 0) {
                int l = rand() % n, r = rand() % n, val = rand() % 1000;
                if (l > r) swap(l, r);
                rf.upd(l + 1, r + 1, val);
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
                assert(rf.query(r + 1) - rf.query(l) == ans);
            }
        }
    }
    cout << "Correct!\n";
    return 0;
}
