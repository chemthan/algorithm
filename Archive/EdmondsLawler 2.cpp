#include <bits/stdc++.h>
using namespace std;

// O(|E| * |V| ^ 1/2)
// index from 1
struct EdmondsLawler {
  static const int MAXV = 1000 + 10;
  static const int MAXE = 1000000 + 10;
  int n, E, start, finish, newRoot, qsize, adj[MAXE], next[MAXE], last[MAXV],
      mat[MAXV], que[MAXV], dad[MAXV], root[MAXV];
  bool inque[MAXV], inpath[MAXV], inblossom[MAXV];
  void init(int _n) {
    n = _n;
    E = 0;
    for (int x = 1; x <= n; x++) {
      last[x] = -1;
      mat[x] = 0;
    }
  }
  void add(int u, int v) {
    adj[E] = v;
    next[E] = last[u];
    last[u] = E++;
  }
  int lca(int u, int v) {
    for (int x = 1; x <= n; x++)
      inpath[x] = false;
    while (true) {
      u = root[u];
      inpath[u] = true;
      if (u == start)
        break;
      u = dad[mat[u]];
    }
    while (true) {
      v = root[v];
      if (inpath[v])
        break;
      v = dad[mat[v]];
    }
    return v;
  }
  void trace(int u) {
    while (root[u] != newRoot) {
      int v = mat[u];
      inblossom[root[u]] = true;
      inblossom[root[v]] = true;
      u = dad[v];
      if (root[u] != newRoot)
        dad[u] = v;
    }
  }
  void blossom(int u, int v) {
    for (int x = 1; x <= n; x++)
      inblossom[x] = false;
    newRoot = lca(u, v);
    trace(u);
    trace(v);
    if (root[u] != newRoot)
      dad[u] = v;
    if (root[v] != newRoot)
      dad[v] = u;
    for (int x = 1; x <= n; x++)
      if (inblossom[root[x]]) {
        root[x] = newRoot;
        if (!inque[x]) {
          inque[x] = true;
          que[qsize++] = x;
        }
      }
  }
  bool bfs() {
    for (int x = 1; x <= n; x++) {
      inque[x] = false;
      dad[x] = 0;
      root[x] = x;
    }
    qsize = 0;
    que[qsize++] = start;
    inque[start] = true;
    finish = 0;
    for (int i = 0; i < qsize; i++) {
      int u = que[i];
      for (int e = last[u]; e != -1; e = next[e]) {
        int v = adj[e];
        if (root[v] != root[u] && v != mat[u]) {
          if (v == start || (mat[v] > 0 && dad[mat[v]] > 0))
            blossom(u, v);
          else if (dad[v] == 0) {
            dad[v] = u;
            if (mat[v] > 0)
              que[qsize++] = mat[v];
            else {
              finish = v;
              return true;
            }
          }
        }
      }
    }
    return false;
  }
  void enlarge() {
    int u = finish;
    while (u > 0) {
      int v = dad[u], x = mat[v];
      mat[v] = u;
      mat[u] = v;
      u = x;
    }
  }
  int maxmat() {
    for (int x = 1; x <= n; x++)
      if (mat[x] == 0) {
        start = x;
        if (bfs())
          enlarge();
      }
    int ret = 0;
    for (int x = 1; x <= n; x++)
      if (mat[x] > x)
        ++ret;
    return ret;
  }
} edmonds;

int main() {
  edmonds.init(3);
  edmonds.add(1, 2);
  edmonds.add(2, 1);
  edmonds.add(1, 3);
  edmonds.add(3, 1);
  cout << edmonds.maxmat() << "\n";
  return 0;
}
