#include <bits/stdc++.h>
using namespace std;

template<class T> T mulmod(T a, T b, T p) {
    a %= p; b %= p;
    T q = (T) ((long double) a * b / p);
    T r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
    /*
    T r = 0;
    int block = 1;
    T base = 1LL << block;
    for (; b; b >>= block) {
        r = (r + a * (b & (base - 1))) % p;
        a = a * base % p;
    }
    return r;
    */
}
template<class T> T powmod(T n, T k, T p) {
    if (!n) return 0;
    T r = 1;
    for (; k; k >>= 1) {
        if (k & 1) r = mulmod(r, n, p);
        n = mulmod(n, n, p);
    }
    return r;
}
template<class T> int rabin(T n) {
    if (n == 2) return 1;
    if (n < 2 || !(n & 1)) return 0;
    const T p[3] = {3, 5, 7};
    T a, d = n - 1, mx = 3;
    int i, r, s = 0;
    while (!(d & 1)) {++s; d >>= 1;}
    for (i = 0; i < mx; i++) {
        if (n == p[i]) return 1;
        if (!(n % p[i])) return 0;
        a = powmod(p[i], d, n);
        if (a != 1) {
            for (r = 0; r < s && a != n - 1; r++) a = mulmod(a, a, n);
            if (r == s) return 0;
        }
    }
    return 1;
}
//Bruteforce for small n
template<class T> T pollardrho(T n) {
    int it = 0, k = 2;
    T x = 3, y = 3;
    while (1) {
        it++;
        x = (mulmod(x, x, n) + n - 1) % n;
        T d = __gcd(abs(y - x), n);
        if (d != 1 && d != n) return d;
        if (it == k) y = x, k <<= 1;
    }
}

int main() {
    long long n = 2063512844981574047LL;
    long long ans = pollardrho(n);
    assert(n % ans == 0);
    cout << ans << " " << n / ans << "\n"; //Expected: 1112041493 1855607779
    return 0;
}
