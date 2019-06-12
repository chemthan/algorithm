#include <bits/stdc++.h>
using namespace std;

typedef set<pair<int, int> > sii;
typedef set<pair<int, int> >::iterator sit;
struct point_t {
    int x, y;
    point_t() : x(0), y(0) {}
    point_t(int x, int y) : x(x), y(y) {}
    point_t(const point_t& rhs) : x(rhs.x), y(rhs.y) {}
    point_t(const sit& p) : x(p->first), y(p->second) {}
    point_t operator - (const point_t& rhs) const {
        return point_t(x - rhs.x, y - rhs.y);
    }
};
long long cross(point_t a, point_t b) {
    return (long long) a.x * b.y - (long long) a.y * b.x;
}
inline int inside(sii& hull, const point_t& p) { //border inclusive
    int x = p.x, y = p.y;
    sit p1 = hull.lower_bound(make_pair(x, y));
    if (p1 == hull.end()) return 0;
    if (p1->first == x) return p1 != hull.begin() && y <= p1->second;
    if (p1 == hull.begin()) return 0;
    sit p2(p1--);
    return cross(p - point_t(p1), point_t(p2) - p) >= 0;
}
inline void rem(sii& hull, sit it, long long& scross) {
    if (hull.size() == 1) {
        hull.erase(it);
        return;
    }
    if (it == hull.begin()) {
        sit p1 = it++;
        scross -= cross(p1, it);
        hull.erase(p1);
        return;
    }
    sit p1 = --it, p2 = ++it;
    if (++it == hull.end()) {
        scross -= cross(p1, p2);
        hull.erase(p2);
        return;
    }
    scross -= cross(p1, p2) + cross(p2, it) - cross(p1, it);
    hull.erase(p2);
}
inline void add(sii& hull, sit it, long long& scross) {
    if (hull.size() == 1) return;
    if (it == hull.begin()) {
        sit p1 = it++;
        scross += cross(p1, it);
        return;
    }
    sit p1 = --it, p2 = ++it;
    if (++it == hull.end()) {
        scross += cross(p1, p2);
        return;
    }
    scross += cross(p1, p2) + cross(p2, it) - cross(p1, it);
}
inline void add(sii& hull, const point_t& p, long long& scross) { //no collinear point_ts
    if (inside(hull, p)) return;
    int x = p.x, y = p.y;
    sit pnt = hull.insert(make_pair(x, y)).first, p1, p2;
    add(hull, pnt, scross);
    for ( ; ; rem(hull, p2, scross)) {
        p1 = pnt;
        if (++p1 == hull.end()) break;
        p2 = p1;
        if (++p1 == hull.end()) break;
        if (cross(point_t(p2) - p, point_t(p1) - p) < 0) break;
    }
    for ( ; ; rem(hull, p2, scross)) {
        if ((p1 = pnt) == hull.begin()) break;
        if (--p1 == hull.begin()) break;
        p2 = p1--;
        if (cross(point_t(p2) - p, point_t(p1) - p) > 0) break;
    }
}

int main() {
    long long ucross = 0, dcross = 0;
    sii uhull, dhull;
    point_t p[] = {point_t(0, 0), point_t(3, 0), point_t(3, 3), point_t(0, 3), point_t(0, 1), point_t(0, 2), point_t(3, 1), point_t(3, 2)};
    for (int i = 0; i < 5; i++) {
        add(uhull, point_t(+p[i].x, +p[i].y), ucross);
        add(dhull, point_t(-p[i].x, -p[i].y), dcross);
    }
    for (sit it = uhull.begin(); it != uhull.end(); it++) {
        cout << "(" << +it->first << "," << +it->second << ") ";
    }
    cout << "\n";
    for (sit it = dhull.begin(); it != dhull.end(); it++) {
        cout << "(" << -it->first << "," << -it->second << ") ";
    }
    cout << "\n";
    cout << fixed << setprecision(1) << "Area: " << fabs(ucross + dcross) / 2.0 << "\n";
    return 0;
}
