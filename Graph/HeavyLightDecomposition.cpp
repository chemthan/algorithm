#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int n;
vector<int> adj[maxn];
int size[maxn];
int lev[maxn];
int p[maxn];
int heavy[maxn];

int num[maxn];
int head[maxn];
int cnt;

void upd(int l, int r, int n, int val) {} //Need to modify
int query(int l, int r, int n) {return 0;} //Need to modify

void firstdfs(int u, int dad) {
    size[u] = 1, heavy[u] = -1;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != dad) {
            p[v] = u, lev[v] = lev[u] + 1;
            firstdfs(v, u);
            size[u] += size[v];
            if (heavy[u] == -1 || size[heavy[u]] < size[v]) {
                heavy[u] = v;
            }
        }
    }
}
void dfs(int u, int h, int p) {
    num[u] = cnt++, head[u] = h;
    if (~heavy[u]) {
        dfs(heavy[u], h, u);
    }
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != p && v != heavy[u]) {
            dfs(v, v, u);
        }
    }
}
void upd(int u, int v, int val) {
    int hu = head[u], hv = head[v];
    while (hu != hv) {
        if (lev[hu] < lev[hv]) swap(u, v), swap(hu, hv);
        upd(num[hu], num[u], n, val);
        u = p[hu], hu = head[u];
    }
    if (lev[u] > lev[v]) swap(u, v);
    upd(num[u], num[v], n, val); //upd(num[u] + 1, num[v]) for edge path
}
int query(int u, int v) {
    int res = 0;
    int hu = head[u], hv = head[v];
    while (hu != hv) {
        if (lev[hu] < lev[hv]) swap(u, v), swap(hu, hv);
        res += query(num[hu], num[u], n);
        u = p[hu], hu = head[u];
    }
    if (lev[u] > lev[v]) swap(u, v);
    res += query(num[u], num[v], n); //query(num[u] + 1, num[v]) for edge path
    return res;
}

int main() {
    return 0;
}
