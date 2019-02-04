#include <bits/stdc++.h>
using namespace std;

typedef int num_t;
namespace CRT {
    num_t res = 0;
    num_t prd = 1;

    void clear() {
        res = 0, prd = 1;
    }
    num_t mul(num_t a, num_t b, num_t p) {
        a %= p, b %= p;
        num_t q = (num_t) ((long double) a * b / p);
        num_t r = a * b - q * p;
        while (r < 0) r += p;
        while (r >= p) r -= p;
        return r;
    }
    template<typename num_t>
    pair<num_t, num_t> euclid(num_t a, num_t b) {
        if (!b) return make_pair(1, 0);
        pair<num_t, num_t> r = euclid(b, a % b);
        return make_pair(r.second, r.first - a / b * r.second);
    }
    void add(num_t p, num_t r) {
        res += mul(r - res % p + p, euclid(prd, p).first + p, p) * prd;
        prd *= p;
        if (res >= prd) res -= prd;
    }
}

int main() {
    int p[] = {2, 3, 5};
    int r[] = {1, 2, 3};
    CRT::clear();
    for (int i = 0; i < 3; i++) {
        CRT::add(p[i], r[i]);
    }
    for (int i = 0; i < 3; i++) {
        assert(CRT::res % p[i] == r[i]);
    }
    cerr << "Correct!\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
