#include <bits/stdc++.h>
using namespace std;

namespace NTT {
    const int maxf = 1 << 20;
    int pr, pw;

    int fpow(int a, int k, int p) {
        if (!k) return 1;
        int res = a, tmp = a;
        k--;
        while (k) {
            if (k & 1) {
                res = (long long) res * tmp % p;
            }
            tmp = (long long) tmp * tmp % p;
            k >>= 1;
        }
        return res;
    }
    void init(int _pr, int _pw) {
        pr = _pr, pw = _pw;
    }
    void dft(int a[], int pr, int pw, int n) {
        for (int m = n, h; h = m / 2, m >= 2; pw = (long long) pw * pw % pr, m = h) {
            for (int i = 0, w = 1; i < h; i++, w = (long long) w * pw % pr) {
                for (int j = i; j < n; j += m) {
                    int k = j + h, x = a[j] - a[k];
                    a[j] += a[k];
                    a[j] -= a[j] >= pr ? pr : 0;
                    a[k] = (long long) w * (x + pr) % pr;
                }
            }
        }
        for (int i = 0, j = 1; j < n - 1; j++) {
            for (int k = n / 2; k > (i ^= k); k /= 2);
            if (j < i) swap(a[i], a[j]);
        }
    }
    int fa[maxf], fb[maxf], fc[maxf];
    void multiply(int a[], int b[], int na, int nb, int c[]) {
        int n = na + nb - 1; while (n != (n & -n)) n += n & -n;
        for (int i = na; i < n; i++) fa[i] = 0;
        for (int i = nb; i < n; i++) fb[i] = 0;
        int pwn = fpow(pw, (pr - 1) / n, pr);
        dft(fa, pr, pwn, n), dft(fb, pr, pwn, n);
        for (int i = 0; i < n; i++) fc[i] = (long long) fa[i] * fb[i] % pr;
        dft(fc, pr, fpow(pwn, pr - 2, pr), n);
        int in = fpow(n, pr - 2, pr);
        for (int i = 0; i < n; i++) fc[i] = (long long) fc[i] * in % pr;
    }
    vector<int> multiply(vector<int> a, vector<int> b) {
        int na = a.size(), nb = b.size();
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        multiply(fa, fb, na, nb, fc);
        int k = na + nb - 1;
        vector<int> res(k);
        for (int i = 0; i < k; i++) res[i] = fc[i];
        return res;
    }
}

const int mod = 998244353;

int main() {
    srand(time(0));
    vector<int> a(123), b(123);
    for (int& x : a) x = rand() % mod;
    for (int& x : b) x = rand() % mod;
    NTT::init(mod, 3);
    vector<int> c = NTT::multiply(a, b);
    vector<int> d(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            d[i + j] += (long long) a[i] * b[j] % mod;
            d[i + j] -= d[i + j] >= mod ? mod : 0;
        }
    }
    assert(c == d);
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
