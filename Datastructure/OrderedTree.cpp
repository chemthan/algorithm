#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(logN)
 */
template<class num_t>
struct OrderedTree {
    int n;
    vector<num_t> a;
    num_t tot;
    vector<num_t> x;
    vector<num_t> y;

    void init(int _n) {
        n = _n;
        a.resize(n);
        for (int i = 0; i < n; i++) a[i] = 0;
        tot = 0;
        x.resize(n + 1);
        y.resize(n + 1);
        for (int i = 0; i <= n; i++) x[i] = y[i] = 0;
    }

    void upd(int p, num_t val, num_t cnt) {
        assert(0 <= p && p < n);
        a[p] = val, tot += cnt;
        for (p++; p <= n; p += p & -p) {
            x[p] += cnt;
            y[p] += cnt * val;
        }
    }

    num_t find_by_order(num_t k) {
        assert(0 <= k && k <= tot);
        if (!k) return -1;
        int p = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (p + (1 << i) <= n && x[p + (1 << i)] < k) {
                k -= x[p + (1 << i)];
                p += 1 << i;
            }
        }
        return a[p];
    }
    num_t find_sum_by_order(num_t k) {
        assert(0 <= k && k <= tot);
        if (!k) return 0;
        num_t res = 0;
        int p = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (p + (1 << i) <= n && x[p + (1 << i)] < k) {
                k -= x[p + (1 << i)];
                res += y[p + (1 << i)];
                p += 1 << i;
            }
        }
        return res + k * a[p];
    }
};
OrderedTree<long long> odtree;

int main() {
    odtree.init(1e5);
    odtree.upd(5, 5, 5);
    odtree.upd(6, 8, 5);
    cout << odtree.find_by_order(6) << "\n";
    cout << odtree.find_sum_by_order(6) << "\n";
    return 0;
}
