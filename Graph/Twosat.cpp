#include <bits/stdc++.h>
using namespace std;

#define pos(v) ((v) << 1)
#define neg(v) (pos(v) ^ 1)
struct Twosat {
    static const int MAXV = 2e5 + 5;
    int n;
    vector<int> forward[MAXV], backward[MAXV];
    bool used[MAXV];
    int cnt, order[MAXV], comp[MAXV];
    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            forward[i].clear();
            backward[i].clear();
        }
    }
    void add(int u, int v) {
        forward[u].push_back(v);
        backward[v].push_back(u);
    }
    void dfs1(int u) {
        used[u] = true;
        for (int i = 0; i < forward[u].size(); i++) {
            int v = forward[u][i];
            if (!used[v]) dfs1(v);
        }
        order[cnt++] = u;
    }
    void dfs2(int u, int c) {
        comp[u] = c;
        for (int i = 0; i < backward[u].size(); i++) {
            int v = backward[u][i];
            if (comp[v] == -1) dfs2(v, c);
        }
    }
    int solve(vector<int>& res) {
        cnt = 0;
        memset(used, 0, sizeof(used));
        for (int u = 0; u < n; u++) if (!used[u]) dfs1(u);
        memset(comp, -1, sizeof(comp));
        int c = 0;
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            if (comp[u] == -1) dfs2(u, c++);
        }
        for (int u = 0; u < n; u += 2)
            if (comp[u] == comp[u ^ 1]) return 0;
        res.clear();
        for (int u = 0; u < n; u += 2) {
            int choose = (comp[u] > comp[u ^ 1]) ? u : u ^ 1;
            if (!(choose & 1)) res.push_back(choose >> 1);
        }
        return 1;
    }
} twosat;

int main() {
    return 0;
}
