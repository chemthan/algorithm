#include <bits/stdc++.h>
using namespace std;

/*
 * Comlexity: O(NlogN)
 */
namespace TCD {
    vector<int> rem;
    vector<int> size;

    void dfs(const vector<vector<int>>& adj, int u, int p) {
        size[u] = 1;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != p && !rem[v]) {
                dfs(adj, v, u);
                size[u] += size[v];
            }
        }
    }
    int findcentroid(const vector<vector<int>>& adj, int u) {
        int p = -1;
        dfs(adj, u, -1);
        int cap = size[u] >> 1;
        while (1) {
            int found = 0;
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i];
                if (v != p && !rem[v] && cap < size[v]) {
                    p = u, u = v;
                    found = 1;
                    break;
                }
            }
            if (!found) return u;
        }
        assert(0);
    }
    void workspace(const vector<vector<int>>&, int);
    void divide(const vector<vector<int>>& adj, int u = 0, int depth = 0) {
        if (!depth) {
            rem.resize(adj.size());
            fill(rem.begin(), rem.end(), 0);
            size.resize(adj.size());
        }
        u = findcentroid(adj, u);
        rem[u] = 1, workspace(adj, u);
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!rem[v]) {
                divide(adj, v, depth + 1);
            }
        }
    }
    void workspace(const vector<vector<int>>& adj, int u) {
    }
}

int main() {
    return 0;
}
