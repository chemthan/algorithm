#include <bits/stdc++.h>
using namespace std;

struct point_t {
    int x, y;
    point_t() : x(0), y(0) {}
    point_t(int x, int y) : x(x), y(y) {}
    point_t(const point_t& rhs) : x(rhs.x), y(rhs.y) {}
    int operator < (const point_t& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
    int operator == (const point_t& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
    point_t operator - (const point_t& rhs) const {return point_t(x - rhs.x, y - rhs.y);}
};
long long cross(point_t a, point_t b) {
    return (long long) a.x * b.y - (long long) a.y * b.x;
}
long long area(point_t a, point_t b, point_t c) {
    return cross(a, b) + cross(b, c) + cross(c, a);
}
long long dist(point_t a, point_t b) {
    return (long long) (a.x - b.x) * (a.x - b.x) + (long long) (a.y - b.y) * (a.y - b.y);
}
void ConvexHull(vector<point_t>& pts) {
    vector<point_t> up, dn;
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area(up[up.size() - 2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area(dn[dn.size() - 2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
}

const int maxn = 1e5 + 5;
int n;
point_t p[maxn];
long long mx;

long long area(int i, int j, int k) {return area(p[i], p[j], p[k]);}
long long dist(int i, int j) {return dist(p[i], p[j]);}
int next(int i) {if (++i == n) i = 0; return i;}

void GetAllAntiPodalPairs() {
    int u = n - 1, v = 0;
    while (area(u, next(u), next(v)) > area(u, next(u), v)) v = next(v);
    int v0 = v, u0 = 0;
    mx = 0;
    while (v != u0) {
        u = next(u);
        mx = max(mx, dist(u, v));
        while (area(u, next(u), next(v)) > area(u, next(u), v)) {
            v = next(v);
            if (u != v0 || v != u0) {
                mx = max(mx, dist(u, v));
            }
            else {
                return;
            }
        }
        if (area(u, next(u), next(v)) == area(u, next(u), v)) {
            if (u != v0 || next(v) != u0) {
                mx = max(mx, dist(u, next(v)));
            }
            else {
                mx = max(mx, dist(next(u), v));
                return;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    vector<point_t> vp;
    for (int i = 0; i < 100000; i++) vp.push_back(point_t(rand(), rand()));
    ConvexHull(vp);
    n = vp.size();
    for (int i = 0; i < n; i++) p[i] = vp[i];
    GetAllAntiPodalPairs();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            assert(mx >= dist(i, j));
        }
    }
    cout << "Correct!\n";
    return 0;
}
