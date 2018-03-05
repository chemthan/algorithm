#include <bits/stdc++.h>
using namespace std;

const int pr[3] = {1004535809, 1007681537, 1012924417}; //2 ^ 20 * {958, 961, 966} + 1
const int pw[3] = {3, 3, 5}; //primitive roots
struct NTT {
    static const int MAXF = 1 << 18;
    int pr;
    int rts[MAXF + 1];
    int bitrev[MAXF];
    int iv[MAXF + 1];

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
    void init(int pr, int pw) {
        this->pr = pr;
        int k = 0; while ((1 << k) < MAXF) k++;
        bitrev[0] = 0;
        for (int i = 1; i < MAXF; i++) {
            bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << k - 1);
        }
        pw = fpow(pw, (pr - 1) / MAXF, pr);
        rts[0] = 1;
        for (int i = 1; i <= MAXF; i++) {
            rts[i] = (long long) rts[i - 1] * pw % pr;
        }
        for (int i = 1; i <= MAXF; i <<= 1) {
            iv[i] = fpow(i, pr - 2, pr);
        }
    }
    void dft(int a[], int n, int sign) {
        int d = 0; while ((1 << d) * n != MAXF) d++;
        for (int i = 0; i < n; i++) {
            if (i < (bitrev[i] >> d)) {
                swap(a[i], a[bitrev[i] >> d]);
            }
        }
        for (int len = 2; len <= n; len <<= 1) {
            int delta = MAXF / len * sign;
            for (int i = 0; i < n; i += len) {
                int *w = sign > 0 ? rts : rts + MAXF;
                for (int k = 0; k + k < len; k++) {
                    int &a1 = a[i + k + (len >> 1)], &a2 = a[i + k];
                    int t = (long long) *w * a1 % pr;
                    a1 = a2 - t;
                    a2 = a2 + t;
                    a1 += a1 < 0 ? pr : 0;
                    a2 -= a2 >= pr ? pr : 0;
                    w += delta;
                }
            }
        }
        if (sign < 0) {
            int in = iv[n];
            for (int i = 0; i < n; i++) {
                a[i] = (long long) a[i] * in % pr;
            }
        }
    }
    void multiply(int a[], int b[], int na, int nb, int c[]) {
        static int fa[MAXF], fb[MAXF];
        int n = na + nb - 1; while (n != (n & -n)) n += n & -n;
        for (int i = 0; i < n; i++) fa[i] = fb[i] = 0;
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        dft(fa, n, 1), dft(fb, n, 1);
        for (int i = 0; i < n; i++) fa[i] = (long long) fa[i] * fb[i] % pr;
        dft(fa, n, -1);
        for (int i = 0; i < n; i++) c[i] = fa[i];
    }
    vector<int> multiply(vector<int> a, vector<int> b) {
        static int fa[MAXF], fb[MAXF], fc[MAXF];
        int na = a.size(), nb = b.size();
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        multiply(fa, fb, na, nb, fc);
        int k = na + nb - 1;
        vector<int> res(k);
        for (int i = 0; i < k; i++) res[i] = fc[i];
        return res;
    }
} ntt;

const int MAXF = 1 << 18;
int n;
int a[MAXF];
int b[MAXF];
int c[MAXF];
int d[MAXF];

int main() {
    srand(time(NULL));
    ntt.init(pr[0], pw[0]);
    n = 1000;
    for (int i = 0; i < n; i++) {
        a[i] = rand() % pr[0];
        b[i] = rand() % pr[0];
    }
    ntt.multiply(a, b, n, n, c);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i + j] = (d[i + j] + (long long) a[i] * b[j]) % pr[0];
        }
    }
    for (int i = 0; i < n + n - 1; i++) {
        assert(c[i] == d[i]);
    }
    cerr << "Correct\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
