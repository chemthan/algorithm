#include <bits/stdc++.h>
using namespace std;

struct point_t {
    int x, y;
    point_t() : x(0), y(0) {}
    point_t(int x, int y) : x(x), y(y) {}
    point_t(const point_t& rhs) : x(rhs.x), y(rhs.y) {}
    int operator < (const point_t& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
    int operator == (const point_t& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
    int operator != (const point_t& rhs) const {return make_pair(y, x) != make_pair(rhs.y, rhs.x);}
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
int n, n1, n2;
vector<point_t> vp1, vp2;

int next1(int i) {if (++i == n1) i = 0; return i;}
int next2(int i) {if (++i == n2) i = 0; return i;}

int compare(pair<point_t, int> a, pair<point_t, int> b) {
    return cross(a.first, b.first) > 0;
}

long long calc(int i1, int i2, int j1, int j2) {
    long long res = 0;
    for (int u = -1; u <= 1; u++) for (int v = -1; v <= 1; v++) {
        int ni1 = (i1 + u + n1) % n1;
        int ni2 = (i2 + u + n1) % n1;
        int nj1 = (j1 + v + n2) % n2;
        int nj2 = (j2 + v + n2) % n2;
        res = max(res, dist(vp1[ni1], vp2[nj1]));
        res = max(res, dist(vp1[ni2], vp2[nj2]));
        res = max(res, dist(vp1[ni1], vp2[nj2]));
        res = max(res, dist(vp1[ni2], vp2[nj1]));
    }
    return res;
}

int main() {
    srand(time(NULL));
    n1 = n2 = 1000;
    for (int i = 0; i < n1; i++) {
        vp1.push_back(point_t(rand(), rand()));
    }
    for (int i = 0; i < n2; i++) {
        vp2.push_back(point_t(rand(), rand()));
    }
    ConvexHull(vp1), ConvexHull(vp2);
    n1 = vp1.size(), n2 = vp2.size();
    if (n1 <= 2 || n2 <= 2) {
        long long mx = 0;
        for (int i = 0; i < n1; i++) for (int j = 0; j < n2; j++) {
            mx = max(mx, dist(vp1[i], vp2[j]));
        }
        cout << mx << "\n";
        return 0;
    }
    int i1 = 0, j1 = 0, i2 = -1, j2 = -1;
    for (int i = 0; i < n1; i++) {
        if (i2 == -1 || vp1[i].y > vp1[i2].y) {
            i2 = i;
        }
    }
    for (int i = 0; i < n2; i++) {
        if (j2 == -1 || vp2[i].y > vp2[j2].y) {
            j2 = i;
        }
    }
    assert(~i2), assert(~j2);
    long long mx = calc(i1, i2, j1, j2);
    point_t vec = point_t(1, 0), first = point_t((int) -1e9, (int) -1e9);
    while (1) {
        vector<pair<point_t, int> > vv;
        if (cross(vec, vp1[next1(i1)] - vp1[i1]) >= 0) {
            vv.push_back(make_pair(vp1[next1(i1)] - vp1[i1], 0));
        }
        if (cross(vec, vp1[i2] - vp1[next1(i2)]) >= 0) {
            vv.push_back(make_pair(vp1[i2] - vp1[next1(i2)], 1));
        }
        if (cross(vec, vp2[next2(j1)] - vp2[j1]) >= 0) {
            vv.push_back(make_pair(vp2[next2(j1)] - vp2[j1], 2));
        }
        if (cross(vec, vp2[j2] - vp2[next2(j2)]) >= 0) {
            vv.push_back(make_pair(vp2[j2] - vp2[next2(j2)], 3));
        }
        sort(vv.begin(), vv.end(), compare);
        int ix = vv[0].second;
        if (ix == 0) i1 = next1(i1);
        else if (ix == 1) i2 = next1(i2);
        else if (ix == 2) j1 = next2(j1);
        else if (ix == 3) j2 = next2(j2);
        vec = vv[0].first;
        mx = max(mx, calc(i1, i2, j1, j2));
        if (first == point_t((int) -1e9, (int) -1e9)) {
            first = vec;
            continue;
        }
        if (vec == first) {
            break;
        }
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            assert(mx >= dist(vp1[i], vp2[j]));
        }
    }
    cout << "Correct!\n";
    return 0;
}
