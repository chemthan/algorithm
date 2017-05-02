#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(NlogN)
 */
template<class T> struct CascadingSegment {
    struct Info {
        T key;
        int lnxt, rnxt;
        Info() : key(0), lnxt(0), rnxt(0) {}
        Info(T key) : key(key), lnxt(0), rnxt(0) {}
        int operator < (const Info& rhs) const {
            return key < rhs.key;
        }
    };
    static const int maxn = 1e5 + 5;
    vector<Info> st[maxn << 2];
    
    //Updating val in increasing order
    void upd(int p, int i, int L, int R, T val) {
        if (i < L || i > R) return;
        int lptr = st[p].size() ? st[p].back().lnxt : 0;
        int rptr = st[p].size() ? st[p].back().rnxt : 0;
        st[p].push_back(Info(val));
        if (L < R) {
            upd(p << 1, i, L, L + R >> 1, val);
            upd(p << 1 | 1, i, (L + R >> 1) + 1, R, val);
            while (lptr < st[p << 1].size() && val >= st[p << 1][lptr].key) lptr++;
            while (rptr < st[p << 1 | 1].size() && val >= st[p << 1 | 1][rptr].key) rptr++;
        }
        st[p].back().lnxt  = lptr, st[p].back().rnxt = rptr;
    }
    //Calculating how many numbers in range [l, r] less than or equal val
    int query(int p, int l, int r, int L, int R, T val) {
        if (l > R || r < L) return 0;
        if (p == 1) {
            int k = upper_bound(st[p].begin(), st[p].end(), Info(val)) - st[p].begin() - 1;
            if (!~k) return 0;
            if (l <= L && r >= R) return k + 1;
            return query(p << 1, l, r, L, L + R >> 1, st[p][k].lnxt - 1) + query(p << 1 | 1, l, r, (L + R >> 1) + 1, R, st[p][k].rnxt - 1);
        }
        if (!~val) return 0;
        if (l <= L && r >= R) return val + 1;
        return query(p << 1, l, r, L, L + R >> 1, st[p][val].lnxt - 1) + query(p << 1 | 1, l, r, (L + R >> 1) + 1, R, st[p][val].rnxt - 1);
    }
};
CascadingSegment<int> cs;

int main() {
    int n = 100;
    cs.upd(1, 3, 0, n - 1, 5);
    cout << cs.query(1, 0, 3, 0, n - 1, 5) << "\n";
    cs.upd(1, 5, 0, n - 1, 10);
    cout << cs.query(1, 3, 5, 0, n - 1, 10) << "\n";
    return 0;
}

