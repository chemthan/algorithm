#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(NlogN)
*/
const int MAXN = 1e5 + 5;
int n;
vector<int> adj[MAXN];
int size[MAXN];
int lev[MAXN];
vector<int>* f[MAXN];
int cnt[MAXN];

void firstdfs(int u, int p) {
    size[u] = 1;
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != p) {
            lev[v] = lev[u] + 1;
            firstdfs(v, u);
            size[u] += size[v];
        }
    }
}

inline void add(int val) {
    cnt[val]++;
}

inline void rem(int val) {
    cnt[val]--;
}

void dfs(int u, int p, int keep) {
    pair<int, int> best;
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != p) {
            best = max(best, make_pair(size[v], v));
        }
    }
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != p && v != best.second) {
            dfs(v, u, 0);
        }
    }
    if (best.first) {
        dfs(best.second, u, 1);
        f[u] = f[best.second];
    }
    else {
        f[u] = new vector<int>;
    }
    //Getting answer from u
    f[u]->push_back(lev[u]);
    add(lev[u]);
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != p && v != best.second) {
            for (int j = 0; j < (int) f[v]->size(); j++) {
                int val = (*f[v])[j];
                //Getting answer from v
            }
            for (int j = 0; j < (int) f[v]->size(); j++) {
                int val = (*f[v])[j];
                f[u]->push_back(val);
                add(val);
            }
        }
    }
    if (!keep) {
        for (int i = 0; i < (int) f[u]->size(); i++) {
            int val = (*f[u])[i];
            rem(val);
        }
    }
}

int main() {
    return 0;
}
