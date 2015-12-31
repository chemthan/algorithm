#include <bits/stdc++.h>
using namespace std;

#define T long double
#define oo 1e18
struct Convexhull {
	struct Line {
		T a, b;
		Line(T a, T b) : a(a), b(b) {}
	};
	long double intersect(Line ln1, Line ln2) {
		return -1.0 * (ln1.b - ln2.b) / (ln1.a - ln2.a);
	}
	int bad(Line ln1, Line ln2, Line ln3) {
		return (ln1.a - ln2.a) * (ln2.b - ln3.b) >= (ln2.a - ln3.a) * (ln1.b - ln2.b);
		//return intersect(ln1, ln2) >= intersect(ln2, ln3);
	}
	vector<Line> hull;
	vector<long double> pos;
	Convexhull() {
		pos.push_back(-oo);
		pos.push_back(+oo);
	}
	void add(T a, T b) {
		Line ln(a, b);
		pos.pop_back();
		while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull[hull.size() - 1], ln)) {
			hull.pop_back();
			pos.pop_back();
		}
		hull.push_back(ln);
		if (hull.size() >= 2) pos.push_back(intersect(hull[hull.size() - 2], hull[hull.size() - 1]));
		pos.push_back(+oo);
	}
	T query(T x) {
		int k = lower_bound(pos.begin(), pos.end(), x) - pos.begin() - 1;
		return hull[k].a * x + hull[k].b;
	}
} convexhull;

struct Node {
	vector<pair<T, T> > line;
	Convexhull hull;
} null;

Node merge(Node n1, Node n2) {
	Node res;
	vector<pair<T, T> > t;
	int u = 0, v = 0;
	while (u < n1.line.size() || v < n2.line.size()) {
		if (u == n1.line.size()) t.push_back(n2.line[v++]);
		else if (v == n2.line.size()) t.push_back(n1.line[u++]);
		else {
			if (n1.line[u] < n2.line[v]) t.push_back(n1.line[u++]);
			else t.push_back(n2.line[v++]);
		}
	}
	for (int i = 0; i < t.size(); i++) if (!i || t[i].first != t[i - 1].first) res.line.push_back(t[i]);
	for (int i = res.line.size() - 1; i >= 0; i--) res.hull.add(res.line[i].first, res.line[i].second);
	return res;
}

const int maxn = 100010;
T a[maxn];
T b[maxn];
struct SegmentTree {
	Node st[4 * maxn];
	void build(int node, int L, int R) {
		if (L == R) {
			st[node].line.push_back(make_pair(a[L], b[L]));
			st[node].hull.add(a[L], b[L]);
			return;
		}
		build(node << 1, L, (L + R) >> 1);
		build((node << 1) + 1, ((L + R) >> 1) + 1, R);
		st[node] = merge(st[node << 1], st[(node << 1) + 1]);
	}
	Node query(int node, int l, int r, int L, int R) {
		if (l > R || r < L) return null;
		if (l <= L && r >= R) return st[node];
		return merge(query(node << 1, l, r, L, (L + R) >> 1), query((node << 1) + 1, l, r, ((L + R) >> 1) + 1, R));
	}
};

int main() {
	convexhull.add(2.0 / 3, 4.0 / 3);
	convexhull.add(0, 4);
	convexhull.add(-1.0 / 2, 3);
	convexhull.add(-3, 12);
	cout<<convexhull.query(1); //Should be 2
	return 0;
}
