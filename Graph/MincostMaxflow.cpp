#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(min(E^2 * V * logV, E * logV * Flow))
*/
#define MCMF MincostMaxflow
#define flow_t int
#define cost_t int
const flow_t foo = (flow_t) 1e9;
const cost_t coo = (cost_t) 1e9;
namespace MincostMaxflow {
    const int maxv = 1e5 + 5;
    const int maxe = 1e6 + 5;
    int n, s, t, E;
    int adj[maxe], nxt[maxe], lst[maxv], frm[maxv];
    flow_t cap[maxe], flw[maxe], totalFlow;
    cost_t cst[maxe], pot[maxe], dst[maxv], totalCost;

    void init(int nn, int ss, int tt) {
        n = nn, s = ss, t = tt;
        fill_n(lst, n, -1), E = 0;
    }
    void add(int u, int v, flow_t ca, cost_t co) {
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
        priority_queue<pair<cost_t, int> > que;
        fill_n(dst, n, coo), dst[s] = 0;
        que.push(make_pair(-dst[s], s));
        while (que.size()) {
            cost_t dnow = -que.top().first;
            int u = que.top().second;
            que.pop();
            if (dst[u] < dnow) continue;
            for (int e = lst[u]; e != -1; e = nxt[e]) if (flw[e] < cap[e]) {
                int v = adj[e];
                cost_t dnxt = dnow + cst[e] + pot[u] - pot[v];
                if (dst[v] > dnxt) {
                    dst[v] = dnxt;
                    frm[v] = e;
                    que.push(make_pair(-dnxt, v));
                }
            }
        }
        return dst[t] < coo;
    }
    cost_t mincost() {
        totalCost = 0, totalFlow = 0;
        bellman();
        while (1) {
            if (!dijkstra()) break;
            flow_t mn = foo;
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
}

int main() {
    MCMF::init(3, 0, 2);
    MCMF::add(0, 1, 1, 3);
    MCMF::add(1, 2, 1, 10);
    MCMF::add(0, 2, 1, 100);
    assert(MCMF::mincost() == 113);
    cerr << "Correct!\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
