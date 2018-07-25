#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(NlogN)
* Problems:
* 1. http://codeforces.com/problemset/problem/757/F
*/
struct DominatorTree {
    static const int maxn = 1e5 + 5;
    int n, rt;
    vector<int> adj1[maxn];
    vector<int> adj2[maxn];
    vector<int> tree[maxn];
    vector<int> bucket[maxn];
    int par[maxn];
    int sdm[maxn];
    int dom[maxn];
    int dsu[maxn];
    int lbl[maxn];
    int arr[maxn];
    int rev[maxn];
    int tms;

    void init(int n, int rt) {
        this->n = n;
        this->rt = rt;
        for (int i = 0; i < n; i++) {
            adj1[i].clear();
            adj2[i].clear();
            tree[i].clear();
            bucket[i].clear();
        }
        fill_n(arr, n, -1);
        tms = 0;
    }
    void add(int u, int v) {
        adj1[u].push_back(v);
    }
    void dfs(int u) {
        arr[u] = tms, rev[tms] = u;
        lbl[tms] = tms, sdm[tms] = tms, dsu[tms] = tms;
        tms++;
        for (int i = 0; i < (int) adj1[u].size(); i++) {
            int w = adj1[u][i];
            if (!~arr[w]) dfs(w), par[arr[w]] = arr[u];
            adj2[arr[w]].push_back(arr[u]);
        }
    }
    int find(int u, int x = 0) {
        if (u == dsu[u]) return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if (v < 0) return u;
        if (sdm[lbl[dsu[u]]] < sdm[lbl[u]]) {
            lbl[u] = lbl[dsu[u]];
        }
        dsu[u] = v;
        return x ? v : lbl[u];
    }
    void join(int u, int v) {
        dsu[v] = u;
    }
    void build() {
        dfs(rt);
        for (int i = tms - 1; i >= 0; i--) {
            for (int j = 0; j < (int) adj2[i].size(); j++) {
                sdm[i] = min(sdm[i], sdm[find(adj2[i][j])]);
            }
            if (i > 1) bucket[sdm[i]].push_back(i);
            for (int j = 0; j < (int) bucket[i].size(); j++) {
                int w = bucket[i][j], v = find(w);
                if (sdm[v] == sdm[w]) dom[w] = sdm[w];
                else dom[w] = v;
            }
            if (i > 0) join(par[i], i);
        }
        for (int i = 1; i < tms; i++) {
            if (dom[i] != sdm[i]) dom[i] = dom[dom[i]];
            tree[rev[i]].push_back(rev[dom[i]]);
            tree[rev[dom[i]]].push_back(rev[i]);
        }
    }
} domtree;

int main() {
    return 0;
}
