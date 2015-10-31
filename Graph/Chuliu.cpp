#include <bits/stdc++.h>
using namespace std;

//Index from 0
const int MAXV = 100010;
const int MAXE = 100010;
namespace Chuliu {
	int n, m, root, pre[MAXV], node[MAXV], vis[MAXV], best[MAXV];
	struct Cost;
	vector<Cost> costlist;
	struct Cost {
		int id, val, used, a, b, pos;
		Cost() {val = -1; used = 0;}
		Cost(int _id, int _val, bool temp) {
			a = b = -1; id = _id;
			val = _val; used = 0;
			pos = costlist.size();
			costlist.push_back(*this);
		}
		Cost(int _a, int _b) {
			a = _a; b = _b; id = -1;
			val = costlist[a].val - costlist[b].val;
			used = 0; pos = costlist.size();
			costlist.push_back(*this);
		}
		void push() {
			if (id == -1) {
				costlist[a].used += used;
				costlist[b].used -= used;
			}
		}
	};
	struct Edge {
		int u, v;
		Cost cost;
		Edge() {}
		Edge(int id, int _u, int _v, int c) {
			u = _u; v = _v;
			cost = Cost(id, c, 0);
		}
	} edge[MAXE];
	void init(int _n) {
		n = _n; m = 0;
		costlist.clear();
	}
	void add(int id, int u, int v, int c) {
		edge[m++] = Edge(id, u, v, c);
	}
	int mst(int root) {
		int res = 0;
		while (true) {
			for (int i = 0; i < n; i++) best[i] = -1;
			for (int e = 0; e < m; e++) {
				int u = edge[e].u, v = edge[e].v;
				if ((best[v] == -1 || edge[e].cost.val < costlist[best[v]].val) && u != v) {
					pre[v] = u;
					best[v] = edge[e].cost.pos;
				}
			}
			for (int i = 0; i < n; i++) if (i != root && best[i] == -1) return -1;
			int cntnode = 0;
			memset(node, -1, sizeof(node));
			memset(vis, -1, sizeof(vis));
			for (int i = 0; i < n; i++) if (i != root) {
				res += costlist[best[i]].val;
				costlist[best[i]].used++;
				int v = i;
				while (vis[v] != i && node[v] == -1 && v != root) {
					vis[v] = i;
					v = pre[v];
				}
				if (v != root && node[v] == -1) {
					for (int u = pre[v]; u != v; u = pre[u]) node[u] = cntnode;
					node[v] = cntnode++;
				}
			}
			if (cntnode == 0) break;
			for (int i = 0; i < n; i++) if (node[i] == -1) node[i] = cntnode++;
			for (int e = 0; e < m; e++) {
				int v = edge[e].v;
				edge[e].u = node[edge[e].u];
				edge[e].v = node[edge[e].v];
				if (edge[e].u != edge[e].v) edge[e].cost = Cost(edge[e].cost.pos, best[v]);
			}
			n = cntnode;
			root = node[root];
		}
		return res;
	}
	vector<int> trace() {
		vector<int> res;
		for (int i = costlist.size() - 1; i >= 0; i--) costlist[i].push();
		for (int i = 0; i < costlist.size(); i++) {
			Cost cost = costlist[i];
			if (cost.id != -1 && cost.used > 0) res.push_back(cost.id);
		}
		return res;
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	Chuliu::init(4);
	Chuliu::add(1, 0, 1, 2);
	Chuliu::add(1, 1, 2, 8);
	Chuliu::add(1, 0, 2, 5);
	Chuliu::add(1, 2, 3, 1);
	printf("%d", Chuliu::mst(0));
	return 0;
}
