#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(1) for updating, O(sqrt(N)) for query
* Problems:
* 1. http://codeforces.com/gym/100818/status/B
* 2. http://codeforces.com/gym/100962/status/F
* 3. https://www.codechef.com/problems/CUBTOWER
*/
struct RangeQuery {
    static const int maxn = 1e5 + 5;
    static const int magic = 320;
    int a[maxn];
    int b[maxn];
    int block[magic];
    vector<int> his;

    void clear() {
        while (his.size()) {
            int k = his.back();
            a[k] = b[k] = block[k / magic] = 0;
            his.pop_back();
        }
    }
    void upd(int n, int val) {
        if (!(b[n]++)) {
            his.push_back(n);
        }
        a[n] += val;
        block[n / magic] += val;
    }
    int query(int l, int r) {
        int res = 0;
        int u = l / magic;
        int v = r / magic;
        for (int i = u + 1; i < v; i++) {
            res += block[i];
        }
        for (int i = l; i <= min(r, (u + 1) * magic - 1); i++) {
            res += a[i];
        }
        if (u < v) {
            for (int i = max(l, v * magic); i <= r; i++) {
                res += a[i];
            }
        }
        return res;
    }
} rq;

const int maxn = 1e5 + 5;
int a[maxn];

int main() {
    srand(time(NULL));
    for (int i = 0; i < 10000; i++) {
        int x = abs(rand()) % 10000;
        int v = abs(rand()) % 10000;
        a[x] += v;
        rq.upd(x, v);
    }
    for (int i = 0; i < 10000; i++) {
        int l = abs(rand()) % 10000;
        int r = abs(rand()) % 10000;
        if (l > r) swap(l, r);
        int res = 0;
        for (int i = l; i <= r; i++) {
            res += a[i];
        }
        assert(res == rq.query(l, r));
    }
    cout << "Correct!\n";
    return 0;
}
