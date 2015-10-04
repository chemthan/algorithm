#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;
struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point(const Point& p) : x(p.x), y(p.y) {}
	bool operator < (const Point& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
	bool operator == (const Point& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
	Point operator + (const Point& p) const {return Point(x + p.x, y + p.y);}
	Point operator - (const Point& p) const {return Point(x - p.x, y - p.y);}
	Point operator * (double c) const {return Point(x * c, y * c);}
	Point operator / (double c) const {return Point(x / c, y / c);}
};
double cross(Point p, Point q) {return p.x * q.y - p.y * q.x;}
double area(Point a, Point b, Point c) {return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;}
double area2(Point a, Point b, Point c) {return cross(a, b) + cross(b, c) + cross(c, a);}
double dot(Point p, Point q) {return p.x * q.x + p.y * q.y;}
double dist(Point p, Point q) {return sqrt(dot(p - q, p - q));}
double dist2(Point p, Point q) {return dot(p - q, p - q);}

Point RotateCCW90(Point p) {return Point(-p.y, p.x);}
Point RotateCW90(Point p) {return Point(p.y, -p.x);}
Point RotateCCW(Point p, double t) {
	return Point(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}
Point ProjectPointLine(Point a, Point b, Point c) {
	return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}
Point ProjectPointSegment(Point a, Point b, Point c) {
	double r = dot(b - a, b - a);
	if (fabs(r) < EPS) return a;
	r = dot(c - a, b - a) / r;
	if (r < 0) return a;
	if (r > 1) return b;
	return a + (b - a) * r;
}
double DistancePointSegment(Point a, Point b, Point c) {
	return dist(c, ProjectPointSegment(a, b, c));
}
//Compute distance between point (x, y, z) and plane ax + by + cz = d
double DistancePointPlane(double x, double y, double z, double a, double b, double c, double d) {
	return fabs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}
//Determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(Point a, Point b, Point c, Point d) {
	return fabs(cross(b - a, c - d)) < EPS;
}
bool LinesCollinear(Point a, Point b, Point c, Point d) {
	return LinesParallel(a, b, c, d) && fabs(cross(a-b, a-c)) < EPS && fabs(cross(c-d, c-a)) < EPS;
}
//Determine if line segment from a to b intersects with line segment from c to d
bool SegmentsIntersect(Point a, Point b, Point c, Point d) {
	if (LinesCollinear(a, b, c, d)) {
		if (dist2(a, c) < EPS || dist2(a, d) < EPS || dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
		if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0) return false;
		return true;
	}
	if (cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
	if (cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
	return true;
}
//Compute intersection of line passing through a and b
//with line passing through c and d, assuming that unique
//intersection exists; for segment intersection, check if
//segments intersect first
Point ComputeLineIntersection(Point a, Point b, Point c, Point d) {
	b = b - a; d = c - d; c = c - a;
	assert(dot(b, b) > EPS && dot(d, d) > EPS);
	return a + b * cross(c, d) / cross(b, d);
}
//Compute center of circle given three points
Point ComputeCircleCenter(Point a, Point b, Point c) {
	b=(a + b) / 2;
	c=(a + c) / 2;
	return ComputeLineIntersection(b, b+RotateCW90(a - b), c, c+RotateCW90(a - c));
}
//Determine if point is in a possibly non-convex polygon
//returns 1 for strictly interior points, 0 for
//strictly exterior points, and 0 or 1 for the remaining points.
bool PointInPolygonSlow(const vector<Point>& p, Point q) {
	bool c = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		if ((p[i].y <= q.y && q.y < p[j].y || p[j].y <= q.y && q.y < p[i].y) && q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y)) c = !c;
	}
	return c;
}
//Strictly inside Polygon
#define Det(a, b, c) ((b.x - a.x) * (c.y - a.y)-(b.y - a.y) * (c.x - a.x))
bool PointInPolygon(vector<Point>& l, Point p) {
	int a = 1, b = l.size() - 1, c;
	if (Det(l[0], l[a], l[b]) > 0) swap(a, b);
	if (Det(l[0], l[a], p) >= 0 || Det(l[0], l[b], p) <= 0) return false;
	while(abs(a - b) > 1) {
		c = (a + b) / 2;
		if (Det(l[0], l[c], p) > 0) b = c; else a = c;
	}
	return Det(l[a], l[b], p) < 0;
}
//Determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<Point>& p, Point q) {
	for (int i = 0; i < p.size(); i++) if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS) return true;
	return false;
}
//Compute intersection of line through points a and b with circle centered at c with radius r > 0
vector<Point> CircleLineIntersection(Point a, Point b, Point c, double r) {
	vector<Point> ret;
	b = b - a; a = a - c;
	double A = dot(b, b);
	double B = dot(a, b);
	double C = dot(a, a) - r * r;
	double D = B * B - A * C;
	if (D < -EPS) return ret;
	ret.push_back(c + a + b * (-B + sqrt(D+EPS)) / A);
	if (D > EPS) ret.push_back(c + a + b * (-B - sqrt(D)) / A);
	return ret;
}
//Compute intersection of circle centered at a with radius r with circle centered at b with radius R
vector<Point> CircleCircleIntersection(Point a, Point b, double r, double R) {
	vector<Point> ret;
	double d = sqrt(dist2(a, b));
	if (d > r + R || d + min(r, R) < max(r, R)) return ret;
	double x = (d * d - R * R + r * r) / (2 * d);
	double y = sqrt(r * r - x * x);
	Point v = (b - a) / d;
	ret.push_back(a + v * x + RotateCCW90(v) * y);
	if (y > 0) ret.push_back(a + v * x - RotateCCW90(v) * y);
	return ret;
}

//This code computes the area or centroid of a (possibly nonconvex)
//polygon, assuming that the coordinates are listed in a clockwise or
//counterclockwise fashion.  Note that the centroid is often known as
//the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<Point>& p) {
	double area = 0;
	for(int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		area += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return area / 2.0;
}
double ComputeArea(const vector<Point>& p) {
	return fabs(ComputeSignedArea(p));
}
Point ComputeCentroid(const vector<Point>& p) {
	Point c(0, 0);
	double scale = 6.0 * ComputeSignedArea(p);
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
	}
	return c / scale;
}
//Tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<Point>& p) {
	for (int i = 0; i < p.size(); i++) {
		for (int k = i + 1; k < p.size(); k++) {
			int j = (i + 1) % p.size();
			int l = (k + 1) % p.size();
			if (i == l || j == k) continue;
			if (SegmentsIntersect(p[i], p[j], p[k], p[l])) return false;
		}
	}
	return true;
}

ostream &operator<<(ostream& os, const Point& p) {
	os<<"("<<p.x<<","<<p.y<<")";
}

int main() {

	// expected: (-5,2)
	cerr << RotateCCW90(Point(2,5)) << endl;

	// expected: (5,-2)
	cerr << RotateCW90(Point(2,5)) << endl;

	// expected: (-5,2)
	cerr << RotateCCW(Point(2,5),M_PI/2) << endl;

	// expected: (5,2)
	cerr << ProjectPointLine(Point(-5,-2), Point(10,4), Point(3,7)) << endl;

	// expected: (5,2) (7.5,3) (2.5,1)
	cerr << ProjectPointSegment(Point(-5,-2), Point(10,4), Point(3,7)) << " "
		<< ProjectPointSegment(Point(7.5,3), Point(10,4), Point(3,7)) << " "
		<< ProjectPointSegment(Point(-5,-2), Point(2.5,1), Point(3,7)) << endl;

	// expected: 6.78903
	cerr << DistancePointPlane(4,-4,3,2,-2,5,-8) << endl;

	// expected: 1 0 1
	cerr << LinesParallel(Point(1,1), Point(3,5), Point(2,1), Point(4,5)) << " "
		<< LinesParallel(Point(1,1), Point(3,5), Point(2,0), Point(4,5)) << " "
		<< LinesParallel(Point(1,1), Point(3,5), Point(5,9), Point(7,13)) << endl;

	// expected: 0 0 1
	cerr << LinesCollinear(Point(1,1), Point(3,5), Point(2,1), Point(4,5)) << " "
		<< LinesCollinear(Point(1,1), Point(3,5), Point(2,0), Point(4,5)) << " "
		<< LinesCollinear(Point(1,1), Point(3,5), Point(5,9), Point(7,13)) << endl;

	// expected: 1 1 1 0
	cerr << SegmentsIntersect(Point(0,0), Point(2,4), Point(3,1), Point(-1,3)) << " "
		<< SegmentsIntersect(Point(0,0), Point(2,4), Point(4,3), Point(0,5)) << " "
		<< SegmentsIntersect(Point(0,0), Point(2,4), Point(2,-1), Point(-2,1)) << " "
		<< SegmentsIntersect(Point(0,0), Point(2,4), Point(5,5), Point(1,7)) << endl;

	// expected: (1,2)
	cerr << ComputeLineIntersection(Point(0,0), Point(2,4), Point(3,1), Point(-1,3)) << endl;

	// expected: (1,1)
	cerr << ComputeCircleCenter(Point(-3,4), Point(6,1), Point(4,5)) << endl;

	vector<Point> v;
	v.push_back(Point(0,0));
	v.push_back(Point(5,0));
	v.push_back(Point(5,5));
	v.push_back(Point(0,5));

	// expected: 1 1 1 0 0
	cerr << PointInPolygonSlow(v, Point(2,2)) << " "
		<< PointInPolygonSlow(v, Point(2,0)) << " "
		<< PointInPolygonSlow(v, Point(0,2)) << " "
		<< PointInPolygonSlow(v, Point(5,2)) << " "
		<< PointInPolygonSlow(v, Point(2,5)) << endl;

	// expected: 0 1 1 1 1
	cerr << PointOnPolygon(v, Point(2,2)) << " "
		<< PointOnPolygon(v, Point(2,0)) << " "
		<< PointOnPolygon(v, Point(0,2)) << " "
		<< PointOnPolygon(v, Point(5,2)) << " "
		<< PointOnPolygon(v, Point(2,5)) << endl;

	// expected: (1,6)
	//           (5,4) (4,5)
	//           blank line
	//           (4,5) (5,4)
	//           blank line
	//           (4,5) (5,4)
	vector<Point> u = CircleLineIntersection(Point(0,6), Point(2,6), Point(1,1), 5);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleLineIntersection(Point(0,9), Point(9,0), Point(1,1), 5);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleCircleIntersection(Point(1,1), Point(10,10), 5, 5);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleCircleIntersection(Point(1,1), Point(8,8), 5, 5);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleCircleIntersection(Point(1,1), Point(4.5,4.5), 10, sqrt(2.0)/2.0);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;
	u = CircleCircleIntersection(Point(1,1), Point(4.5,4.5), 5, sqrt(2.0)/2.0);
	for (int i = 0; i < u.size(); i++) cerr << u[i] << " "; cerr << endl;

	// area should be 5.0
	// centroid should be (1.1666666, 1.166666)
	Point pa[] = { Point(0,0), Point(5,0), Point(1,1), Point(0,5) };
	vector<Point> p(pa, pa+4);
	Point c = ComputeCentroid(p);
	cerr << "Area: " << ComputeArea(p) << endl;
	cerr << "Centroid: " << c << endl;

	return 0;
}
