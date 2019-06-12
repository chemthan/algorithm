#include <bits/stdc++.h>
using namespace std;

#define double long double
#define EPS 1e-12
const double PI = acos((double) -1);
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
vector<point_t> CircleLineIntersection(point_t a, point_t b, point_t c, double r) {
    vector<point_t> res;
    b = b - a; a = a - c;
    double A = dot(b, b);
    double B = dot(a, b);
    double C = dot(a, a) - r * r;
    double D = B * B - A * C;
    if (D < -EPS) return res;
    res.push_back(c + a + b * (-B + sqrt(D + EPS)) / A);
    if (D > EPS) res.push_back(c + a + b * (-B - sqrt(D)) / A);
    return res;
}
vector<point_t> CircleCircleIntersection(point_t a, point_t b, double r, double R) {
    vector<point_t> res;
    double d = sqrt(dist2(a, b));
    if (d > r + R - EPS || d + min(r, R) < max(r, R) + EPS) return res;
    double x = (d * d - R * R + r * r) / (2 * d);
    double y = sqrt(r * r - x * x);
    point_t v = (b - a) / d;
    res.push_back(a + v * x + RotateCCW90(v) * y);
    res.push_back(a + v * x - RotateCCW90(v) * y);
    return res;
}
double Angle(point_t a, point_t b) {
    double x = dist(point_t(0, 0), a);
    double y = dist(point_t(0, 0), b);
    double z = dist(a, b);
    double r = (x * x + y * y - z * z) / 2 / x / y;
    if (sign(r, +1) >= 0) return 0.0;
    if (sign(r, -1) <= 0) return PI;
    return acos(r);
}
double Area(point_t ct, double r, point_t a, point_t b) {
    a = a - ct; b = b - ct; ct = point_t(0, 0);
    double alpha = Angle(a, b);
    return r * r * alpha / 2 - dist(ct, a) * dist(ct, b) * sin(alpha) / 2;
}
struct Circle {
    point_t c;
    double r;
    Circle() : r(0.0) {}
    Circle(point_t c, double r) : c(c), r(r) {}
    Circle(const Circle& rhs) : c(rhs.c), r(rhs.r) {}
};

double calc(double lo, double hi, vector<Circle>& vc) {
    double res = 0.0;
    vector<pair<pair<double, int>, pair<pair<point_t, point_t>, int> > > vx;
    for (int i = 0; i < vc.size(); i++) {
        vector<double> vl, vr;
        if (!sign(lo, vc[i].c.y - vc[i].r)) {
            vl.push_back(vc[i].c.x);
            vl.push_back(vc[i].c.x);
        }
        else if (sign(lo, vc[i].c.y - vc[i].r) > 0 && sign(lo, vc[i].c.y + vc[i].r) < 0) {
            vector<point_t> res = CircleLineIntersection(point_t(0, lo), point_t(1, lo), point_t(vc[i].c.x, vc[i].c.y), vc[i].r);
            if (res.size() == 2) {
                if (res[0].x > res[1].x) {
                    swap(res[0], res[1]);
                }
                vl.push_back(res[0].x);
                vl.push_back(res[1].x);
            }
        }
        if (!sign(hi, vc[i].c.y + vc[i].r)) {
            vr.push_back(vc[i].c.x);
            vr.push_back(vc[i].c.x);
        }
        else if (sign(hi, vc[i].c.y - vc[i].r) > 0 && sign(hi, vc[i].c.y + vc[i].r) < 0) {
            vector<point_t> res = CircleLineIntersection(point_t(0, hi), point_t(1, hi), point_t(vc[i].c.x, vc[i].c.y), vc[i].r);
            if (res.size() == 2) {
                if (res[0].x > res[1].x) {
                    swap(res[0], res[1]);
                }
                vr.push_back(res[0].x);
                vr.push_back(res[1].x);
            }
        }
        if (vl.size() == 2 && vr.size() == 2) {
            for (int j = 0; j < 2; j++) {
                vx.push_back(make_pair(make_pair((vl[j] + vr[j]) / 2, j), make_pair(make_pair(point_t(vl[j], lo), point_t(vr[j], hi)), i)));
            }
        }
    }
    sort(vx.begin(), vx.end());
    int cnt = 0;
    pair<pair<point_t, point_t>, int> cur;
    for (int i = 0; i < vx.size(); i++) {
        if (cnt == 0 && !vx[i].first.second) {
            cur = vx[i].second;
        }
        if (vx[i].first.second) cnt--; else cnt++;
        if (!cnt) {
            int ix1 = cur.second;
            int ix2 = vx[i].second.second;
            res += Area(vc[ix1].c, vc[ix1].r, cur.first.first, cur.first.second);
            res += Area(vc[ix2].c, vc[ix2].r, vx[i].second.first.first, vx[i].second.first.second);
            res += (fabs(cur.first.first.x - vx[i].second.first.first.x) + fabs(cur.first.second.x - vx[i].second.first.second.x)) * (hi - lo) / 2;
        }
    }
    return res;
}
double calc(vector<Circle> vc) {
    vector<double> vy;
    for (int i = 0; i < vc.size(); i++) {
        vy.push_back(vc[i].c.y);
        vy.push_back(vc[i].c.y - vc[i].r);
        vy.push_back(vc[i].c.y + vc[i].r);
        for (int j = i + 1; j < vc.size(); j++) {
            vector<point_t> res = CircleCircleIntersection(vc[i].c, vc[j].c, vc[i].r, vc[j].r);
            for (int k = 0; k < res.size(); k++) {
                vy.push_back(res[k].y);
            }
        }
    }
    sort(vy.begin(), vy.end()), vy.erase(unique(vy.begin(), vy.end()), vy.end());
    double res = 0.0;
    for (int i = 0; i < vy.size() - 1; i++) {
        if (sign(vy[i], vy[i + 1])) {
            res += calc(vy[i], vy[i + 1], vc);
        }
    }
    return res;
}

int main() {
    srand(2311);
    vector<Circle> vc;
    for (int i = 0; i < 100; i++) {
        int x = rand(), y = rand(), r = rand();
        vc.push_back(Circle(point_t(x, y), r));
    }
    cout << fixed << setprecision(9) << calc(vc) << "\n";
    return 0;
}
