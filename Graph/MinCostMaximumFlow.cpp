#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(min(E^2 * V * logV, E * logV * Flow))
*/
template<class TF, class TC, TF Foo, TC Coo> struct MinCostMaximumFlow {
    static const int MAXV = 1e5 + 5;
    static const int MAXE = 1e6 + 5;
    int n, s, t, E;
    int adj[MAXE], nxt[MAXE], lst[MAXV], frm[MAXV];
    TF cap[MAXE], flw[MAXE], totalFlow;
    TC cst[MAXE], pot[MAXE], dst[MAXV], totalCost;
    void init(int n, int s, int t) {
        this->n = n, this->s = s, this->t = t;
        fill_n(lst, n, -1), E = 0;
    }
    void add(int u, int v, TF ca, TC co) {
        adj[E] = v, cap[E] = ca, flw[E] = 0, cst[E] = +co, nxt[E] = lst[u], lst[u] = E++;
        adj[E] = u, cap[E] =  0, flw[E] = 0, cst[E] = -co, nxt[E] = lst[v], lst[v] = E++;
    }
    void bellman() {
        fill_n(pot, n, 0);
        while (1) {
            int found = 0;
            for (int u = 0; u < n; u++) for (int e = lst[u]; e != -1; e = nxt[e]) if (flw[e] < cap[e]) {
                int v = adj[e];
                if (pot[v] > pot[u] + cst[e]) {
                    pot[v] = pot[u] + cst[e];
                    found = 1;
                }
            }
            if (!found) break;
        }
    }
    int dijkstra() {
        priority_queue<pair<TC, int> > que;
        fill_n(dst, n, Coo), dst[s] = 0;
        que.push(make_pair(-dst[s], s));
        while (que.size()) {
            TC dnow = -que.top().first;
            int u = que.top().second;
            que.pop();
            if (dst[u] < dnow) continue;
            for (int e = lst[u]; e != -1; e = nxt[e]) if (flw[e] < cap[e]) {
                int v = adj[e];
                TC dnxt = dnow + cst[e] + pot[u] - pot[v];
                if (dst[v] > dnxt) {
                    dst[v] = dnxt;
                    frm[v] = e;
                    que.push(make_pair(-dnxt, v));
                }
            }
        }
        return dst[t] < Coo;
    }
    TC mincost() {
        totalCost = 0, totalFlow = 0;
        bellman();
        while (1) {
            if (!dijkstra()) break;
            TF mn = Foo;
            for (int v = t, e = frm[v]; v != s; v = adj[e ^ 1], e = frm[v]) mn = min(mn, cap[e] - flw[e]);
            for (int v = t, e = frm[v]; v != s; v = adj[e ^ 1], e = frm[v]) {
                flw[e] += mn;
                flw[e ^ 1] -= mn;
            }
            totalFlow += mn;
            totalCost += mn * (dst[t] - pot[s] + pot[t]);
            for (int u = 0; u < n; u++) pot[u] += dst[u];
        }
        return totalCost;
    }
};
MinCostMaximumFlow<int, int, (int) 1e9, (int) 1e9> mcmf;

int main() {
    mcmf.init(3, 0, 2);
    mcmf.add(0, 1, 1, 3);
    mcmf.add(1, 2, 1, 10);
    mcmf.add(0, 2, 1, 100);
    cout << mcmf.mincost() << "\n";
    return 0;
}
