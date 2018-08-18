#include <bits/stdc++.h>
using namespace std;

namespace LCA {
    const int maxn = 1e5 + 5;
    const int logn = 20;
    vector<int> events;
    int sta[maxn];
    int tin[maxn];
    int idx[maxn];
    int tms;
    int f[logn][maxn << 1];
    int lg[maxn];

    void dfs(int u, int p, vector<int> adj[]) {
        idx[tin[u] = tms++] = u;
        sta[u] = events.size();
        events.push_back(tin[u]);
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != p) {
                dfs(v, u, adj);
                events.push_back(tin[u]);
            }
        }
    }
    int query(int u, int v) {
        int l = u == v ? 0 : lg[v - u];
        return min(f[l][u], f[l][v - (1 << l) + 1]);
    }
    int lca(int u, int v) {
        if (sta[u] > sta[v]) swap(u, v);
        return idx[query(sta[u], sta[v])];
    }
    void build(vector<int> adj[]) {
        events.clear();
        dfs(tms = 0, -1, adj);
        for (int i = 0; i < events.size(); i++) {
            f[0][i] = events[i];
        }
        for (int i = 1; i < logn; i++) {
            for (int j = 0; j + (1 << i - 1) < events.size(); j++) {
                f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
            }
        }
        for (int i = 1; i < maxn; i++) {
            lg[i] = __lg(i);
        }
    }
}

int main() {
    return 0;
}
