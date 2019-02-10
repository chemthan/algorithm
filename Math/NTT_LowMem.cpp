#include <bits/stdc++.h>
using namespace std;

template<const int mod, const int maxf>
struct NTT {
    int pw;
    int fpow(int a, int k) {
        if (!k) return 1;
        int res = a, tmp = a;
        k--;
        while (k) {
            if (k & 1) {
                res = (long long) res * tmp % mod;
            }
            tmp = (long long) tmp * tmp % mod;
            k >>= 1;
        }
        return res;
    }
    int prt() {
        vector<int> dvs;
        for (int i = 2; i * i < mod; i++) {
            if ((mod - 1) % i) continue;
            dvs.push_back(i);
            if (i * i != mod - 1) dvs.push_back((mod - 1) / i);
        }
        for (int i = 2; i < mod; i++) {
            int flag = 1;
            for (int j = 0; j < dvs.size(); j++) {
                if (fpow(i, dvs[j]) == 1) {
                    flag = 0;
                    break;
                }
            }
            if (flag) return i;
        }
        assert(0);
        return -1;
    }
    NTT() {
        pw = prt();
    }
    void dft(int a[], int pw, int n) {
        for (int m = n, h; h = m / 2, m >= 2; pw = (long long) pw * pw % mod, m = h) {
            for (int i = 0, w = 1; i < h; i++, w = (long long) w * pw % mod) {
                for (int j = i; j < n; j += m) {
                    int k = j + h, x = a[j] - a[k];
                    a[j] += a[k];
                    a[j] -= a[j] >= mod ? mod : 0;
                    a[k] = (long long) w * (x + mod) % mod;
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
        int pwn = fpow(pw, (mod - 1) / n);
        dft(fa, pwn, n), dft(fb, pwn, n);
        for (int i = 0; i < n; i++) fc[i] = (long long) fa[i] * fb[i] % mod;
        dft(fc, fpow(pwn, mod - 2), n);
        int in = fpow(n, mod - 2);
        for (int i = 0; i < n; i++) fc[i] = (long long) fc[i] * in % mod;
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
};

const int mod = 998244353;
NTT<mod, 1 << 17> ntt;

int main() {
    srand(time(0));
    vector<int> a(1234), b(1234);
    for (int& x : a) x = rand() % mod;
    for (int& x : b) x = rand() % mod;
    vector<int> c = ntt.multiply(a, b);
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
