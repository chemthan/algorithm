#include <bits/stdc++.h>
using namespace std;

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
point_t ProjectPointLine(point_t a, point_t b, point_t c) {
    return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}
double DistancePointLine(point_t a, point_t b, point_t c) {
    return dist(c, ProjectPointLine(a, b, c));
}
point_t ComputeLineIntersection(point_t a, point_t b, point_t c, point_t d) {
    b = b - a; d = c - d; c = c - a;
    return a + b * cross(c, d) / cross(b, d);
}
struct Line {
    point_t l, r;
    Line() {}
    Line(point_t l, point_t r) : l(l), r(r) {}
    Line(const Line& rhs) : l(rhs.l), r(rhs.r) {}
};
Line Bisector(point_t a, point_t b) {
    point_t c = (a + b) / 2;
    return Line(c, c + RotateCCW90(b - c));
}
struct Circle {
    point_t cen;
    double rad;
    Circle() : rad(0) {}
    Circle(point_t cen, double rad) : cen(cen), rad(rad) {}
    Circle(const Circle& rhs) : cen(rhs.cen), rad(rhs.rad) {}
    int operator < (const Circle& rhs) const {
        return rad < rhs.rad;
    }
};
Circle CircumCircle(point_t a, point_t b, point_t c) {
    if (sign(cross(a - c, b - c)) == 0) {
        Circle res = Circle((a + b) / 2, dist(a, b) / 2);
        res = max(res, Circle((b + c) / 2, dist(b, c) / 2));
        res = max(res, Circle((c + a) / 2, dist(c, a) / 2));
        return res;
    }
    Line ln1 = Bisector(a, b);
    Line ln2 = Bisector(b, c);
    point_t cen = ComputeLineIntersection(ln1.l, ln1.r, ln2.l, ln2.r);
    return Circle(cen, dist(cen, a));
}

Circle Enclose(vector<point_t>& p) {
    random_shuffle(p.begin(), p.end());
    int n = p.size();
    Circle c(p[0], 0);
    for (int i = 1; i < n; i++) {
        if (sign(dist(c.cen, p[i]), c.rad) > 0) {
            c = Circle(p[i], 0);
            for (int j = 0; j < i; j++) {
                if (sign(dist(c.cen, p[j]), c.rad) > 0) {
                    c = Circle((p[i] + p[j]) / 2, dist(p[i], p[j]) / 2);
                    for (int k = 0; k < j; k++) {
                        if (sign(dist(c.cen, p[k]), c.rad) > 0) {
                            c = CircumCircle(p[i], p[j], p[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}

int Inside(vector<point_t>& p, Circle c) {
    for (int i = 0; i < p.size(); i++) {
        if (sign(dist(c.cen, p[i]), c.rad) > 0) return 0;
    }
    return 1;
}

Circle bruteforce(vector<point_t> p) {
    Circle best = Circle(point_t(), +1e100);
    for (int i = 0; i < p.size(); i++) {
        for (int j = i + 1; j < p.size(); j++) {
            for (int k = j + 1; k < p.size(); k++) {
                Circle c = CircumCircle(p[i], p[j], p[k]);
                if (Inside(p, c)) {
                    best = min(best, c);
                }
            }
            Circle c = Circle((p[i] + p[j]) / 2, dist(p[i], p[j]) / 2);
            if (Inside(p, c)) {
                best = min(best, c);
            }
        }
    }
    return best;
}

int main() {
    srand(time(NULL));
    for (int it = 0; it < 100; it++) {
        map<pair<int, int>, int> hs;
        vector<point_t> p;
        for (int i = 0; i < 50; i++) {
            int x = rand();
            int y = rand();
            if (!hs.count(make_pair(x, y))) {
                hs[make_pair(x, y)];
                p.push_back(point_t(x, y));
            }
        }
        Circle c = Enclose(p);
        Circle ans = bruteforce(p);
        assert(sign(dist(c.cen, ans.cen)) == 0);
        assert(sign(c.rad, ans.rad) == 0);
        cout << fixed << setprecision(3) << c.cen << " " << c.rad << "\n";
    }
    map<pair<int, int>, int> hs;
    vector<point_t> p;
    for (int i = 0; i < 100000; i++) {
        int x = rand();
        int y = rand();
        if (!hs.count(make_pair(x, y))) {
            hs[make_pair(x, y)];
            p.push_back(point_t(x, y));
        }
    }
    Circle c = Enclose(p);
    cout << fixed << setprecision(3) << c.cen << " " << c.rad << "\n";
    cout << "Correct!\n";
    return 0;
}
