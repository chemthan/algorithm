#include <bits/stdc++.h>
using namespace std;

typedef int num_t;
namespace CRT {
    const int maxn = 123;
    int n;
    num_t p[maxn], r[maxn];
    num_t b[maxn], x[maxn];

    void clear() {
        n = 0;
    }
    void add(num_t pr, num_t rm) {
        assert(0 <= rm && rm < pr);
        for (int i = 0; i < n; i++) {
            assert(__gcd(p[i], pr) == 1);
        }
        p[n] = pr, r[n++] = rm;
    }
    num_t mul(num_t a, num_t b, num_t p) {
        a %= p, b %= p;
        num_t q = (num_t) ((long double) a * b / p);
        num_t r = a * b - q * p;
        while (r < 0) r += p;
        while (r >= p) r -= p;
        return r;
    }
    pair<num_t, num_t> euclid(num_t a, num_t b) {
        if (!b) return make_pair(1, 0);
        pair<num_t, num_t> r = euclid(b, a % b);
        return make_pair(r.second, r.first - a / b * r.second);
    }
    num_t calc() {
        num_t M = 1;
        for (int i = 0; i < n; i++) M *= p[i];
        num_t N = 0;
        for (int i = 0; i < n; i++) {
            b[i] = M / p[i];
            x[i] = (euclid(b[i], p[i]).first % p[i] + p[i]) % p[i];
            N += mul(r[i] * b[i], x[i], M);
            if (N >= M) N -= M;
        }
        return N;
    }
}

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
    cerr << "Correct!\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
