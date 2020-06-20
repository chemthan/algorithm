#include <bits/stdc++.h>
using namespace std;

struct Tree_t {
    vector<int> events;
    vector<int> sta;
    vector<int> lev;
    vector<int> tin;
    vector<int> tou;
    vector<int> idx;
    vector<vector<int>> par;
    int timer;
    vector<vector<int>> f;
    vector<int> mlg;

    void dfs(int u, int p, const vector<vector<int>>& adj) {
        idx[tin[u] = timer++] = u;
        sta[u] = events.size();
        events.push_back(tin[u]);
        for (int i = 1; i < (int) par.size(); i++) {
            par[i][u] = par[i - 1][par[i - 1][u]];
        }
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != p) {
                lev[v] = lev[u] + 1;
                par[0][v] = u;
                dfs(v, u, adj);
                events.push_back(tin[u]);
            }
        }
        tou[u] = timer - 1;
    }
    void build(const vector<vector<int>>& adj, int rt = 0) {
        events.clear();
        sta.resize(adj.size());
        lev.resize(adj.size());
        tin.resize(adj.size());
        tou.resize(adj.size());
        idx.resize(adj.size());
        par.resize(__lg(adj.size()) + 1);
        for (int i = 0; i < (int) par.size(); i++) {
            par[i].resize(adj.size());
            par[i][rt] = rt;
        }
        timer = lev[rt] = 0, dfs(rt, -1, adj);
        int logn = __lg(events.size()) + 1;
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
    int rmq(int u, int v) {
        int l = u == v ? 0 : mlg[v - u];
        return min(f[l][u], f[l][v - (1 << l) + 1]);
    }
    int lca(int u, int v) {
        if (sta[u] > sta[v]) swap(u, v);
        return idx[rmq(sta[u], sta[v])];
    }
    int dist(int u, int v) {
        int a = lca(u, v);
        return lev[u] + lev[v] - lev[a] - lev[a];
    }
    int isanc(int p, int u) {
        return tin[p] <= tin[u] && tou[u] <= tou[p];
    }
    int go_up(int u, int k) {
        for (int i = (int) par.size() - 1; 0 <= i; i--) {
            if ((1 << i) <= k) {
                k -= 1 << i;
                u = par[i][u];
            }
        }
        return u;
    }
    int go_to(int u, int v, int k) {
        int a = lca(u, v);
        if (k <= lev[u] - lev[a]) {
            return go_up(u, k);
        }
        k -= lev[u] - lev[a];
        k = lev[v] - lev[a] - k;
        return go_up(v, k);
    }
};

int main() {
    return 0;
}
