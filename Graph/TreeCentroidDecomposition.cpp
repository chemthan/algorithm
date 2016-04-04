#include <bits/stdc++.h>
using namespace std;

//O(nlogn)
const int MAXN = 100010;
int n;
vector<int> adj[MAXN];
int del[MAXN];
int size[MAXN];
void dfs(int u, int p) {
	size[u] = 1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p && !del[v]) {
			dfs(v, u);
			size[u] += size[v];
		}
	}
}
int findcenter(int u) {
	int p = -1; dfs(u, -1);
	int cap = size[u] >> 1;
	while (1) {
		bool found = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (v != p && !del[v] && size[v] > cap) {
				found = true;
				p = u; u = v;
				break;
			}
		}
		if (!found) return u;
	}
}
void work(int u) {
}
void tcd(int u) {
	u = findcenter(u);
	del[u] = 1; work(u);
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (!del[v]) {
			tcd(v);
		}
	}
}

int main() {
	return 0;
}
