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
void ConvexHull(vector<point_t>& pts, vector<point_t>& up, vector<point_t>& dn) {
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
vector<pair<int, int> > v;

long long dist(point_t a, point_t b) {return (long long) (a.x - b.x) * (a.x - b.x) + (long long) (a.y - b.y) * (a.y - b.y);}
long long area(int i, int j, int k) {return abs(area(p[i], p[j], p[k]));}

int main() {
    srand(time(NULL));
    vector<point_t> vp, up, dn;
    for (int i = 0; i < 100000; i++) vp.push_back(point_t(rand(), rand()));
    ConvexHull(vp, up, dn);
    int u = 0, v = dn.size() - 1, w = up.size() - 1;
    long long mx = dist(up[u], dn[v]);
    while (u < w || v > 0) {
        if (u == w) v--;
        else if (!v) u++;
        else {
            if (cross(up[u + 1] - up[u], dn[v] - dn[v - 1]) < 0) {
                u++;
            }
            else {
                v--;
            }
        }
        mx = max(mx, dist(up[u], dn[v]));
    }
    for (int i = 0; i < vp.size(); i++) {
        for (int j = i + 1; j < vp.size(); j++) {
            assert(mx >= dist(vp[i], vp[j]));
        }
    }
    cout << "Correct!\n";
    return 0;
}
