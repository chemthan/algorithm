#include <bits/stdc++.h>
using namespace std;

//O(V^1/2*E)
const int MAXV = 1010;
const int MAXE = 1000010;
struct Blossom {
	int n, E, lst[MAXV], next[MAXE], adj[MAXE];
	int nxt[MAXV], mat[MAXV], dad[MAXV], col[MAXV];
	int que[MAXV], qh, qt;
	int vis[MAXV], act[MAXV];
	int tag, total;
	
	void init(int _n) {
		n = _n;
		for (int i = 0; i <= n; i++) lst[i] = nxt[i] = mat[i] = vis[i] = 0;
		E = 1; tag = total = 0;
	}
	void add(int u,int v) {
		if(!mat[u] && !mat[v]) {mat[u] = v; mat[v] = u; total++;}
		E++; adj[E] = v; next[E] = lst[u]; lst[u] = E;
		E++; adj[E] = u; next[E] = lst[v]; lst[v] = E;
	}
	int lca(int u, int v) {
		tag++;
		for(; ; swap(u, v)) {
			if (u) {
				if (vis[u = dad[u]] == tag) {
					return u;
				}
				vis[u] = tag;
				u = nxt[mat[u]];
			}
		}
	}
	void blossom(int u, int v, int g) {
		while (dad[u] != g) {
			nxt[u] = v;
			if (col[mat[u]] == 2) {
				col[mat[u]] = 1;
				que[++qt] = mat[u];
			}
			if (u == dad[u]) dad[u] = g;
			if (mat[u] == dad[mat[u]]) dad[mat[u]] = g;
			v = mat[u];
			u = nxt[v];
		}
	}
	int augument(int s) {
		for (int i = 1; i <= n; i++) {
			col[i] = 0;
			dad[i] = i;
		}
		qh = 0; que[qt = 1] = s; col[s] = 1;
		for (int u, v, i; qh < qt; ) {
			act[u = que[++qh]] = 1;
			for (i = lst[u];i ; i = next[i]) {
				v = adj[i];
				if (col[v] == 0) {
					nxt[v] = u;
					col[v] = 2;
					if (!mat[v]) {
						for (; v; v = u) {
							u = mat[nxt[v]];
							mat[v] = nxt[v];
							mat[nxt[v]] = v;
						}
						return 1;
					}
					col[mat[v]] = 1;
					que[++qt] = mat[v];
				}
				else if (dad[u] != dad[v] && col[v] == 1) {
					int g = lca(u, v);
					blossom(u, v, g);
					blossom(v, u, g);
					for (int j = 1; j <= n; j++) {
						dad[j] = dad[dad[j]];
					}
				}
			}
		}
		return 0;
	}
	int maxmat() {
		for (int i = 1; i <= n; i++) {
			if (!mat[i]) {
				total += augument(i);
			}
		}
		return total;
	}
} blossom;

int main() {
	return 0;
}
