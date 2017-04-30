#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: average O(logN)
*/
template<class TC, class TD> struct KDTree {
    static const int maxn = 1e5 + 5;
    static const TD oo = (TD) 1e18;
    TC tx[maxn];
    TC ty[maxn];
    TD best;
    
    static int cmpX(const pair<TC, TC>& a, const pair<TC, TC>& b) {return a.first < b.first;}
    static int cmpY(const pair<TC, TC>& a, const pair<TC, TC>& b) {return a.second < b.second;}
    TD dist(TC x, TC y, TC z, TC t) {return (TD) (x - z) * (x - z) + (TD) (y - t) * (y - t);} //Euclidean distance
    //TD dist(TC x, TC y, TC z, TC t) {return abs(x - z) + abs(y - t);} //Manhattan distance
    
    void build(int l, int r, int divX, pair<TC, TC> p[]) {
        if (l >= r) return;
        int m = l + r >> 1;
        nth_element(p + l, p + m, p + r, divX ? cmpX : cmpY);
        tx[m] = p[m].first;
        ty[m] = p[m].second;
        build(l, m, !divX, p);
        build(m + 1, r, !divX, p);
    }
    void query(int l, int r, TC x, TC y, int divX) {
        if (l >= r) return;
        int m = l + r >> 1;
        if (dist(x, y, tx[m], ty[m])) {
            best = min(best, dist(x, y, tx[m], ty[m]));
        }
        TC delta = divX ? x - tx[m] : y - ty[m];
        if (delta <= 0) {
            query(l, m, x, y, !divX);
            if (dist(delta, 0, 0, 0) < best) query(m + 1, r, x, y, !divX);
        }
        else {
            query(m + 1, r, x, y, !divX);
            if (dist(delta, 0, 0, 0) < best) query(l, m, x, y, !divX);
        }
    }
    TD query(TC x, TC y, int n) {
        best = oo;
        query(0, n, x, y, 1);
        return best;
    }
};
KDTree<int, long long> kd;

const int maxn = 1e5 + 5;
const long long oo = (long long) 1e18;
int n, q;
int x[maxn];
int y[maxn];
pair<int, int> p[maxn];

int main() {
    srand(time(NULL));
    n = 1000;
    for (int i = 0; i < n; i++) {
        x[i] = rand(), y[i] = rand();
        p[i].first = x[i], p[i].second = y[i];
    }
    kd.build(0, n, 1, p);
    q = 1000;
    for (int i = 0; i < q; i++) {
        int u = rand(), v = rand();
        long long ans = oo;
        for (int j = 0; j < n; j++) {
            ans = min(ans, kd.dist(u, v, x[j], y[j]));
        }
        assert(ans == kd.query(u, v, n));
    }
    cout << "Correct!\n";
    return 0;
}
