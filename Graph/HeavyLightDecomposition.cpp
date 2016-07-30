#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;
int n;
vector<int> adj[MAXN];
int size[MAXN];
int lev[MAXN];
int p[MAXN];
int num[MAXN];
int head[MAXN];
int cnt;

void upd(int l, int r, int n, int val) {} //Need to modify
int query(int l, int r, int n) {return 0;} //Need to modify
void dfs1(int u, int dad = -1) {
	size[u] = 1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != dad) {
			p[v] = u, lev[v] = lev[u] + 1;
			dfs1(v, u);
			size[u] += size[v];
		}
	}
}
void dfs2(int u, int h, int dad = -1) {
	num[u] = cnt++, head[u] = h;
	pair<int, int> best = make_pair(-1, -1);
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != dad) {
			best = max(best, make_pair(lev[v], v));
		}
	}
	if (~best.second) {
		dfs2(best.second, h, u);
	}
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != dad && v != best.second) {
			dfs2(v, v, u);
		}
	}
}
void upd(int u, int v, int val) {
	int hu = head[u], hv = head[v];
	while (hu != hv) {
		if (lev[hu] < lev[hv]) swap(u, v), swap(hu, hv);
		upd(num[hu], num[u], n, val);
		u = p[hu], hu = head[u];
	}
	if (lev[u] > lev[v]) swap(u, v);
	upd(num[u], num[v], n, val); //upd(num[u] + 1, num[v]) for edge path
}
int query(int u, int v) {
	int res = 0;
	int hu = head[u], hv = head[v];
	while (hu != hv) {
		if (lev[hu] < lev[hv]) swap(u, v), swap(hu, hv);
		res += query(num[hu], num[u], n);
		u = p[hu], hu = head[u];
	}
	if (lev[u] > lev[v]) swap(u, v);
	res += query(num[u], num[v], n); //query(num[u] + 1, num[v]) for edge path
	return res;
}

int main() {
	return 0;
}
