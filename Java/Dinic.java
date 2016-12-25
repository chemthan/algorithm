public class Dinic {
	int E, adj[], lst[], nxt[], flw[], cap[], lev[];
	int n, s, t;

	public Dinic(int n, int s, int t, int maxe) {
		E = 0;
		lst = new int[n];
		Arrays.fill(lst, -1);
		lev = new int[n];
		nxt = new int[maxe << 1];
		adj = new int[maxe << 1];
		flw = new int[maxe << 1];
		cap = new int[maxe << 1];
		this.n = n;
		this.s = s;
		this.t = t;
	}

	public void add(int u, int v, int c) {
		adj[E] = v; nxt[E] = lst[u]; flw[E] = 0; cap[E] = c; lst[u] = E++;
		adj[E] = u; nxt[E] = lst[v]; flw[E] = 0; cap[E] = 0; lst[v] = E++;
	}

	public boolean bfs() {
		Arrays.fill(lev, -1);
		int[] que = new int[n];
		lev[s] = 0;
		int qe = 0;
		que[qe++] = s;
		for (int i = 0; i < qe; i++) {
			int u = que[i];
			for (int e = lst[u]; e != -1; e = nxt[e]) if (flw[e] < cap[e]) {
				int v = adj[e];
				if (lev[v] == -1) {
					lev[v] = lev[u] + 1;
					que[qe++] = v;
				}
			}
		}
		return lev[t] != -1;
	}

	public int argument(int u, int mx) {
		if (u == t) return mx;
		for (int e = lst[u]; e != -1; e = nxt[e]) if (flw[e] < cap[e]) {
			int v = adj[e];
			if (lev[v] == lev[u] + 1 && (mx = argument(v, Math.min(mx, cap[e] - flw[e]))) > 0) {
				flw[e] += mx;
				flw[e ^ 1] -= mx;
				return mx;
			}
		}
		return 0;
	}

	public int maxflow() {
		int res = 0;
		while (bfs()) {
			int tmp = 0;
			while ((tmp = argument(s, (int) 1e9)) > 0) {
				res += tmp;
			}
		}
		return res;
	}
}
