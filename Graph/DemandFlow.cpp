#include <bits/stdc++.h>
using namespace std;

#define DF Demandflow
#define flow_t int
const flow_t foo = (flow_t)1e9;
namespace Demandflow {
const int maxv = 1e5 + 5;
const int maxe = 1e6 + 5;
int n, s, t, E;
int adj[maxe], nxt[maxe], lst[maxv], ptr[maxv], lev[maxv], que[maxv];
flow_t flw[maxe], cap[maxe];
flow_t incoming[maxe], outcoming[maxe];
void add(int u, int v, flow_t c1, flow_t c2) {
  adj[E] = v, flw[E] = 0, cap[E] = c1, nxt[E] = lst[u], lst[u] = E++;
  adj[E] = u, flw[E] = 0, cap[E] = c2, nxt[E] = lst[v], lst[v] = E++;
}
void init(int nn, int ss, int tt, int lim) {
  n = nn, E = 0;
  s = n++, t = n++;
  fill_n(lst, n, -1);
  fill_n(incoming, n, 0), fill_n(outcoming, n, 0);
  add(tt, ss, lim, 0);
}
void add_demand(int u, int v, flow_t demand, flow_t cap) {
  incoming[v] += demand;
  outcoming[u] += demand;
  add(u, v, cap - demand, 0);
}
int bfs() {
  fill_n(lev, n, 0), lev[s] = 1;
  int qsize = 0;
  que[qsize++] = s;
  for (int i = 0; i < qsize; i++) {
    for (int u = que[i], e = lst[u]; ~e; e = nxt[e]) {
      int v = adj[e];
      if (flw[e] < cap[e] && !lev[v]) {
        lev[v] = lev[u] + 1;
        que[qsize++] = v;
      }
    }
  }
  return lev[t];
}
flow_t dfs(int u, flow_t bot) {
  if (u == t)
    return bot;
  for (int &e = ptr[u]; ~e; e = nxt[e]) {
    int v = adj[e];
    flow_t delta = 0;
    if (lev[v] == lev[u] + 1 && flw[e] < cap[e] &&
        (delta = dfs(v, min(bot, cap[e] - flw[e]))) > 0) {
      flw[e] += delta;
      flw[e ^ 1] -= delta;
      return delta;
    }
  }
  return 0;
}
bool check() {
  int sum_in = 0;
  for (int u = 0; u < n - 2; u++) {
    add(s, u, incoming[u], 0);
    add(u, t, outcoming[u], 0);
    sum_in += incoming[u];
  }
  fill_n(flw, E, 0);
  flow_t total = 0;
  while (bfs()) {
    for (int i = 0; i < n; i++)
      ptr[i] = lst[i];
    for (flow_t delta = dfs(s, foo); delta > 0; delta = dfs(s, foo))
      total += delta;
  }
  return total == sum_in;
}
} // namespace Demandflow

int main() {
  DF::init(3, 0, 2, 1000);
  DF::add_demand(0, 1, 1, 2);
  DF::add_demand(0, 1, 1, 2);
  DF::add_demand(1, 2, 2, 2);
  assert(DF::check());
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}
