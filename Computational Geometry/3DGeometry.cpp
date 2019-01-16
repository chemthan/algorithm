#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9
#define oo 1e100
#define nabs(x) ((x) < 0 ? -(x) : (x))
template<class num_t>
struct point_t {
    inline int sign(num_t x) {return x < -EPS ? -1 : x > +EPS;}
    inline int sign(num_t x, num_t y) {return sign(x - y);}

    num_t x, y, z;
    template<class X_t, class Y_t, class Z_t>
    point_t(X_t x = 0, Y_t y = 0, Z_t z = 0) : x(x), y(y), z(z) {}
    point_t operator + (const point_t& rhs) const {
        return point_t(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    point_t operator - (const point_t& rhs) const {
        return point_t(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    point_t operator * (const num_t& k) const {
        return point_t(x * k, y * k, z * k);
    }
    point_t operator / (const num_t& k) const {
        return point_t(x / k, y / k, z / k);
    }
    inline num_t len() {
        return hypot(hypot(x, y), z);
    }
    inline num_t norm() {
        return x * x + y * y + z * z;
    }
    inline num_t distLP(point_t p1, point_t p2) const {
        return det(p2 - p1, *this - p1).len() / (p2 - p1).len();
    }
    inline num_t distFP(point_t p1, point_t p2, point_t p3) const {
        point_t n = det(p2 - p1, p3 - p1);
        if (!sign(n.len())) return +oo;
        return nabs(dot(n, *this - p1) / n.len());
    }
    inline friend point_t det(point_t a, point_t b) {
        return point_t(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }
    inline friend num_t mix(point_t a, point_t b, point_t c) {
        return a.x * b.y * c.z + a.y * b.z * c.x + a.z * b.x * c.y - a.z * b.y * c.x - a.x * b.z * c.y - a.y * b.x * c.z;
    }
    inline friend num_t dot(point_t a, point_t b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    friend num_t distLL(point_t p1, point_t p2, point_t q1, point_t q2) {
        point_t p = q1 - p1, u = p2 - p1, v = q2 - q1;
        num_t d = u.norm() * v.norm() - dot(u, v) * dot(u, v);
        if (sign(d) == 0) return p1.distLP(q1, q2);
        num_t s = (dot(p, u) * v.norm() - dot(p, v) * dot(u, v)) / d;
        return (p1 + u * s).distLP(q1, q2);
    }
    friend num_t distSS(point_t p1, point_t p2, point_t q1, point_t q2) {
        point_t p = q1 - p1, u = p2 - p1, v = q2 - q1;
        num_t d = u.norm() * v.norm() - dot(u, v) * dot(u, v);
        if (sign(d) == 0) return min( min((p1 - q1).len(), (p1 - q2).len()), min((p2 - q1).len(), (p2 - q2).len()));
        num_t s1 = (dot(p, u) * v.norm() - dot(p, v) * dot(u, v)) / d;
        num_t s2 = (dot(p, v) * u.norm() - dot(p, u) * dot(u, v)) / d;
        if (s1 < 0.0) s1 = 0.0; if (s1 > 1.0) s1 = 1.0;
        if (s2 < 0.0) s2 = 0.0; if (s2 > 1.0) s2 = 1.0;
        point_t r1 = p1 + u * s1; point_t r2 = q1 + v * s2;
        return (r1 - r2).len();
    }
    friend int isFL(point_t p, point_t o, point_t q1, point_t q2, point_t& res) {
        num_t a = dot(o, q2 - p), b = dot(o, q1 - p), d = a - b;
        if (sign(d) == 0) return 0;
        res = (q1 * a - q2 * b) / d;
        return 1;
    }
    friend int isFF(point_t p1, point_t o1, point_t p2, point_t o2, point_t& a, point_t& b) {
        point_t e = det(o1, o2), v = det(o1, e);
        num_t d = dot(o2, v); if (sign(d) == 0) return 0;
        point_t q = p1 + v * (dot(o2, p2 - p1) / d);
        a = q; b = q + e;
        return 1;
    }
    inline friend num_t volume(point_t a, point_t b, point_t c, point_t d) {
        return nabs(mix(b - a, c - a, d - a)) / 6;
    }
};


int main() {
    srand(time(NULL));
    point_t<long double> a(rand() % 1000, rand() % 1000, rand() % 1000);
    point_t<long double> b(rand() % 1000, rand() % 1000, rand() % 1000);
    point_t<long double> c(rand() % 1000, rand() % 1000, rand() % 1000);
    point_t<long double> d(rand() % 1000, rand() % 1000, rand() % 1000);
    cout << fixed << setprecision(9) << volume(a, b, c, d) << "\n";
    cout << fixed << setprecision(9) << nabs(dot(det(b - a, c - a), d - a)) / 6 << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
