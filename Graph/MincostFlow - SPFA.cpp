#include <bits/stdc++.h>
using namespace std;

//MincostFlow
//O(min(E^2*V*logV, E*logV*Flow))
struct MincostFlow {
	typedef long long T;
	static const T oo = (T) 1e18;
	static const int MAXV = 1000 + 10;
	static const int MAXE = 1000000 + 10;
	int n, s, t, E, adj[MAXE], next[MAXE], last[MAXV], which[MAXV];
	T totalCost, totalFlow, cap[MAXE], flow[MAXE], cost[MAXE], dist[MAXV], vis[MAXV];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t;
		memset(last, -1, sizeof(last)); E = 0;
	}
	void add(int u, int v, T ca, T co) {
		adj[E] = v; cap[E] = ca; flow[E] = 0; cost[E] = +co; next[E] = last[u]; last[u] = E++;
		adj[E] = u; cap[E] =  0; flow[E] = 0; cost[E] = -co; next[E] = last[v]; last[v] = E++;
	}
	int spfa() {
		for (int u = 0; u < n; u++) dist[u] = oo;
		dist[s] = 0;
		queue<int> que; que.push(s);
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (int e = last[u]; e != -1; e = next[e]) if (flow[e] < cap[e]) {
				int v = adj[e];
				if (dist[v] > dist[u] + cost[e]) {
					dist[v] = dist[u] + cost[e];
					which[v] = e;
					if (!vis[v]) {
						vis[v] = 1;
						que.push(v);
					}
				}
			}
			vis[u] = 0;
		}
		return dist[t] < oo;
	}
	int maxflow(T desireFlow = oo) {
		totalCost = totalFlow = 0;
		while (totalFlow < desireFlow) {
			if (!spfa()) return 0;
			T delta = desireFlow - totalFlow;
			for (int v = t, e = which[v]; v != s; v = adj[e ^ 1], e = which[v]) delta = min(delta, cap[e] - flow[e]);
			for (int v = t, e = which[v]; v != s; v = adj[e ^ 1], e = which[v]) {
				flow[e] += delta;
				flow[e ^ 1] -= delta;
			}
			totalFlow += delta;
			totalCost += delta * dist[t];
		}
		return 1;
	}
} mcf;

int main() {
	mcf.init(3, 0, 2);
	mcf.add(0, 1, 1, 3);
	mcf.add(1, 2, 1, 10);
	mcf.add(0, 2, 1, 100);
	mcf.maxflow();
	cout << mcf.totalCost << "\n";
	return 0;
}
