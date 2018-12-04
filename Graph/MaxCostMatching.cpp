#include <bits/stdc++.h>
using namespace std;

#define MCM MaxCostMatching
namespace MaxCostMatching {
#define dist(e) (lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2)
    const int maxn = 1e3 + 5;
    const int oo = (int) 1e9;
    struct Edge {
        int u, v, w;
    } g[maxn][maxn];

    int n, m, n_x;
    int lab[maxn], match[maxn], slack[maxn], st[maxn], pa[maxn];
    int flower_from[maxn][maxn], s[maxn], vis[maxn];
    vector<int> flower[maxn];
    deque<int> q;

    void init(int _n) {
        n = _n;
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                g[u][v] = Edge{u, v, 0};
            }
        }
    }
    void add(int u, int v, int w) {
        g[u][v].w = max(g[u][v].w, w);
        g[v][u].w = max(g[v][u].w, w);
    }
    void update_slack(int u,int x) {
        if (!slack[x] || dist(g[u][x]) < dist(g[slack[x]][x])) slack[x] = u;
    }
    void set_slack(int x) {
        slack[x] = 0;
        for (int u = 1; u <= n; u++) {
            if (g[u][x].w > 0 && st[u] != x && s[st[u]] == 0) update_slack(u, x);
        }
    }
    void q_push(int x) {
        if (x <= n) return q.push_back(x);
        for (int i = 0; i < flower[x].size(); i++) q_push(flower[x][i]);
    }
    void set_st(int x,int b) {
        st[x] = b;
        if (x <= n) return;
        for(int i = 0; i < flower[x].size(); i++) set_st(flower[x][i], b);
    }
    int get_pr(int b,int xr) {
        int pr = find(flower[b].begin(), flower[b].end(), xr) - flower[b].begin();
        if (pr % 2 == 1) {
            reverse(flower[b].begin() + 1, flower[b].end());
            return (int) flower[b].size() - pr;
        }
        else {
            return pr;
        }
    }
    void set_match(int u, int v) {
        match[u] = g[u][v].v;
        if (u <= n) return;
        Edge e = g[u][v];
        int xr = flower_from[u][e.u], pr = get_pr(u, xr);
        for (int i = 0; i < pr; i++) set_match(flower[u][i], flower[u][i ^ 1]);
        set_match(xr, v);
        rotate(flower[u].begin(), flower[u].begin() + pr, flower[u].end());
    }
    void augment(int u, int v) {
        int xnv = st[match[u]];
        set_match(u, v);
        if (!xnv) return;
        set_match(xnv, st[pa[xnv]]);
        augment(st[pa[xnv]], xnv);
    }
    int get_lca(int u, int v) {
        static int t = 0;
        for (t++; u || v; swap(u, v)) {
            if (u == 0) continue;
            if(vis[u] == t) return u;
            vis[u] = t;
            u = st[match[u]];
            if (u) u = st[pa[u]];
        }
        return 0;
    }
    void add_blossom(int u, int lca, int v) {
        int b = n + 1;
        while (b <= n_x && st[b]) b++;
        if (b > n_x) n_x++;
        lab[b] = 0, s[b] = 0;
        match[b] = match[lca];
        flower[b].clear();
        flower[b].push_back(lca);
        for (int x = u, y; x != lca; x = st[pa[y]]) {
            flower[b].push_back(x), flower[b].push_back(y = st[match[x]]), q_push(y);
        }
        reverse(flower[b].begin() + 1, flower[b].end());
        for (int x = v, y; x != lca; x = st[pa[y]]) {
            flower[b].push_back(x), flower[b].push_back(y = st[match[x]]), q_push(y);
        }
        set_st(b, b);
        for (int x = 1; x <= n_x; x++) g[b][x].w = g[x][b].w = 0;
        for (int x = 1; x <= n; x++) flower_from[b][x] = 0;
        for (int i = 0; i < flower[b].size(); i++) {
            int xs = flower[b][i];
            for (int x = 1; x <= n_x; x++) {
                if (g[b][x].w == 0 || dist(g[xs][x]) < dist(g[b][x])) {
                    g[b][x] = g[xs][x], g[x][b] = g[x][xs];
                }
            }
            for (int x = 1; x <= n; x++) {
                if (flower_from[xs][x]) flower_from[b][x] = xs;
            }
        }
        set_slack(b);
    }
    void expand_blossom(int b) {
        for (int i = 0; i < flower[b].size(); i++) {
            set_st(flower[b][i], flower[b][i]);
        }
        int xr = flower_from[b][g[b][pa[b]].u], pr=get_pr(b, xr);
        for (int i = 0; i < pr; i += 2) {
            int xs = flower[b][i], xns = flower[b][i + 1];
            pa[xs] = g[xns][xs].u;
            s[xs] = 1, s[xns] = 0;
            slack[xs] = 0, set_slack(xns);
            q_push(xns);
        }
        s[xr] = 1, pa[xr] = pa[b];
        for (int i = pr + 1; i < flower[b].size(); i++) {
            int xs = flower[b][i];
            s[xs] = -1, set_slack(xs);
        }
        st[b] = 0;
    }
    int on_found_Edge(const Edge &e) {
        int u = st[e.u], v = st[e.v];
        if (s[v] == -1) {
            pa[v] = e.u, s[v] = 1;
            int nu = st[match[v]];
            slack[v] = slack[nu] = 0;
            s[nu] = 0, q_push(nu);
        }
        else if (s[v] == 0) {
            int lca = get_lca(u, v);
            if (!lca) return augment(u, v), augment(v, u), 1;
            else add_blossom(u, lca, v);
        }
        return 0;
    }
    int matching() {
        fill(s, s + n_x + 1, -1), fill(slack, slack + n_x + 1, 0);
        q.clear();
        for(int x = 1; x <= n_x; x++) {
            if (st[x] == x && !match[x]) pa[x] = 0, s[x]= 0, q_push(x);
        }
        if (q.empty()) return 0;
        while (1) {
            while (q.size()) {
                int u = q.front();
                q.pop_front();
                if (s[st[u]] == 1) continue;
                for (int v = 1; v <= n; v++) {
                    if (g[u][v].w > 0 && st[u] != st[v]) {
                        if (dist(g[u][v]) == 0) {
                            if (on_found_Edge(g[u][v])) return 1;
                        }
                        else update_slack(u, st[v]);
                    }
                }
            }
            int d = oo;
            for (int b = n + 1; b <= n_x; b++) {
                if (st[b] == b && s[b] == 1) d = min(d, lab[b] / 2);
            }
            for (int x = 1; x <= n_x; x++) {
                if (st[x] == x && slack[x]) {
                    if (s[x] == -1) d = min(d, dist(g[slack[x]][x]));
                    else if (s[x] == 0) d = min(d, dist(g[slack[x]][x]) / 2);
                }
            }
            for (int u = 1; u <= n; u++) {
                if (s[st[u]] == 0) {
                    if (lab[u] <= d) return 0;
                    lab[u] -= d;
                }
                else if (s[st[u]] == 1) lab[u] += d;
            }
            for (int b = n + 1; b <= n_x; b++) {
                if (st[b] == b) {
                    if (s[st[b]] == 0) lab[b] += d * 2;
                    else if (s[st[b]] == 1) lab[b] -= d * 2;
                }
            }
            q.clear();
            for (int x = 1; x <= n_x; x++) {
                if (st[x] == x && slack[x] && st[slack[x]] !=x && dist(g[slack[x]][x]) == 0) {
                    if (on_found_Edge(g[slack[x]][x])) return 1;
                }
            }
            for (int b = n + 1; b <= n_x; b++) {
                if (st[b]==b && s[b] == 1 && lab[b] == 0) expand_blossom(b);
            }
        }
        return 0;
    }
    int maxcost() {
        fill(match, match + n + 1, 0);
        n_x = n;
        int tot_weight = 0;
        int n_matches = 0;
        for (int u = 0; u <= n; u++) st[u] = u, flower[u].clear();
        int w_max = 0;
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                flower_from[u][v] = (u == v ? u : 0);
                w_max = max(w_max, g[u][v].w);
            }
        }
        for (int u = 1; u <= n; u++) lab[u] = w_max;
        while (matching()) n_matches++;
        for (int u = 1; u <= n; u++) {
            if (match[u] && match[u] < u) {
                tot_weight += g[u][match[u]].w;
            }
        }
        return tot_weight;
    }
}

int main() {
    MCM::init(4);
    MCM::add(1, 2, 5);
    MCM::add(2, 3, 10);
    MCM::add(3, 4, 2);
    cout << MCM::maxcost() << "\n";
    return 0;
}
