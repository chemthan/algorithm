#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;
const int maxm = 1e6 + 5;
const int oo = (int) 1e9;
int n, ec;
int id[maxn], pre[maxn], in[maxn], vis[maxn];

struct edge_t {
    int u, v, w;
    edge_t(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
} edge[maxm];

void add(int u, int v, int w) {
    edge[++ec] = edge_t(u, v, w);
}
int arborescence(int n, int root) {
    int res = 0, index;
    while (1) {
        for (int i = 1; i <= n; i++) {
            in[i] = oo, vis[i] = -1, id[i] = -1;
        }
        for (int i = 1; i <= ec; i++) {
            int u = edge[i].u, v = edge[i].v;
            if (u == v || in[v] <= edge[i].w) continue;
            in[v] = edge[i].w, pre[v] = u;
        }
        pre[root] = root, in[root] = 0;
        for (int i = 1; i <= n; i++) {
            res += in[i];
            if (in[i] == oo) return -1;
        }

        index = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i] != -1) continue;
            int u = i, v;
            while (vis[u] == -1) {
                vis[u] = i;
                u = pre[u];
            }
            if (vis[u] != i || u == root) continue;
            for (v = u, u = pre[u], index++; u != v; u = pre[u]) id[u] = index;
            id[v] = index;
        }
        if (index == 0) return res;
        for (int i = 1; i <= n; i++) if (id[i] == -1) id[i] = ++index;
        for (int i = 1; i <= ec; i++) {
            int u = edge[i].u, v = edge[i].v;
            edge[i].u = id[u], edge[i].v = id[v];
            edge[i].w -= in[v];
        }
        n = index, root = id[root];
    }
    return res;
}

int main() {
    return 0;
}
