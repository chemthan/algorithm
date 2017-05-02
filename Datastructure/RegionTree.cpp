#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(NlogN)
*/
struct RegionTree {
    static const int maxn = 1e5 + 5;
    int n;
    vector<int> adj[maxn]; //diagonals and edges
    int cnt; //number of regions
    map<pair<int, int>, int> hs; //hs[a, b] index of region below diagonal (a, b)
    vector<pair<int, int> > g[maxn]; //edges of a region
    vector<int> tree[maxn]; //region tree
    
    static int ix;
    static int compare(int x, int y) {
        if (x > ix && y < ix) return 0;
        if (x < ix && y > ix) return 1;
        return x > y;
    }
    
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            tree[i].clear();
        }
        cnt = 0;
        hs.clear();
        for (int i = 0; i < n; i++) {
            g[i].clear();
        }
    }
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void build() {
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            ix = i;
            sort(adj[i].begin(), adj[i].end(), compare);
        }
        for (int u = n - 1; u >= 0; u--) {
            for (int i = 0; i < (int) adj[u].size() - 1; i++) {
                int v = adj[u][i + 1];
                int w = adj[u][i];
                if (!hs.count(make_pair(u, v))) {
                    hs[make_pair(u, v)] = cnt;
                    g[cnt].push_back(make_pair(u, v));
                    cnt++;
                }
                int ix = hs[make_pair(u, v)];
                if (!hs.count(make_pair(w, u))) {
                    g[ix].push_back(make_pair(w, u));
                }
                hs[make_pair(w, u)] = ix;
            }
        }
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < (int) g[i].size(); j++) {
                pair<int, int> p = g[i][j];
                swap(p.first, p.second);
                if (hs.count(p)) {
                    tree[i].push_back(hs[p]);
                }
            }
        }
    }
} rt;

int main() {
    return 0;
}
