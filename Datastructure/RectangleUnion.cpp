#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: NlogN
 * Problems:
 * 1. https://vn.spoj.com/problems/AREA/
 */

template<typename num_t>
long long calc(vector<tuple<num_t, num_t, num_t, num_t>>& recs) {
    vector<num_t> dc;
    for (auto& rec : recs) {
        dc.push_back(get<1>(rec));
        dc.push_back(get<3>(rec));
    }
    sort(dc.begin(), dc.end());
    dc.erase(unique(dc.begin(), dc.end()), dc.end());
    vector<num_t> st(dc.size() << 2);
    vector<int> lz(dc.size() << 2);
    function<void(int, int, int, int, int, int)> upd = [&] (int p, int l, int r, int L, int R, int val) {
        if (lz[p]) st[p] = dc[R] - dc[L];
        else if (L < R - 1) st[p] = st[p << 1] + st[p << 1 | 1];
        else st[p] = 0;
        if (r - 1 < L || R - 1 < l) return;
        if (l <= L && R <= r) {
            lz[p] += val;
            if (lz[p]) st[p] = dc[R] - dc[L];
            else if (L < R - 1) st[p] = st[p << 1] + st[p << 1 | 1];
            else st[p] = 0;
            return;
        }
        upd(p << 1, l, r, L, L + R >> 1, val);
        upd(p << 1 | 1, l, r, L + R >> 1, R, val);
        if (lz[p]) st[p] = dc[R] - dc[L];
        else if (L < R - 1) st[p] = st[p << 1] + st[p << 1 | 1];
        else st[p] = 0;
    };
    vector<tuple<num_t, int, int, int>> vals;
    for (auto& rec : recs) {
        num_t x0, y0, x1, y1; tie(x0, y0, x1, y1) = rec;
        y0 = lower_bound(dc.begin(), dc.end(), y0) - dc.begin();
        y1 = lower_bound(dc.begin(), dc.end(), y1) - dc.begin();
        vals.push_back({x0, +1, y0, y1});
        vals.push_back({x1, -1, y0, y1});
    }
    sort(vals.begin(), vals.end());
    long long res = 0;
    num_t cur = 0;
    for (auto& e : vals) {
        num_t x; int s, lo, hi; tie(x, s, lo, hi) = e;
        res += (long long) st[1] * (x - cur);
        upd(1, lo, hi, 0, (int) dc.size() - 1, s);
        cur = x;
    }
    return res;
}

int main() {
    return 0;
}
