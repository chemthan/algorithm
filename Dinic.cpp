#include <bits/stdc++.h>
using namespace std;

//Dinic
//O(|V|^2 * |E|)
#define maxv 1000010
#define maxe 1000010
#define inf 1000000000
struct Dinic {
	int n, s, t, E, adj[maxe], flow[maxe], cap[maxe], next[maxe], last[maxv], run[maxv], level[maxv], que[maxv];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t; E = 0;
		for (int i = 0; i <= n; i++) last[i] = -1;
	}
	void add(int u, int v, int c1, int c2) {
		adj[E] = v; flow[E] = 0; cap[E] = c1; next[E] = last[u]; last[u] = E++;
		adj[E] = u; flow[E] = 0; cap[E] = c2; next[E] = last[v]; last[v] = E++;
	}
	bool bfs() {
		for (int i = 0; i <= n; i++) level[i] = -1;
		level[s] = 0;
		int qsize = 0;
		que[qsize++] = s;
		for (int i = 0; i < qsize; i++) {
			for (int u = que[i], e = last[u]; e != -1; e = next[e]) {
				int v = adj[e];
				if (flow[e] < cap[e] && level[v] == -1) {
					level[v] = level[u] + 1;
					que[qsize++] = v;
				}
			}
		}
		return level[t] != -1;
	}
	int dfs(int u, int bot) {
		if (u == t) return bot;
		for (int &e = run[u]; e != -1; e = next[e]) {
			int v = adj[e], delta = 0;
			if (level[v] == level[u] + 1 && flow[e] < cap[e] && (delta = dfs(v, min(bot, cap[e] - flow[e]))) > 0) {
				flow[e] += delta; flow[e ^ 1] -= delta;
				return delta;
			}
		}
		return 0;
	}
	int maxflow() {
		int total = 0;
		while (bfs()) {
			for (int i = 0; i <= n; i++) run[i] = last[i];
			for (int delta = dfs(s, inf); delta > 0; delta = dfs(s, inf)) total += delta;
		}
		return total;
	}
} dinic;

int main() {
    dinic.init(3, 0, 2);
    dinic.add(0, 1, 2, 0);
    dinic.add(1, 2, 3, 0);
    printf("%d", dinic.maxflow());
    return 0;
}
