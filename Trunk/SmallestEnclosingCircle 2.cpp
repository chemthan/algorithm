#include <bits/stdc++.h>
using namespace std;

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
int rlcmp(RL x) {return x < -EPS ? -1 : x > EPS;}
int rlcmp(RL x, RL y) {return rlcmp(x - y);}
ostream& operator << (ostream& os, const PT& p) {
  os << "(" << p.x << "," << p.y << ")"; 
}
PT ProjectPointLine(PT a, PT b, PT c) {
	return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}
RL DistancePointLine(PT a, PT b, PT c) {
	return dist(c, ProjectPointLine(a, b, c));
}
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
	b = b - a; d = c - d; c = c - a;
	return a + b * cross(c, d) / cross(b, d);
}
struct Line {
	PT l, r;
	Line() {}
	Line(PT l, PT r) : l(l), r(r) {}
	Line(const Line& rhs) : l(rhs.l), r(rhs.r) {}
};
Line Bisector(PT a, PT b) {
	PT c = (a + b) / 2;
	return Line(c, c + RotateCCW90(b - c));
}
struct Circle {
	PT cen;
	RL rad;
	Circle() : rad(0) {}
	Circle(PT cen, RL rad) : cen(cen), rad(rad) {}
	Circle(const Circle& rhs) : cen(rhs.cen), rad(rhs.rad) {}
	int operator < (const Circle& rhs) const {
		return rad < rhs.rad;
	}
};
Circle CircumCircle(PT a, PT b, PT c) {
	if (rlcmp(cross(a - c, b - c)) == 0) {
		Circle res = Circle((a + b) / 2, dist(a, b) / 2);
		res = max(res, Circle((b + c) / 2, dist(b, c) / 2));
		res = max(res, Circle((c + a) / 2, dist(c, a) / 2));
		return res;
	}
	Line ln1 = Bisector(a, b);
	Line ln2 = Bisector(b, c);
	PT cen = ComputeLineIntersection(ln1.l, ln1.r, ln2.l, ln2.r);
	return Circle(cen, dist(cen, a));
}
int Inside(vector<PT>& vp, Circle c) {
	for (int i = 0; i < vp.size(); i++) {
		if (rlcmp(dist(c.cen, vp[i]), c.rad) > 0) return 0;
	}
	return 1;
}
Circle Enclose(vector<PT>& vp, PT p, PT q) {
	Circle res = Circle(PT(), +1e100);
	pair<RL, Circle> best = make_pair(-1e100, Circle());
	for (int i = 0; i < vp.size(); i++) if (rlcmp(cross(p - vp[i], q - vp[i])) >= 0) {
		Circle c = CircumCircle(p, q, vp[i]);
		RL d = DistancePointLine(p, q, c.cen);
		if (rlcmp(cross(p - c.cen, q - c.cen)) < 0) d *= -1;
		best = max(best, make_pair(d, c));
	}
	if (best.first > -1e100 && Inside(vp, best.second)) {
		res = min(res, best.second);
	}
	best = make_pair(-1e100, Circle());
	for (int i = 0; i < vp.size(); i++) if (rlcmp(cross(p - vp[i], q - vp[i])) < 0) {
		Circle c = CircumCircle(p, q, vp[i]);
		RL d = DistancePointLine(p, q, c.cen);
		if (rlcmp(cross(p - c.cen, q - c.cen)) > 0) d *= -1;
		best = max(best, make_pair(d, c));
	}
	if (best.first > -1e100 && Inside(vp, best.second)) {
		res = min(res, best.second);
	}
	Circle c = Circle((p + q) / 2, dist(p, q) / 2);
	if (Inside(vp, c)) {
		res = min(res, c);
	}
	return res;
}
Circle Enclose(vector<PT>& vp, PT p) {
	Circle c = Circle((p + vp[0]) / 2, dist(p, vp[0]) / 2);
	vector<PT> cur; cur.push_back(vp[0]);
	for (int i = 1; i < vp.size(); i++) {
		if (rlcmp(dist(c.cen, vp[i]), c.rad) > 0) {
			c = Enclose(cur, p, vp[i]);
		}
		cur.push_back(vp[i]);
	}
	return c;
}
Circle Enclose(vector<PT>& vp) {
	random_shuffle(vp.begin(), vp.end());
	Circle c = Circle((vp[0] + vp[1]) / 2, dist(vp[0], vp[1]) / 2);
	vector<PT> cur; cur.push_back(vp[0]), cur.push_back(vp[1]);
	for (int i = 2; i < vp.size(); i++) {
		if (rlcmp(dist(c.cen, vp[i]), c.rad) > 0) {
			c = Enclose(cur, vp[i]);
		}
		cur.push_back(vp[i]);
	}
	return c;
}
Circle bruteforce(vector<PT> vp) {
	Circle best = Circle(PT(), +1e100);
	for (int i = 0; i < vp.size(); i++) {
		for (int j = i + 1; j < vp.size(); j++) {
			for (int k = j + 1; k < vp.size(); k++) {
				Circle c = CircumCircle(vp[i], vp[j], vp[k]);
				if (Inside(vp, c)) {
					best = min(best, c);
				}
			}
			Circle c = Circle((vp[i] + vp[j]) / 2, dist(vp[i], vp[j]) / 2);
			if (Inside(vp, c)) {
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
		vector<PT> vp;
		for (int i = 0; i < 50; i++) {
			int x = rand();
			int y = rand();
			if (!hs.count(make_pair(x, y))) {
				hs[make_pair(x, y)];
				vp.push_back(PT(x, y));
			}
		}
		Circle c = Enclose(vp);
		Circle ans = bruteforce(vp);
		assert(rlcmp(dist(c.cen, ans.cen)) == 0);
		assert(rlcmp(c.rad, ans.rad) == 0);
		cout << fixed << setprecision(3) << c.cen << " " << c.rad << "\n";
	}
	map<pair<int, int>, int> hs;
	vector<PT> vp;
	for (int i = 0; i < 100000; i++) {
		int x = rand();
		int y = rand();
		if (!hs.count(make_pair(x, y))) {
			hs[make_pair(x, y)];
			vp.push_back(PT(x, y));
		}
	}
	Circle c = Enclose(vp);
	cout << fixed << setprecision(3) << c.cen << " " << c.rad << "\n";
	cout << "Correct!\n";
	return 0;
}
