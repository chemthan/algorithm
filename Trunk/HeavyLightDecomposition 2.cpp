#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;
const int LOGN = 20;
int n;
vector<int> adj[MAXN];
int nchain, nbase;
int hchain[MAXN];
int ichain[MAXN];
int size[MAXN];
int pib[MAXN];
int lev[MAXN];
int p[MAXN][LOGN];
int tin[MAXN];
int tou[MAXN];
int tms;

void init() {
	memset(p, 0, sizeof(p)); memset(lev, 0, sizeof(lev));
	memset(hchain, -1, sizeof(hchain)); memset(ichain, -1, sizeof(ichain)); memset(pib, -1, sizeof(pib));
	tms = -1; nchain = nbase = 0;
}
void dfs(int u, int dad = -1) {
	tin[u] = ++tms;
	size[u] = 1;
	for (int i = 1; i < LOGN; i++) p[u][i] = p[p[u][i - 1]][i - 1];
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != dad) {
			p[v][0] = u; lev[v] = lev[u] + 1;
			dfs(v, u); size[u] += size[v];
		}
	}
	tou[u] = tms;
}
int lca(int u, int v) {
	if (lev[u] < lev[v]) swap(u, v);
	if (tin[v] <= tin[u] && tou[v] >= tou[u]) return v;
	for (int i = LOGN - 1; i >= 0; i--) if (lev[p[u][i]] >= lev[v]) u = p[u][i];
	for (int i = LOGN - 1; i >= 0; i--) if (p[u][i] != p[v][i]) {u = p[u][i]; v = p[v][i];}
	return p[u][0];
}
void hld(int u) {
	if (!~hchain[nchain]) hchain[nchain] = u;
	ichain[u] = nchain;
	pib[u] = nbase++;
	int tmp = -1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p[u][0] && (!~tmp || size[v] > size[tmp])) tmp = v;
	}
	if (~tmp) hld(tmp);
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != p[u][0] && v != tmp) {nchain++; hld(v);}
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
		u = p[hchain[uchain]][0];
		uchain = ichain[u];
	}
}

int main() {
	return 0;
}
