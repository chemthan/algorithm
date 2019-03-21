#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(E * sqrt(V))
 */
#define HK HopcroftKarp
namespace HopcroftKarp {
    const int maxv = 1e3 + 5;
    const int maxe = 1e6 + 5;
    int nx, ny, E, nmatches;
    int adj[maxe], nxt[maxe];
    int lst[maxv], ptr[maxv], lev[maxv], que[maxv], matx[maxv], maty[maxv];
    void init(int _nx, int _ny) {
        nx = _nx, ny = _ny;
        E = nmatches = 0, fill_n(lst, nx, -1);
        fill_n(matx, nx, -1), fill_n(maty, ny, -1);
    }
    void add(int x, int y) {
        adj[E] = y, nxt[E] = lst[x], lst[x] = E++;
    }
    int bfs() {
        int qh = 0, qe = 0;
        for (int x = 0; x < nx; x++) {
            if (~matx[x]) {
                lev[x] = 0;
            }
            else {
                lev[x] = 1;
                que[qe++] = x;
            }
        }
        int res = 0;
        while (qh < qe) {
            int x = que[qh++];
            for (int e = lst[x]; ~e; e = nxt[e]) {
                int y = adj[e];
                if (!~maty[y]) {
                    res = 1;
                }
                else if (!lev[maty[y]]) {
                    lev[maty[y]] = lev[x] + 1;
                    que[qe++] = maty[y];
                }
            }
        }
        return res;
    }
    int dfs(int x) {
        for (int& e = ptr[x]; ~e; e = nxt[e]) {
            int y = adj[e];
            if (!~maty[y] || (lev[maty[y]] == lev[x] + 1 && dfs(maty[y]))) {
                matx[x] = y;
                maty[y] = x;
                return 1;
            }
        }
        return 0;
    }
    int maxmat() {
        while (bfs()) {
            for (int x = 0; x < nx; x++) {
                ptr[x] = lst[x];
            }
            for (int x = 0; x < nx; x++) {
                if (!~matx[x]) {
                    nmatches += dfs(x);
                }
            }
        }
        return nmatches;
    }
    int vis[2][maxv];
    void dfs(int u, int r) {
        vis[r][u] = 1;
        if (!r) {
            for (int e = lst[u]; ~e; e = nxt[e]) {
                int v = adj[e];
                if (matx[u] != v && !vis[!r][v]) {
                    dfs(v, !r);
                }
            }
        }
        else {
            int v = maty[u];
            if (~v && !vis[!r][v]) {
                dfs(v, !r);
            }
        }
    }
    vector<int> mincover() {
        maxmat();
        vector<int> res;
        fill_n(vis[0], nx, 0), fill_n(vis[1], ny, 0);
        for (int x = 0; x < nx; x++) {
            if (!~matx[x] && !vis[0][x]) {
                dfs(x, 0);
            }
        }
        for (int x = 0; x < nx; x++) {
            if (!vis[0][x]) {
                res.push_back(x);
            }
        }
        for (int y = 0; y < ny; y++) {
            if (vis[1][y]) {
                res.push_back(nx + y);
            }
        }
        return res;
    }
    vector<int> maxind() {
        maxmat();
        vector<int> res;
        fill_n(vis[0], nx, 0), fill_n(vis[1], ny, 0);
        for (int x = 0; x < nx; x++) {
            if (!~matx[x] && !vis[0][x]) {
                dfs(x, 0);
            }
        }
        for (int x = 0; x < nx; x++) {
            if (vis[0][x]) {
                res.push_back(x);
            }
        }
        for (int y = 0; y < ny; y++) {
            if (!vis[1][y]) {
                res.push_back(nx + y);
            }
        }
        return res;
    }
}

int main() {
    HK::init(3, 3);
    HK::add(0, 1);
    HK::add(0, 2);
    HK::add(1, 2);
    cout << HK::maxmat() << "\n";
    for (int x : HK::mincover()) {
        cout << x << " ";
    }
    cout << "\n";
    for (int x : HK::maxind()) {
        cout << x << " ";
    }
    cout << "\n";
    return 0;
}
