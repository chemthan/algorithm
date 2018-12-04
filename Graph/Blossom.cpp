#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(E*sqrt(V))
 * Indexing from 1
 */

#define BS Blossom
namespace Blossom {
    const int maxv = 1e3 + 5;
    const int maxe = 1e6 + 5;
    int n, E, lst[maxv], next[maxe], adj[maxe];
    int nxt[maxv], mat[maxv], dad[maxv], col[maxv];
    int que[maxv], qh, qt;
    int vis[maxv], act[maxv];
    int tag, total;

    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; i++) {
            lst[i] = nxt[i] = mat[i] = vis[i] = 0;
        }
        E = 1, tag = total = 0;
    }
    void add(int u,int v) {
        if (!mat[u] && !mat[v]) mat[u] = v, mat[v] = u, total++;
        E++, adj[E] = v, next[E] = lst[u], lst[u] = E;
        E++, adj[E] = u, next[E] = lst[v], lst[v] = E;
    }
    int lca(int u, int v) {
        tag++;
        for(; ; swap(u, v)) {
            if (u) {
                if (vis[u = dad[u]] == tag) {
                    return u;
                }
                vis[u] = tag;
                u = nxt[mat[u]];
            }
        }
    }
    void blossom(int u, int v, int g) {
        while (dad[u] != g) {
            nxt[u] = v;
            if (col[mat[u]] == 2) {
                col[mat[u]] = 1;
                que[++qt] = mat[u];
            }
            if (u == dad[u]) dad[u] = g;
            if (mat[u] == dad[mat[u]]) dad[mat[u]] = g;
            v = mat[u];
            u = nxt[v];
        }
    }
    int augument(int s) {
        for (int i = 1; i <= n; i++) {
            col[i] = 0;
            dad[i] = i;
        }
        qh = 0; que[qt = 1] = s; col[s] = 1;
        for (int u, v, i; qh < qt; ) {
            act[u = que[++qh]] = 1;
            for (i = lst[u];i ; i = next[i]) {
                v = adj[i];
                if (col[v] == 0) {
                    nxt[v] = u;
                    col[v] = 2;
                    if (!mat[v]) {
                        for (; v; v = u) {
                            u = mat[nxt[v]];
                            mat[v] = nxt[v];
                            mat[nxt[v]] = v;
                        }
                        return 1;
                    }
                    col[mat[v]] = 1;
                    que[++qt] = mat[v];
                }
                else if (dad[u] != dad[v] && col[v] == 1) {
                    int g = lca(u, v);
                    blossom(u, v, g);
                    blossom(v, u, g);
                    for (int j = 1; j <= n; j++) {
                        dad[j] = dad[dad[j]];
                    }
                }
            }
        }
        return 0;
    }
    int maxmat() {
        for (int i = 1; i <= n; i++) {
            if (!mat[i]) {
                total += augument(i);
            }
        }
        return total;
    }
}

int main() {
    BS::init(3);
    BS::add(1, 2);
    BS::add(1, 3);
    BS::maxmat();
    for (int i = 1; i <= BS::n; i++) {
        BS::act[i] = 0;
    }
    BS::maxmat();
    //BS::act[i] = 1 iff the number of matching doesn't change if remove vertex i
    for (int i = 1; i <= BS::n; i++) {
        cout << i << " " << BS::act[i] << "\n";
    }
    return 0;
}
