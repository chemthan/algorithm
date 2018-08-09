#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N*sqrt(N))
*/
struct Query {
	static const int MAGIC = 320;
	int l, r, a, idx;
	int operator < (const Query& rhs) {
		if (l / MAGIC != rhs.l / MAGIC) return l / MAGIC < rhs.l / MAGIC;
		return r < rhs.r;
	}
};
const int MAXN = 100000 + 10;
const int LOGN = 20;
int n, q;
vector<int> adj[MAXN];
Query query[MAXN];
int p[LOGN][MAXN];
int vis[MAXN];
int lev[MAXN];
int tin[MAXN];
int tou[MAXN];
int idx[MAXN << 1];
int tms;

void dfs(int u, int dad = -1) {
	idx[tin[u] = tms++] = u;
	for (int i = 1; i < LOGN; i++) p[i][u] = p[i - 1][p[i - 1][u]];
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != dad) {
			lev[v] = lev[u] + 1;
			p[0][v] = u;
			dfs(v, u);
		}
	}
	idx[tou[u] = tms++] = u;
}
int isparent(int u, int v) {
	return tin[u] <= tin[v] && tou[u] >= tou[v];
}
int lca(int u, int v) {
	if (lev[u] < lev[v]) swap(u, v);
	if (isparent(v, u)) return v;
	for (int i = LOGN - 1; i >= 0; i--) {
		if (lev[p[i][u]] >= lev[v]) {
			u = p[i][u];
		}
	}
	for (int i = LOGN - 1; i >= 0; i--) {
		if (p[i][u] != p[i][v]) {
			u = p[i][u];
			v = p[i][v];
		}
	}
	return p[0][u];
}

void add(int u) {} //Need to modify
void rem(int u) {} //Need to modify
void deal(int u) {if (vis[u] ^= 1) add(u); else rem(u);}

int main() {
	cin >> n >> q;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--, v--;
		adj[u].push_back(v), adj[v].push_back(u);
	}
	dfs(0);
	for (int i = 0; i < q; i++) {
		int u, v; cin >> u >> v; u--, v--;
		if (lev[u] > lev[v]) swap(u, v);
		int a = lca(u, v);
		if (u == a) {
			query[i].l = tin[u];
			query[i].r = tin[v];
			query[i].a = -1;
		}
		else {
			query[i].l = tou[u];
			query[i].r = tin[v];
			query[i].a = a;
		}
		query[i].idx = i;
	}
	sort(query, query + q);
	int l = 0, r = -1;
	for (int i = 0; i < q; i++) {
		while (l < query[i].l) deal(idx[l++]);
		while (l > query[i].l) deal(idx[--l]);
		while (r < query[i].r) deal(idx[++r]);
		while (r > query[i].r) deal(idx[r--]);
		if (~query[i].a) deal(query[i].a);
		//get ans
		if (~query[i].a) deal(query[i].a);
	}
	return 0;
}
