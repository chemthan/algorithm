#include <bits/stdc++.h>
using namespace std;

namespace BCC {
int timer;
vector<int> num;
vector<int> low;
vector<int> art;
vector<pair<int, int>> bridges;
vector<vector<int>> comps;
vector<int> stk;

void _dfs(const vector<vector<int>> &adj, int u, int p = -1) {
  num[u] = low[u] = ++timer;
  stk.push_back(u);
  for (int v : adj[u]) {
    if (!num[v]) {
      _dfs(adj, v, u);
      if (low[v] > num[u]) {
        bridges.push_back({u, v});
      }
      low[u] = min(low[u], low[v]);
      if (low[v] >= num[u]) {
        art[u] = num[u] > 1 || num[v] > 2;
        vector<int> comp = {u};
        comps.push_back(comp);
        while (comps.back().back() != v) {
          comps.back().push_back(stk.back()), stk.pop_back();
        }
      }
    } else if (v != p) {
      low[u] = min(low[u], num[v]);
    }
  }
}

tuple<vector<vector<int>>, vector<int>, vector<pair<int, int>>>
build(const vector<vector<int>> &adj, int rt = 0) {
  int n = adj.size();
  timer = 0;
  num = vector<int>(n);
  low = vector<int>(n);
  art = vector<int>(n);
  bridges.clear();
  comps.clear();
  stk.clear();
  _dfs(adj, rt);
  return {comps, art, bridges};
}
} // namespace BCC

int main() {
  int n = 10;
  vector<vector<int>> adj(n);
  for (auto [u, v] :
       {make_pair(1, 2), make_pair(2, 3), make_pair(3, 4), make_pair(4, 5),
        make_pair(5, 3), make_pair(2, 7), make_pair(7, 9), make_pair(9, 10),
        make_pair(10, 6), make_pair(6, 7), make_pair(1, 8)}) {
    u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  auto [comps, art, bridges] = BCC::build(adj);
  vector<int> lb(n);
  vector<pair<int, int>> new_edges;
  {
    int ptr = 0;
    for (int u = 0; u < n; u++) {
      if (art[u]) {
        lb[u] = ptr++;
      }
    }
    for (auto comp : comps) {
      for (int u : comp) {
        if (!art[u]) {
          lb[u] = ptr;
        } else {
          new_edges.push_back({ptr, lb[u]});
        }
      }
      ptr++;
    }
  }
  return 0;
}
