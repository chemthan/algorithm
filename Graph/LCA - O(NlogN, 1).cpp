#include <bits/stdc++.h>
using namespace std;

struct LCA {
    vector<int> events;
    vector<int> sta;
    vector<int> tin;
    vector<int> idx;
    int tms;
    vector<vector<int>> f;
    vector<int> mlg;

    void dfs(int u, int p, const vector<vector<int>>& adj) {
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
        int l = u == v ? 0 : mlg[v - u];
        return min(f[l][u], f[l][v - (1 << l) + 1]);
    }
    int lca(int u, int v) {
        if (sta[u] > sta[v]) swap(u, v);
        return idx[query(sta[u], sta[v])];
    }
    void build(const vector<vector<int>>& adj) {
        events.clear();
        sta.resize(adj.size());
        tin.resize(adj.size());
        idx.resize(adj.size());
        dfs(tms = 0, -1, adj);
        int logn = __lg(adj.size()) + 1;
        f.resize(logn);
        for (int i = 0; i < logn; i++) {
            f[i].resize(events.size());
        }
        for (int i = 0; i < events.size(); i++) {
            f[0][i] = events[i];
        }
        for (int i = 1; i < logn; i++) {
            for (int j = 0; j + (1 << i - 1) < events.size(); j++) {
                f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
            }
        }
        mlg.resize(events.size());
        for (int i = 1; i < mlg.size(); i++) {
            mlg[i] = __lg(i);
        }
    }
};

int main() {
    return 0;
}
