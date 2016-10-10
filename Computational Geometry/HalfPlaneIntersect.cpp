#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: Nlog(N)
* Problems:
* 1. https://www.codechef.com/problems/ALLPOLY
*/

#define RL double
#define EPS 1e-9
struct PT {
	RL x, y;
	PT() : x(0), y(0) {}
	PT(RL x, RL y) : x(x), y(y) {}
	PT(const PT& p) : x(p.x), y(p.y) {}
	int operator < (const PT& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
	int operator == (const PT& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
	PT operator + (const PT& p) const {return PT(x + p.x, y + p.y);}
	PT operator - (const PT& p) const {return PT(x - p.x, y - p.y);}
	PT operator * (RL c) const {return PT(x * c, y * c);}
	PT operator / (RL c) const {return PT(x / c, y / c);}
};
RL cross(PT p, PT q) {return p.x * q.y - p.y * q.x;}
RL area(PT a, PT b, PT c) {return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;}
RL area2(PT a, PT b, PT c) {return cross(a, b) + cross(b, c) + cross(c, a);}
RL dot(PT p, PT q) {return p.x * q.x + p.y * q.y;}
RL dist(PT p, PT q) {return sqrt(dot(p - q, p - q));}
RL dist2(PT p, PT q) {return dot(p - q, p - q);}
PT RotateCCW90(PT p) {return PT(-p.y, p.x);}
PT RotateCW90(PT p) {return PT(p.y, -p.x);}
PT RotateCCW(PT p, RL t) {return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));}
int sign(RL x) {return x < -EPS ? -1 : x > EPS;}
int sign(RL x, RL y) {return sign(x - y);}
ostream& operator << (ostream& os, const PT& p) {
  os << "(" << p.x << "," << p.y << ")"; 
}
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
	b = b - a; d = c - d; c = c - a;
	return a + b * cross(c, d) / cross(b, d);
}

//Contains all points p such that: cross(b - a, p - a) >= 0
struct Plane {
	PT a, b;
	Plane() {}
	Plane(PT a, PT b) : a(a), b(b) {}
	Plane(const Plane& rhs) : a(rhs.a), b(rhs.b) {}
	int operator < (const Plane& rhs) const {
		PT p = b - a;
		PT q = rhs.b - rhs.a;
		int fp = (p.y < 0 || (p.y == 0 && p.x < 0));
		int fq = (q.y < 0 || (q.y == 0 && q.x < 0));
		if (fp != fq) return fp == 0;
		if (cross(p, q)) return cross(p, q) > 0;
		return cross(p, rhs.b - a) < 0;
	}
};
PT PlaneIntersection(Plane u, Plane v) {
	return ComputeLineIntersection(u.a, u.b, v.a, v.b);
}
int check(Plane a, Plane b, Plane c) {
	return cross(a.b - a.a, PlaneIntersection(b, c) - a.a) > EPS;
}

const int maxn = 100000 + 10;
Plane que[maxn];
int qh, qe;

int main() {
	srand(time(NULL));
	vector<Plane> vpl;
	for (int i = 0; i < 100000; i++) {
		vpl.push_back(Plane(PT(rand(), rand()), PT(rand(), rand())));
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
