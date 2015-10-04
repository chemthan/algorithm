#include <bits/stdc++.h>
using namespace std;

//Minimum Manhattan Spanning Tree
struct Point {
	int x, y;
	int idx;
	int t, d, nxt;
};

bool comparey(Point a, Point b) {
	return make_pair(a.y, a.x) < make_pair(b.y, b.x);
}

bool comparesum(Point a, Point b) {
	return make_pair(a.x + a.y, a.y) < make_pair(b.x + b.y, b.y);
}

bool comparesub(Point a, Point b) {
	return make_pair(a.x - a.y, a.y) < make_pair(b.x - b.y, b.y);
}

const int maxn = 100010;
int n;
Point p[maxn];
int x[maxn];
int y[maxn];

int par[maxn];
void init() {
	for (int i = 0; i < n; i++) par[i] = i;
}
int find(int u) {
	return par[u] == u ? par[u] : par[u] = find(par[u]);
}
void joint(int u, int v) {
	par[find(u)] = par[find(v)];
}

void go1(int l, int r) {
	if (p[l].y < p[r].y) {
		int k = (p[l].y + p[r].y) >> 1;
		int m; for (m = l; m <= r; m++) if (p[m].y > k) break; m--;
		go1(l, m); go1(m + 1, r);
		for (int i = l; i <= m; i++) p[i].t = 0;
		for (int i = m + 1; i <= r; i++) p[i].t = 1;
		sort(p + l, p + r + 1, comparesum);
		int cur = INT_MIN, idx = -1;
		for (int i = l; i <= r; i++) {
			if (p[i].t == 0) {
				if (p[i].d < cur) {
					p[i].d = cur;
					p[i].nxt = idx;
				}
			}
			else {
				if (cur < p[i].x - p[i].y) {
					cur = p[i].x - p[i].y;
					idx = p[i].idx;
				}
			}
		}
	}
	else for (int i = l + 1; i <= r; i++) {
		p[i].d = p[i - 1].x - p[i - 1].y;
		p[i].nxt = p[i - 1].idx;
	}
}

void go2(int l, int r) {
	if (p[l].y < p[r].y) {
		int k = (p[l].y + p[r].y) >> 1;
		int m; for (m = l; m <= r; m++) if (p[m].y > k) break; m--;
		go2(l, m); go2(m + 1, r);
		for (int i = l; i <= m; i++) p[i].t = 0;
		for (int i = m + 1; i <= r; i++) p[i].t = 1;
		sort(p + l, p + r + 1, comparesub);
		int cur = INT_MIN, idx = -1;
		for (int i = l; i <= r; i++) {
			if (p[i].t == 1) {
				if (p[i].d < cur) {
					p[i].d = cur;
					p[i].nxt = idx;
				}
			}
			else {
				if (cur < p[i].x + p[i].y) {
					cur = p[i].x + p[i].y;
					idx = p[i].idx;
				}
			}
		}
	}
	else for (int i = l + 1; i <= r; i++) {
		p[i].d = p[i - 1].x + p[i - 1].y;
		p[i].nxt = p[i - 1].idx;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {scanf("%d%d", &p[i].x, &p[i].y); x[i] = p[i].x; y[i] = p[i].y; p[i].idx = i;}
	priority_queue<pair<int, pair<int, int> > > pq;
	for (int _ = 0; _ < 4; _++) {
		for (int i = 0; i < n; i++) {p[i].y *= -1; swap(p[i].x, p[i].y);}
		for (int i = 0; i < n; i++) {
			p[i].d = INT_MIN;
			p[i].nxt = -1;
		}
		sort(p, p + n, comparey); go1(0, n - 1);
		for (int i = 0; i < n; i++) if (p[i].nxt != -1) {
			int u = p[i].idx;
			int v = p[i].nxt;
			pq.push(make_pair(-abs(x[u] - x[v]) - abs(y[u] - y[v]), make_pair(u, v)));
		}
		for (int i = 0; i < n; i++) {
			p[i].d = INT_MIN;
			p[i].nxt = -1;
		}
		sort(p, p + n, comparey); go2(0, n - 1);
		for (int i = 0; i < n; i++) if (p[i].nxt != -1) {
			int u = p[i].idx;
			int v = p[i].nxt;
			pq.push(make_pair(-abs(x[u] - x[v]) - abs(y[u] - y[v]), make_pair(u, v)));
		}
	}
	long long ans = 0; init();
	while (pq.size()) {
		int u = pq.top().second.first;
		int v = pq.top().second.second;
		if (find(u) != find(v)) {
			joint(u, v);
			ans -= pq.top().first;
		}
		pq.pop();
	}
	printf("%lld", ans);
	return 0;
}
