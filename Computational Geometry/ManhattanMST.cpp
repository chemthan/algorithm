#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int oo = (int) 1e9;

struct point_t {
    int x, y, idx;
    point_t() {x = y = idx = 0;}
    point_t(const point_t& rhs) : x(rhs.x), y(rhs.y), idx(rhs.idx) {}
    int operator < (const point_t& rhs) const {
        return make_pair(x, make_pair(y, idx)) < make_pair(rhs.x, make_pair(rhs.y, rhs.idx));
    }
};

pair<int, int> fen[maxn];
void upd(int p, pair<int, int> val) {
    p++;
    for (; p > 0; p -= p & -p) fen[p] = min(fen[p], val);
}
int query(int p) {
    p++;
    pair<int, int> res = make_pair(oo, -1);
    for (; p < maxn; p += p & -p) {
        res = min(res, fen[p]);
    }
    return res.second;
}

int dj[maxn];
void init() {
    for (int i = 0; i < maxn; i++) dj[i] = i;
}
int find(int u) {
    return dj[u] == u ? dj[u] : dj[u] = find(dj[u]);
}
int join(int u, int v) {
    int p = find(u);
    int q = find(v);
    if (p != q) {
        dj[p] = q;
        return 1;
    }
    return 0;
}

int n;
point_t p[maxn];
priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;

int dist(point_t a, point_t b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void add(int u, int v, int d) {
    pq.push(make_pair(d, make_pair(u, v)));
}

void manhattan() {
    for (int i = 0; i < n; i++) p[i].idx = i;
    for (int dir = 0; dir < 4; dir++) {
        for (int i = 0; i < maxn; i++) {
            fen[i] = make_pair(oo, -1);
        }
        if (dir == 1 || dir == 3) {
            for (int i = 0; i < n; i++) swap(p[i].x, p[i].y);
        }
        else if (dir == 2) {
            for (int i = 0; i < n; i++) p[i].x = -p[i].x;
        }
        sort(p, p + n);
        vector<int> v; static int a[maxn];
        for (int i = 0; i < n; i++) v.push_back(a[i] = p[i].y - p[i].x);
        sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
        for (int i = 0; i < n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
        for (int i = n - 1; i >= 0; i--) {
            int pos = query(a[i]);
            if (~pos) add(p[i].idx, p[pos].idx, dist(p[i], p[pos]));
            upd(a[i], make_pair(p[i].x + p[i].y, i));
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);        
    }
    manhattan();
    init();
    int ans = 0;
    while (pq.size()) {
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        int w = pq.top().first;
        pq.pop();
        if (join(u, v)) {
            ans += w;
        }
    }
    printf("%d\n", ans);
    return 0;
}
