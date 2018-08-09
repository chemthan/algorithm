#include <bits/stdc++.h>
using namespace std;

#define double double
#define EPS 1e-9
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

int main() {
    return 0;
}
