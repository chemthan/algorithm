#include <bits/stdc++.h>
using namespace std;

#define double double
#define EPS 1e-9
const double PI = acos(-1);
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

double sqr(double x) {return x * x;}
double AreaTC(point_t ct, double r, point_t p1, point_t p2) {
    double a, b, c, x, y, s = cross(p1 - ct, p2 - ct) / 2;
    a = dist(ct, p2), b = dist(ct, p1), c = dist(p1, p2);
    if (a <= r && b <= r) {
        return s;
    }
    else if (a < r && b >= r) {
        x = (dot(p1 - p2, ct - p2) + sqrt(c * c * r * r - sqr(cross(p1 - p2, ct - p2)))) / c;
        return asin(s * (c - x) * 2 / c / b / r) * r * r / 2 + s * x / c;
    }
    else if (a >= r && b < r) {
        y = (dot(p2 - p1, ct - p1) + sqrt(c * c * r * r - sqr(cross(p2 - p1, ct - p1)))) / c;
        return asin(s * (c - y) * 2 / c / a / r) * r * r / 2 + s * y / c;
    }
    else {
        if (fabs(2 * s) >= r * c || dot(p2 - p1, ct - p1) <= 0 || dot(p1 - p2, ct - p2) <= 0) {
            if (dot(p1 - ct, p2 - ct) < 0) {
                if (cross(p1 - ct, p2 - ct) < 0) {
                    return (-PI - asin(s * 2 / a / b)) * r * r / 2;
                }
                else {
                    return (PI - asin(s * 2 / a / b)) * r * r / 2;
                }
            }
            else {
                return asin(s * 2 / a / b) * r * r / 2;
            }
        }
        else {
            x = (dot(p1 - p2, ct - p2) + sqrt(c * c * r * r - sqr(cross(p1 - p2, ct - p2)))) / c;
            y = (dot(p2 - p1, ct - p1) + sqrt(c * c * r * r - sqr(cross(p2 - p1, ct - p1)))) / c;
            return (asin(s * (1 - x / c) * 2 / r / b) + asin(s * (1 - y / c) * 2 / r / a)) * r * r / 2 + s * ((y + x) / c - 1);
        }
    }
}
double AreaTC(point_t ct, double r, point_t p1, point_t p2, point_t p3) {
    return AreaTC(ct, r, p1, p2) + AreaTC(ct, r, p2, p3) + AreaTC(ct, r, p3, p1);
}

int main() {
    return 0;
}
