#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int n;
vector<int> adj[MAXN];
int num[MAXN];
int low[MAXN];
int tms;
int root, nchild;

void dfs(int u, int p = -1) {
    num[u] = low[u] = ++tms;
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i];
        if (!num[v]) {
            if (u == root) nchild++;
            dfs(v, u);
            if (low[v] >= num[u]) {
                //u is an articulation point
            }
            if (low[v] > num[u]) {
                //u -> v is a bridge
            }
            low[u] = min(low[u], low[v]);
        }
        else if (v != p) {
            low[u] = min(low[u], num[v]);
        }
    }
}

int main() {
    dfs(root = 0);
    if (nchild > 1) {
        //root is an articulation point
    }
    return 0;
}
