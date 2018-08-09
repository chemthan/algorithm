#include <bits/stdc++.h>
using namespace std;

#define SCALE int
namespace CRT {
    const int MAXN = 123;
    int n;
    SCALE p[MAXN], r[MAXN];
    SCALE b[MAXN], x[MAXN];

    void clear() {
        n = 0;
    }
    void add(SCALE pr, SCALE rm) {
        assert(0 <= rm && rm < pr);
        for (int i = 0; i < n; i++) {
            assert(__gcd(p[i], pr) == 1);
        }
        p[n] = pr, r[n++] = rm;
    }
    SCALE mul(SCALE a, SCALE b, SCALE p) {
        a %= p, b %= p;
        SCALE q = (SCALE) ((long double) a * b / p);
        SCALE r = a * b - q * p;
        while (r < 0) r += p;
        while (r >= p) r -= p;
        return r;
    }
    pair<SCALE, SCALE> euclid(SCALE a, SCALE b) {
        if (!b) return make_pair(1, 0);
        pair<SCALE, SCALE> r = euclid(b, a % b);
        return make_pair(r.second, r.first - a / b * r.second);
    }
    SCALE calc() {
        SCALE M = 1;
        for (int i = 0; i < n; i++) M *= p[i];
        SCALE N = 0;
        for (int i = 0; i < n; i++) {
            b[i] = M / p[i];
            x[i] = (euclid(b[i], p[i]).first % p[i] + p[i]) % p[i];
            N += mul(r[i] * b[i], x[i], M);
            if (N >= M) N -= M;
        }
        return N;
    }
};

int main() {
    int p[] = {2, 3, 5};
    int r[] = {1, 2, 3};
    CRT::clear();
    for (int i = 0; i < 3; i++) {
        CRT::add(p[i], r[i]);
    }
    int res = CRT::calc();
    for (int i = 0; i < 3; i++) {
        assert(res % p[i] == r[i]);
    }
    cerr << "Correct\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
