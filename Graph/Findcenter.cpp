#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
vector<int> adj[MAXN];
int size[MAXN];
void dfs(int u, int p) {
	size[u] = 1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p) {
			dfs(v, u);
			size[u] += size[v];
		}
	}
}
int findcenter(int u) {
	int p = -1; dfs(u, -1);
	int cap = size[u] >> 1;
	while (1) {
		int found = 0;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (v != p && size[v] > cap) {
				found = 1;
				p = u; u = v;
				break;
			}
		}
		if (!found) return u;
	}
}

int main() {
	return 0;
}
