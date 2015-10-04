#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;
int n;
vector<int> adj[maxn];

const int maxe = 30;
int nchain, nbase;
int hchain[maxn];
int ichain[maxn];
int size[maxn];
int pib[maxn];
int vis[maxn];
int lev[maxn];
int p[maxe][maxn];
int tin[maxn];
int tou[maxn];
int tms;

void init() {
	memset(vis, 0, sizeof(vis)); memset(p, 0, sizeof(p)); memset(lev, 0, sizeof(lev));
	memset(hchain, -1, sizeof(hchain)); memset(ichain, -1, sizeof(ichain)); memset(pib, -1, sizeof(pib));
	tms = nchain = nbase = 0;
}
void dfs(int u) {
	tin[u] = tms++;
	vis[u] = size[u] = 1;
	for (int i = 1; i < maxe; i++) p[i][u] = p[i - 1][p[i - 1][u]];
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (!vis[v]) {
			p[0][v] = u; lev[v] = lev[u] + 1; dfs(v);
			size[u] += size[v];
		}
	}
	tou[u] = tms++;
}
int lca(int u, int v) {
	if (lev[u] < lev[v]) swap(u, v);
	if (tin[v] <= tin[u] && tou[v] >= tou[u]) return v;
	for (int i = maxe - 1; i >= 0; i--) if (lev[u] - (1 << i) >= lev[v]) u = p[i][u];
	for (int i = maxe - 1; i >= 0; i--) if (p[i][u] != p[i][v]) {u = p[i][u]; v = p[i][v];}
	return p[0][u];
}
void hld(int u) {
	if (hchain[nchain] == -1) hchain[nchain] = u;
	ichain[u] = nchain;
	pib[u] = nbase++;
	int tmp = -1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p[0][u]) {if (tmp == -1 || size[v] > size[tmp]) tmp = v;}
	}
	if (tmp != -1) hld(tmp);
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p[0][u] && v != tmp) {nchain++; hld(v);}
	}
}
void update(int u, int a) {
	int uchain = ichain[u], achain = ichain[a];
	while (1) {
		if (uchain == achain) {
			//update(1, pib[a] + 1, pib[u], 0, n - 1);
			return;
		}
		//update(1, pib[hchain[uchain]], pib[u], 0, n - 1);
		u = p[0][hchain[uchain]];
		uchain = ichain[u];
	}
}

int main() {
    return 0;
}
