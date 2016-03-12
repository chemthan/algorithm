#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;
vector<int> adj[maxn];
int size[maxn];

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
		bool found = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (v != p && size[v] > cap) {
				found = true;
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
