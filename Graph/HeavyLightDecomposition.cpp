#include <bits/stdc++.h>
using namespace std;

namespace HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> size;
    vector<int> lev;
    vector<int> p;
    vector<int> heavy;

    vector<int> num;
    vector<int> head;
    int cnt;

    void firstdfs(int u, int dad) {
        size[u] = 1, heavy[u] = -1;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != dad) {
                p[v] = u, lev[v] = lev[u] + 1;
                firstdfs(v, u);
                size[u] += size[v];
                if (heavy[u] == -1 || size[heavy[u]] < size[v]) {
                    heavy[u] = v;
                }
            }
        }
    }
    void dfs(int u, int h, int p) {
        num[u] = cnt++, head[u] = h;
        if (~heavy[u]) {
            dfs(heavy[u], h, u);
        }
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != p && v != heavy[u]) {
                dfs(v, v, u);
            }
        }
    }
    void build(const vector<vector<int>>& _adj) {
        n = (int) _adj.size();
        adj = _adj;
        size.resize(n);
        lev.resize(n);
        p.resize(n);
        heavy.resize(n);

        num.resize(n);
        head.resize(n);
        cnt = 0;
        firstdfs(0, -1), dfs(0, 0, -1);
    }
    vector<pair<int, int>> getsegs(int u, int v) {
        vector<pair<int, int>> res;
        int hu = head[u], hv = head[v];
        while (hu != hv) {
            if (lev[hu] < lev[hv]) swap(u, v), swap(hu, hv);
            res.push_back(make_pair(num[hu], num[u]));
            u = p[hu], hu = head[u];
        }
        if (lev[u] > lev[v]) swap(u, v);
        //upd(num[u] + 1, num[v]) for edge path
        res.push_back(make_pair(num[u], num[v]));
        return res;
    }
}

int main() {
    return 0;
}
