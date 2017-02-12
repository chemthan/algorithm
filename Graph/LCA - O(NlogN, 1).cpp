#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int LOGN = 20;
int n;
vector<int> adj[MAXN];
vector<int> event;
int st[MAXN];
int tin[MAXN];
int idx[MAXN];
int tms;

int f[LOGN][MAXN << 1];
void build() {
	for (int i = 0; i < event.size(); i++) {
		f[0][i] = event[i];
	}
	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j + (1 << i - 1) < event.size(); j++) {
			f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
		}
	}
}
int query(int u, int v) {
	int l = u == v ? 0 : __lg(v - u);
	return min(f[l][u], f[l][v - (1 << l) + 1]);
}
void dfs(int u, int p = -1) {
	idx[tin[u] = tms++] = u;
	st[u] = event.size();
	event.push_back(tin[u]);
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p) {
			dfs(v, u);
			event.push_back(tin[u]);
		}
	}
}
int lca(int u, int v) {
	if (st[u] > st[v]) swap(u, v);
	return idx[query(st[u], st[v])];
}

int main() {
	return 0;
}
