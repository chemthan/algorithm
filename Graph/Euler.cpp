#include <bits/stdc++.h>
using namespace std;

namespace Euler {
    vector<int> find(const vector<pair<int, int>>& edges) {
        vector<vector<pair<int, int>>> adj;
        vector<int> dup;
        for (int i = 0; i < (int) edges.size(); i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            if (u ^ v) {
                for (int j = 0; j < 2; j++) {
                    while ((int) adj.size() <= u) {
                        adj.push_back(vector<pair<int, int>>());
                    }
                    adj[u].push_back(make_pair(v, i));
                    swap(u, v);
                }
            }
            else {
                while ((int) dup.size() <= u) {
                    dup.push_back(0);
                }
                dup[u]++;
            }
        }
        int st = 0;
        for (int u = 0; u < (int) adj.size(); u++) {
            if (adj[u].size() & 1) {
                st = u;
                break;
            }
        }
        vector<int> f(edges.size());
        vector<int> res, stk;
        function<void(int)> dfs = [&] (int u) {
            stk.push_back(u);
            while (u < (int) adj.size() && !adj[u].empty()) {
                int v = adj[u].back().first;
                int e = adj[u].back().second;
                adj[u].pop_back();
                if (!f[e]) {
                    f[e] = 1, dfs(v);
                }
            }
            int v = stk.back();
            stk.pop_back();
            res.push_back(v);
            while (v < (int) dup.size() && dup[v]) {
                res.push_back(v);
                dup[v]--;
            }
        };
        dfs(st);
        return res;
    }
};

int main() {
    vector<pair<int, int>> edges;
    edges.push_back(make_pair(0, 1));
    edges.push_back(make_pair(1, 2));
    edges.push_back(make_pair(2, 0));
    edges.push_back(make_pair(2, 2));
    vector<int> res = Euler::find(edges);
    for (int i = 0; i < (int) res.size(); i++) {
        cout << res[i] << " \n"[i == (int) res.size() - 1];
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
