#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(E*sqrt(V))
* Indexing from 1
*/
struct HopcroftKarp {
    static const int MAXV = 1e3 + 5;
    static const int MAXE = 1e6 + 5;
    int nx, ny, E, adj[MAXE], nxt[MAXE], lst[MAXV], cur[MAXV], lev[MAXV], que[MAXV], matx[MAXV], maty[MAXV];
    void init(int nx, int ny) {
        this->nx = nx, this->ny = ny;
        E = 0, fill_n(lst, nx + 1, -1);
        fill_n(matx, nx + 1, -1), fill_n(maty, ny + 1, -1);
    }
    void add(int x, int y) {
        adj[E] = y, nxt[E] = lst[x], lst[x] = E++;
    }
    int bfs() {
        int qsize = 0;
        for (int x = 1; x <= nx; x++) if (matx[x] != -1) lev[x] = -1;
        else {
            lev[x] = 0;
            que[qsize++] = x;
        }
        int found = 0;
        for (int i = 0; i < qsize; i++) {
            for (int x = que[i], e = lst[x]; e != -1; e = nxt[e]) {
                int y = adj[e];
                if (maty[y] == -1) found = 1;
                else if (lev[maty[y]] == -1) {
                    lev[maty[y]] = lev[x] + 1;
                    que[qsize++] = maty[y];
                }
            }
        }
        return found;
    }
    int dfs(int x) {
        for (int &e = cur[x]; e != -1; e = nxt[e]) {
            int y = adj[e];
            if (maty[y] == -1 || (lev[maty[y]] == lev[x] + 1 && dfs(maty[y]))) {
                matx[x] = y;
                maty[y] = x;
                return 1;
            }
        }
        return 0;
    }
    int maxmat() {
        int res = 0;
        while (bfs()) {
            for (int x = 1; x <= nx; x++) cur[x] = lst[x];
            for (int x = 1; x <= nx; x++) if (matx[x] == -1) res += dfs(x);
        }
        return res;
    }
} hopkarp;

int main() {
    hopkarp.init(3, 3);
    hopkarp.add(1, 2);
    hopkarp.add(1, 3);
    hopkarp.add(2, 3);
    cout << hopkarp.maxmat() << "\n";
    return 0;
}
