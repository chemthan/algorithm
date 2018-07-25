#include <bits/stdc++.h>
using namespace std;

#define double long double
#define EPS 1e-12
const double PI = acos((double) -1);
struct PT {
    double x, y;
    PT() : x(0), y(0) {}
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT& p) : x(p.x), y(p.y) {}
    int operator < (const PT& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
    int operator == (const PT& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
    PT operator + (const PT& p) const {return PT(x + p.x, y + p.y);}
    PT operator - (const PT& p) const {return PT(x - p.x, y - p.y);}
    PT operator * (double c) const {return PT(x * c, y * c);}
    PT operator / (double c) const {return PT(x / c, y / c);}
};
double cross(PT p, PT q) {return p.x * q.y - p.y * q.x;}
double area(PT a, PT b, PT c) {return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;}
double area2(PT a, PT b, PT c) {return cross(a, b) + cross(b, c) + cross(c, a);}
double dot(PT p, PT q) {return p.x * q.x + p.y * q.y;}
double dist(PT p, PT q) {return sqrt(dot(p - q, p - q));}
double dist2(PT p, PT q) {return dot(p - q, p - q);}
PT RotateCCW90(PT p) {return PT(-p.y, p.x);}
PT RotateCW90(PT p) {return PT(p.y, -p.x);}
PT RotateCCW(PT p, double t) {return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));}
int sign(double x) {return x < -EPS ? -1 : x > EPS;}
int sign(double x, double y) {return sign(x - y);}
ostream& operator << (ostream& os, const PT& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
vector<PT> CircleLineIntersection(PT a, PT b, PT c, double r) {
    vector<PT> res;
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
vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
    vector<PT> res;
    double d = sqrt(dist2(a, b));
    if (d > r + R - EPS || d + min(r, R) < max(r, R) + EPS) return res;
    double x = (d * d - R * R + r * r) / (2 * d);
    double y = sqrt(r * r - x * x);
    PT v = (b - a) / d;
    res.push_back(a + v * x + RotateCCW90(v) * y);
    res.push_back(a + v * x - RotateCCW90(v) * y);
    return res;
}
double Angle(PT a, PT b) {
    double x = dist(PT(0, 0), a);
    double y = dist(PT(0, 0), b);
    double z = dist(a, b);
    double r = (x * x + y * y - z * z) / 2 / x / y;
    if (sign(r, +1) >= 0) return 0.0;
    if (sign(r, -1) <= 0) return PI;
    return acos(r);
}
double Area(PT ct, double r, PT a, PT b) {
    a = a - ct; b = b - ct; ct = PT(0, 0);
    double alpha = Angle(a, b);
    return r * r * alpha / 2 - dist(ct, a) * dist(ct, b) * sin(alpha) / 2;
}
struct Circle {
    PT c;
    double r;
    Circle() : r(0.0) {}
    Circle(PT c, double r) : c(c), r(r) {}
    Circle(const Circle& rhs) : c(rhs.c), r(rhs.r) {}
};

double calc(double lo, double hi, vector<Circle>& vc) {
    double res = 0.0;
    vector<pair<pair<double, int>, pair<pair<PT, PT>, int> > > vx;
    for (int i = 0; i < vc.size(); i++) {
        vector<double> vl, vr;
        if (!sign(lo, vc[i].c.y - vc[i].r)) {
            vl.push_back(vc[i].c.x);
            vl.push_back(vc[i].c.x);
        }
        else if (sign(lo, vc[i].c.y - vc[i].r) > 0 && sign(lo, vc[i].c.y + vc[i].r) < 0) {
            vector<PT> res = CircleLineIntersection(PT(0, lo), PT(1, lo), PT(vc[i].c.x, vc[i].c.y), vc[i].r);
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
            vector<PT> res = CircleLineIntersection(PT(0, hi), PT(1, hi), PT(vc[i].c.x, vc[i].c.y), vc[i].r);
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
                vx.push_back(make_pair(make_pair((vl[j] + vr[j]) / 2, j), make_pair(make_pair(PT(vl[j], lo), PT(vr[j], hi)), i)));
            }
        }
    }
    sort(vx.begin(), vx.end());
    int cnt = 0;
    pair<pair<PT, PT>, int> cur;
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
            vector<PT> res = CircleCircleIntersection(vc[i].c, vc[j].c, vc[i].r, vc[j].r);
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
        vc.push_back(Circle(PT(x, y), r));
    }
    cout << fixed << setprecision(9) << calc(vc) << "\n";
    return 0;
}
