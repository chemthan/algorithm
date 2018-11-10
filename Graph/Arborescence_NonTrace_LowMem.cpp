#include <bits/stdc++.h>
using namespace std;

#define ABS Arborescence
#define num_t int
#define INDEX0
namespace Arborescence {
    const int maxv = 1e3 + 5;
    const int maxe = 1e6 + 5;
    const num_t oo = (num_t) 1e9;

    struct edge_t {
        int u, v;
        num_t w;
        edge_t(int u = 0, int v = 0, num_t w = 0) : u(u), v(v), w(w) {}
    } edge[maxe];

    int ec;
    int id[maxv], pre[maxv], in[maxv], vis[maxv];

    void init() {
        ec = 0;
    }

    void add(int u, int v, int w) {
#ifdef INDEX0
        u++, v++;
#endif
        edge[++ec] = edge_t(u, v, w);
    }
    num_t mst(int n, int rt) {
#ifdef INDEX0
        rt++;
#endif
        num_t res = 0;
        int idx;
        while (1) {
            for (int i = 1; i <= n; i++) {
                in[i] = oo, vis[i] = -1, id[i] = -1;
            }
            for (int i = 1; i <= ec; i++) {
                int u = edge[i].u, v = edge[i].v;
                if (u == v || in[v] <= edge[i].w) continue;
                in[v] = edge[i].w, pre[v] = u;
            }
            pre[rt] = rt, in[rt] = 0;
            for (int i = 1; i <= n; i++) {
                res += in[i];
                if (in[i] == oo) return -1;
            }

            idx = 0;
            for (int i = 1; i <= n; i++) {
                if (vis[i] != -1) continue;
                int u = i, v;
                while (vis[u] == -1) {
                    vis[u] = i;
                    u = pre[u];
                }
                if (vis[u] != i || u == rt) continue;
                for (v = u, u = pre[u], idx++; u != v; u = pre[u]) id[u] = idx;
                id[v] = idx;
            }
            if (idx == 0) return res;
            for (int i = 1; i <= n; i++) if (id[i] == -1) id[i] = ++idx;
            for (int i = 1; i <= ec; i++) {
                int u = edge[i].u, v = edge[i].v;
                edge[i].u = id[u], edge[i].v = id[v];
                edge[i].w -= in[v];
            }
            n = idx, rt = id[rt];
        }
        return res;
    }
}

int main() {
    ABS::init();
    ABS::add(0, 1, 2);
    ABS::add(1, 2, 8);
    ABS::add(0, 2, 5);
    ABS::add(2, 3, 1);
    cout << ABS::mst(4, 0) << "\n"; //expected 8
    return 0;
}
