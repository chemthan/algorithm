#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: Nlog(N)
 * Problems:
 * 1. https://www.codechef.com/problems/ALLPOLY
 */

#define double double
#define EPS 1e-9
struct point_t {
    double x, y;
    point_t() : x(0), y(0) {}
    point_t(double x, double y) : x(x), y(y) {}
    point_t(const point_t& p) : x(p.x), y(p.y) {}
    int operator < (const point_t& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
    int operator == (const point_t& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
    point_t operator + (const point_t& p) const {return point_t(x + p.x, y + p.y);}
    point_t operator - (const point_t& p) const {return point_t(x - p.x, y - p.y);}
    point_t operator * (double c) const {return point_t(x * c, y * c);}
    point_t operator / (double c) const {return point_t(x / c, y / c);}
};
double cross(point_t p, point_t q) {return p.x * q.y - p.y * q.x;}
double area(point_t a, point_t b, point_t c) {return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;}
double area2(point_t a, point_t b, point_t c) {return cross(a, b) + cross(b, c) + cross(c, a);}
double dot(point_t p, point_t q) {return p.x * q.x + p.y * q.y;}
double dist(point_t p, point_t q) {return sqrt(dot(p - q, p - q));}
double dist2(point_t p, point_t q) {return dot(p - q, p - q);}
point_t RotateCCW90(point_t p) {return point_t(-p.y, p.x);}
point_t RotateCW90(point_t p) {return point_t(p.y, -p.x);}
point_t RotateCCW(point_t p, double t) {return point_t(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));}
int sign(double x) {return x < -EPS ? -1 : x > EPS;}
int sign(double x, double y) {return sign(x - y);}
ostream& operator << (ostream& os, const point_t& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
point_t ComputeLineIntersection(point_t a, point_t b, point_t c, point_t d) {
    b = b - a; d = c - d; c = c - a;
    return a + b * cross(c, d) / cross(b, d);
}

//Contains all points p such that: cross(b - a, p - a) >= 0
struct Plane {
    point_t a, b;
    Plane() {}
    Plane(point_t a, point_t b) : a(a), b(b) {}
    Plane(const Plane& rhs) : a(rhs.a), b(rhs.b) {}
    int operator < (const Plane& rhs) const {
        point_t p = b - a;
        point_t q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (p.y == 0 && p.x < 0));
        int fq = (q.y < 0 || (q.y == 0 && q.x < 0));
        if (fp != fq) return fp == 0;
        if (cross(p, q)) return cross(p, q) > 0;
        return cross(p, rhs.b - a) < 0;
    }
};
point_t PlaneIntersection(Plane u, Plane v) {
    return ComputeLineIntersection(u.a, u.b, v.a, v.b);
}
int check(Plane a, Plane b, Plane c) {
    return cross(a.b - a.a, PlaneIntersection(b, c) - a.a) > EPS;
}

const int maxn = 1e5 + 5;
Plane que[maxn];
int qh, qe;

int main() {
    srand(time(NULL));
    vector<Plane> vpl;
    for (int i = 0; i < 100000; i++) {
        vpl.push_back(Plane(point_t(rand(), rand()), point_t(rand(), rand())));
    }
    sort(vpl.begin(), vpl.end());
    vector<Plane> tmp;
    for (int i = 0; i < vpl.size(); i++) {
        if (!i || cross(vpl[i].b - vpl[i].a, vpl[i - 1].b - vpl[i - 1].a)) {
            tmp.push_back(vpl[i]);
        }
    }
    vpl = tmp;
    qh = qe = 0;
    for (int i = 0; i < vpl.size(); i++) {
        while (qe - qh > 1 && !check(vpl[i], que[qe - 2], que[qe - 1])) qe--;
        while (qe - qh > 1 && !check(vpl[i], que[qh], que[qh + 1])) qh++;
        que[qe++] = vpl[i];
    }
    while (qe - qh > 2 && !check(que[qh], que[qe - 2], que[qe - 1])) qe--;
    while (qe - qh > 2 && !check(que[qe - 1], que[qh], que[qh + 1])) qh++;
    return 0;
}
