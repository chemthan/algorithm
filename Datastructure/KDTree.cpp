#include <bits/stdc++.h>
using namespace std;

typedef long long T;
const int maxn = 2e5 + 10;
const T oo = (T) 1e18;
int n, q;
int x[maxn];
int y[maxn];
pair<int, int> p[maxn];
int tx[maxn];
int ty[maxn];
T best;

int cmpX(const pair<int, int>& a, const pair<int, int>& b) {return a.first < b.first;}
int cmpY(const pair<int, int>& a, const pair<int, int>& b) {return a.second < b.second;}
T dist(int x, int y, int z, int t) {return (T) (x - z) * (x - z) + (T) (y - t) * (y - t);} //Euclidean distance
//T dist(int x, int y, int z, int t) {return abs(x - z) + abs(y - t);} //Manhattan distance

void build(int l, int r, int divX, pair<int, int> p[]) {
    if (l >= r) return;
    int m = l + r >> 1;
    nth_element(p + l, p + m, p + r, divX ? cmpX : cmpY);
    tx[m] = p[m].first;
    ty[m] = p[m].second;
    build(l, m, !divX, p);
    build(m + 1, r, !divX, p);
}
void query(int l, int r, int x, int y, int divX) {
    if (l >= r) return;
    int m = l + r >> 1;
    if (dist(x, y, tx[m], ty[m])) {
        best = min(best, dist(x, y, tx[m], ty[m]));
    }
    int delta = divX ? x - tx[m] : y - ty[m];
    if (delta <= 0) {
        query(l, m, x, y, !divX);
        if (dist(delta, 0, 0, 0) < best) query(m + 1, r, x, y, !divX);
    }
    else {
        query(m + 1, r, x, y, !divX);
        if (dist(delta, 0, 0, 0) < best) query(l, m, x, y, !divX);
    }
}
T query(int x, int y) {
    best = +oo;
    query(0, n, x, y, 1);
    return best;
}

int main() {
    srand(time(NULL));
    n = 1000;
    for (int i = 0; i < n; i++) {
        x[i] = rand(), y[i] = rand();
        p[i].first = x[i], p[i].second = y[i];
    }
    build(0, n, 1, p);
    q = 1000;
    for (int i = 0; i < q; i++) {
        int u = rand(), v = rand();
        T ans = +oo;
        for (int j = 0; j < n; j++) {
            ans = min(ans, dist(u, v, x[j], y[j]));
        }
        assert(ans == query(u, v));
    }
    cout << "Correct!\n";
    return 0;
}
