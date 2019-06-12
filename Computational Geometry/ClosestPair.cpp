#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
typedef long long T;
const T oo = (T) 1e18;
struct point_t {
    int x, y;
    point_t() : x(0), y(0) {}
    point_t(int x, int y) : x(x), y(y) {}
    point_t(const point_t& rhs) : x(rhs.x), y(rhs.y) {}
    int operator < (const point_t& rhs) const {return make_pair(x, y) < make_pair(rhs.x, rhs.y);}
} mem[MAXN];
T squaredist(point_t a, point_t b) {
    return (T) (a.x - b.x) * (a.x - b.x) + (T) (a.y - b.y) * (a.y - b.y);
}
int cmpY(point_t lhs, point_t rhs) {
    return make_pair(lhs.y, lhs.x) < make_pair(rhs.y, rhs.x);
}
T closestpair(point_t p[], int l, int r) {
    T res = oo;
    if (r - l <= 3) {
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                res = min(res, squaredist(p[i], p[j]));
            }
        }
        sort(p + l, p + r + 1, cmpY);
    }
    else {
        int mid = l + r >> 1;
        int xmid = p[mid].x;
        res = min(closestpair(p, l, mid), closestpair(p, mid + 1, r));
        inplace_merge(p + l, p + mid + 1, p + r + 1, cmpY);
        int cnt = 0;
        for (int i = l; i <= r; i++) {
            if ((T) (p[i].x - xmid) * (p[i].x - xmid) < res) mem[cnt++] = p[i];
        }
        for (int i = 0; i < cnt; i++) {
            for (int j = 1; j <= 8 && i + j < cnt; j++) {
                res = min(res, squaredist(mem[i], mem[i + j]));
            }
        }
    }
    return res;
}

int n;
point_t p[MAXN];

int main() {
    srand(time(NULL));
    for (int test = 1; test < 1000; test++) {
        n = rand() % 1000 + 1;
        for (int i = 0; i < n; i++) {
            p[i].x = rand();
            p[i].y = rand();
        }
        T ans = oo;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans = min(ans, squaredist(p[i], p[j]));
            }
        }
        sort(p, p + n);
        assert(ans == closestpair(p, 0, n - 1));
    }
    cout << "Correct!\n";
    return 0;
}
