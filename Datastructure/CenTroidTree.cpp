#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(NlogN)
*/
struct CentroidTree {
    struct Info {
        int d;
        Info() : d(0) {}
        Info(int d) : d(d) {}
        Info(const Info& rhs) : d(rhs.d) {}
        Info operator + (const int& w) const {
            return Info(d + w);
        }
        Info operator + (const Info& rhs) const {
            return Info(d + rhs.d);
        }
    };
    
    static const int maxn = 1e5 + 5;
    static const int logn = 20;
    int n;
    vector<int> adj[maxn];
    int size[maxn];
    int del[maxn];
    vector<int> tree[maxn];
    int lev[maxn];
    int p[logn][maxn];
    Info info[logn][maxn];
    
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            tree[i].clear();
            del[i] = 0;
        }
    }
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int u, int p) {
        size[u] = 1;
        for (int i = 0; i < (int) adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != p && !del[v]) {
                dfs(v, u);
                size[u] += size[v];
            }
        }
    }
    int findcentroid(int u) {
        dfs(u, -1);
        int p = -1, t = size[u];
        while (1) {
            pair<int, int> best;
            for (int i = 0; i < (int) adj[u].size(); i++) {
                int v = adj[u][i];
                if (v != p && !del[v]) {
                    best = max(best, make_pair(size[v], v));
                }
            }
            if (best.first + best.first <= t) {
                return u;
            }
            p = u, u = best.second;
        }
    }
    void upd(int u, int dep, int p) {
        for (int i = 0; i < (int) adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != p && !del[v]) {
                info[dep][v] = info[dep][u] + 1;
                upd(v, dep, u);
            }
        }
    }
    int divide(int u, int dep) {
        lev[u = findcentroid(u)] = dep;
        p[0][u] = u;
        info[dep][u] = Info(0);
        upd(u, dep, -1);
        del[u] = 1;
        for (int i = 0; i < (int) adj[u].size(); i++) {
            int v = adj[u][i];
            if (!del[v]) {
                int w = divide(v, dep + 1);
                tree[u].push_back(w);
                p[0][w] = u;
            }
        }
        return u;
    }
    int lca(int u, int v) {
        if (lev[u] < lev[v]) swap(u, v);
        for (int k = logn - 1; k >= 0; k--) {
            if (lev[p[k][u]] >= lev[v]) {
                u = p[k][u];
            }
        }
        if (u == v) return u;
        for (int k = logn - 1; k >= 0; k--) {
            if (p[k][u] != p[k][v]) {
                u = p[k][u], v = p[k][v];
            }
        }
        return p[0][u];
    }
    Info getInfo(int u, int v) {
        int a = lca(u, v);
        int ix = lev[a];
        return info[ix][u] + info[ix][v];
    }
    void build() {
        divide(0, 0);
        for (int k = 1; k < logn; k++) {
            for (int u = 0; u < n; u++) {
                p[k][u] = p[k - 1][p[k - 1][u]];
            }
        }
    }
} ct;

int main() {
    return 0;
}
