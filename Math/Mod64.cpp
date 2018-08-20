#include <bits/stdc++.h>
using namespace std;

template<class num_t>
num_t modmul(num_t a, num_t b, num_t p) {
    a %= p, b %= p;
    num_t q = (num_t) ((long double) a * b / p);
    num_t r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
    /*
       num_t r = 0;
       int block = 1;
       num_t base = 1LL << block;
       for (; b; b >>= block) {
       r = (r + a * (b & (base - 1))) % p;
       a = a * base % p;
       }
       return r;
     */
}
template<class num_t>
num_t modpow(num_t n, num_t k, num_t p) {
    if (!n) return 0;
    num_t r = 1;
    for (; k; k >>= 1) {
        if (k & 1) r = modmul(r, n, p);
        n = modmul(n, n, p);
    }
    return r;
}

int main() {
    long long a = (long long) 1e15 + 2311;
    long long b = (long long) 1e16 + 1992;
    long long p = (long long) 1e18 + 2016;
    assert(modmul(a, b, p) == 81840000004553112LL);
    assert(modpow(a, b, p) == 457363391775234913LL);
    cerr << "Correct!\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
