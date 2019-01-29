#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: build O(NlogN), query O(1)
 */
template<class num_t, class cmp = less<num_t> >
struct RMQ {
    int n;
    vector<num_t> a;
    vector<vector<num_t> > f;

    inline num_t best(const num_t& a, const num_t& b) {
        if (cmp()(a, b)) return a;
        return b;
    }
    void init(int _n) {
        n = _n;
        int p = 1; while ((1 << p) < n) p++;
        a.resize(n), f.resize(p + 1);
        a.shrink_to_fit(), f.shrink_to_fit();
        for (int i = 0; i < (int) f.size(); i++) {
            f[i].resize(n);
        }
    }
    num_t& operator [] (int u) {
        assert(u < (int) a.size());
        return a[u];
    }
    void build() {
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int l = 0, k; (k = 1 << l) < n; l++) {
            for (int i = 0; i + k < n; i++) {
                f[l + 1][i] = best(f[l][i], f[l][i + k]);
            }
        }
    }
    num_t query(int a, int b) {
        assert(a <= b);
        int l = a == b ? 0 : __lg(b - a);
        return best(f[l][a], f[l][b - (1 << l) + 1]);
    }
};
RMQ<int> rmq;

int main() {
    srand(time(NULL));
    for (int it = 0; it < 10; it++) {
        rmq.init(rand() % 100000 + 1);
        for (int i = 0; i < rmq.n; i++) {
            rmq[i] = rand();
        }
        rmq.build();
        for (int test = 0; test < 1000; test++) {
            int l = rand() % rmq.n, r = rand() % rmq.n;
            if (l > r) swap(l, r);
            int res = 1 << 30 | (1 << 30) - 1;
            for (int i = l; i <= r; i++) {
                res = min(res, rmq[i]);
            }
            assert(rmq.query(l, r) == res);
        }
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
