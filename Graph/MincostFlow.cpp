#include <bits/stdc++.h>
using namespace std;

//MincostFlow
//O(|V|^4 * MAX_EDGE_COST)
#define maxv 1000010
#define maxe 1000010
#define linf 1000000000000000000LL
struct MincostFlow {
	int n, s, t, E, adj[maxe], next[maxe], last[maxv], which[maxv];
	long long totalCost, totalFlow, cap[maxe], flow[maxe], cost[maxe], pot[maxe], dist[maxv];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t;
		memset(last, -1, sizeof(last)); E = 0;
	}
	void add(int u, int v, long long ca, long long co) {
		adj[E] = v; cap[E] = ca; flow[E] = 0; cost[E] = +co; next[E] = last[u]; last[u] = E++;
		adj[E] = u; cap[E] =  0; flow[E] = 0; cost[E] = -co; next[E] = last[v]; last[v] = E++;
	}
	void bellman() {
		bool stop = false;
		memset(pot, 0, sizeof(pot));
		while (!stop) {
			stop = true;
			for (int u = 0; u < n; u++) for (int e = last[u]; e != -1; e = next[e]) if (flow[e] < cap[e]) {
				int v = adj[e];
				if (pot[v] > pot[u] + cost[e]) {
					pot[v] = pot[u] + cost[e];
					stop = false;
				}
			}
		}
	}
	bool dijkstra() {
		typedef pair<long long, int> node;
		priority_queue<node, vector<node>, greater<node> > que;
		for (int u = 0; u < n; u++) dist[u] = linf;
		dist[s] = 0;
		que.push(make_pair(0, s));
		while (!que.empty()) {
			long long dnow = que.top().first;
			int u = que.top().second;
			que.pop();
			if (dnow > dist[u]) continue;
			for (int e = last[u]; e != -1; e = next[e]) if (flow[e] < cap[e]) {
				int v = adj[e];
				long long dnext = dnow + cost[e] + pot[u] - pot[v];
				if (dist[v] > dnext) {
					dist[v] = dnext;
					which[v] = e;
					que.push(make_pair(dnext, v));
				}
			}
		}
		return dist[t] < linf;
	}
	bool maxflow(long long desireFlow = linf) {
		totalCost = totalFlow = 0;
		bellman();
		while (totalFlow < desireFlow) {
			if (!dijkstra()) return false;
			long long delta = desireFlow - totalFlow;
			for (int v = t, e = which[v]; v != s; v = adj[e ^ 1], e = which[v]) delta = min(delta, cap[e] - flow[e]);
			for (int v = t, e = which[v]; v != s; v = adj[e ^ 1], e = which[v]) {
				flow[e] += delta;
				flow[e ^ 1] -= delta;
			}
			totalFlow += delta;
			totalCost += delta * (dist[t] - pot[s] + pot[t]);
			for (int u = 0; u < n; u++) pot[u] += dist[u];
		}
		return true;
	}
} mcf;

int main() {
	mcf.init(3, 0, 2);
	mcf.add(0, 1, 1, 3);
	mcf.add(1, 2, 1, 10);
	mcf.add(0, 2, 1, 100);
	mcf.maxflow();
	printf("%lld", mcf.totalCost);
	return 0;
}
