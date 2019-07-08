#include <bits/stdc++.h>
using namespace std;

#define double long double
namespace FFT {
    const int maxf = 1 << 17;
    struct cp {
        double x, y;
        cp(double x = 0, double y = 0) : x(x), y(y) {}
        cp operator + (const cp& rhs) const {
            return cp(x + rhs.x, y + rhs.y);
        }
        cp operator - (const cp& rhs) const {
            return cp(x - rhs.x, y - rhs.y);
        }
        cp operator * (const cp& rhs) const {
            return cp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
        }
        cp operator !() const {
            return cp(x, -y);
        }
    } rts[maxf + 1];
    cp fa[maxf], fb[maxf];
    cp fc[maxf], fd[maxf];

    int bitrev[maxf];
    void fftinit() {
        int k = 0; while ((1 << k) < maxf) k++;
        bitrev[0] = 0;
        for (int i = 1; i < maxf; i++) {
            bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << k - 1);
        }
        double PI = acos((double) -1.0);
        rts[0] = rts[maxf] = cp(1, 0);
        for (int i = 1; i + i <= maxf; i++) {
            rts[i] = cp(cos(i * 2 * PI / maxf), sin(i * 2 * PI / maxf));
        }
        for (int i = maxf / 2 + 1; i < maxf; i++) {
            rts[i] = !rts[maxf - i];
        }
    }
    void dft(cp a[], int n, int sign) {
        static int isinit;
        if (!isinit) {
            isinit = 1;
            fftinit();
        }
        int d = 0; while ((1 << d) * n != maxf) d++;
        for (int i = 0; i < n; i++) {
            if (i < (bitrev[i] >> d)) {
                swap(a[i], a[bitrev[i] >> d]);
            }
        }
        for (int len = 2; len <= n; len <<= 1) {
            int delta = maxf / len * sign;
            for (int i = 0; i < n; i += len) {
                cp *x = a + i,*y = a + i + (len >> 1), *w = sign > 0 ? rts : rts + maxf;
                for (int k = 0; k + k < len; k++) {
                    cp z = *y * *w;
                    *y = *x - z, *x = *x + z;
                    x++, y++, w += delta;
                }
            }
        }
        if (sign < 0) {
            for (int i = 0; i < n; i++) {
                a[i].x /= n;
                a[i].y /= n;
            }
        }
    }
    void multiply(int a[], int b[], int na, int nb, long long c[], int dup = 0) {
        int n = na + nb - 1; while (n != (n & -n)) n += n & -n;
        for (int i = 0; i < n; i++) fa[i] = fb[i] = cp();
        for (int i = 0; i < na; i++) fa[i] = cp(a[i]);
        for (int i = 0; i < nb; i++) fb[i] = cp(b[i]);
        dft(fa, n, 1);
        if (dup) {
            for (int i = 0; i < n; i++) fb[i] = fa[i];
        }
        else {
            dft(fb, n, 1);
        }
        for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
        dft(fa, n, -1);
        for (int i = 0; i < n; i++) c[i] = (long long) floor(fa[i].x + 0.5);
    }
    void multiply(int a[], int b[], int na, int nb, int c[], int mod = (int) 1e9 + 7, int dup = 0) {
        int n = na + nb - 1;
        while (n != (n & -n)) n += n & -n;
        for (int i = 0; i < n; i++) fa[i] = fb[i] = cp();
        static const int magic = 15;
        for (int i = 0; i < na; i++) fa[i] = cp(a[i] >> magic, a[i] & (1 << magic) - 1);
        for (int i = 0; i < nb; i++) fb[i] = cp(b[i] >> magic, b[i] & (1 << magic) - 1);
        dft(fa, n, 1);
        if (dup) {
            for (int i = 0; i < n; i++) fb[i] = fa[i];
        }
        else {
            dft(fb, n, 1);
        }
        for (int i = 0; i < n; i++) {
            int j = (n - i) % n;
            cp x = fa[i] + !fa[j];
            cp y = fb[i] + !fb[j];
            cp z = !fa[j] - fa[i];
            cp t = !fb[j] - fb[i];
            fc[i] = (x * t + y * z) * cp(0, 0.25);
            fd[i] = x * y * cp(0, 0.25) + z * t * cp(-0.25, 0);
        }
        dft(fc, n, -1), dft(fd, n, -1);
        for (int i = 0; i < n; i++) {
            long long u = ((long long) floor(fc[i].x + 0.5)) % mod;
            long long v = ((long long) floor(fd[i].x + 0.5)) % mod;
            long long w = ((long long) floor(fd[i].y + 0.5)) % mod;
            c[i] = ((u << magic) + v + (w << magic + magic)) % mod;
        }
    }
    vector<int> multiply(vector<int> a, vector<int> b, int mod = (int) 1e9 + 7) {
        static int fa[maxf], fb[maxf], fc[maxf];
        int na = a.size(), nb = b.size();
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        multiply(fa, fb, na, nb, fc, mod, a == b);
        int k = na + nb - 1;
        vector<int> res(k);
        for (int i = 0; i < k; i++) res[i] = fc[i];
        return res;
    }
    int fpow(int a, int k, int p) {
        if (!k) return 1;
        int res = a, t = a; k--;
        while (k) {
            if (k & 1) res = (long long) res * t % p;
            t = (long long) t * t % p;
            k >>= 1;
        }
        return res;
    }
    vector<int> invert(vector<int> a, int n, int mod){
        assert(a[0] != 0);
        vector<int> x(1, fpow(a[0], mod - 2, mod));
        while (x.size() < n) {
            vector<int> tmp(a.begin(), a.begin() + min(a.size(), 2 * x.size()));
            vector<int> nx = multiply(multiply(x, x, mod), tmp, mod);
            x.resize(2 * x.size());
            for (int i = 0; i < x.size(); i++) {
                x[i] += x[i];
                x[i] -= nx[i];
                if (x[i] < 0) x[i] += mod;
                if (x[i] >= mod) x[i] -= mod;
            }
        }
        x.resize(n);
        return x;
    }
    pair<vector<int>, vector<int> > divmod(vector<int> a, vector<int> b, int mod) {
        int n = a.size(), m = b.size();
        if (n < m) {
            return make_pair(vector<int>(), a);
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        vector<int> rb = invert(b, n - m + 1, mod);
        vector<int> d = multiply(a, rb, mod);
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        while (d.size() > n - m + 1) d.pop_back();
        reverse(d.begin(), d.end());
        vector<int> r = multiply(d, b, mod);
        while (r.size() >= m) r.pop_back();
        for (int i = 0; i < m; i++) {
            r[i] = a[i] - r[i];
            if (r[i] < 0) r[i] += mod;
        }
        return make_pair(d, r);
    }
    vector<int> chirpz_transform(vector<int> a, int z, int k, int mod) {
        int n = a.size();
        vector<int> x;
        vector<int> y;
        int iz = fpow(z, mod - 2, mod);
        for (int i = 0; i < n; i++) {
            x.push_back((long long) a[i] * fpow(z, (long long) i * i, mod) % mod);
        }
        for (int i = 1 - n; i < k; i++) {
            y.push_back(fpow(iz, (long long) i * i, mod));
        }
        vector<int> r = FFT::multiply(x, y, mod);
        vector<int> res(k);
        for (int i = 0; i < k; i++) {
            res[i] = (long long) r[i + n - 1] * fpow(z, (long long) i * i, mod) % mod;
        }
        return res;
    }
}
#undef double

const int maxn = 1e5 + 5;
const int mod = (int) 1e9 + 7;
int n, m;
int a[maxn];
vector<int> st[maxn << 2];

void build(int p, int L, int R) {
    if (L == R) {
        st[p].resize(2);
        st[p][0] = mod - a[L + R >> 1];
        st[p][1] = 1;
        return;
    }
    build(p << 1, L, L + R >> 1);
    build(p << 1 | 1, (L + R >> 1) + 1, R);
    st[p] = FFT::multiply(st[p << 1], st[p << 1 | 1]);
    while (st[p].size() > R - L + 2) st[p].pop_back();
}

void divide(int p, int L, int R, vector<int> poly, vector<int>& vals) {
    poly = FFT::divmod(poly, st[p], mod).second;
    if (L == R) {
        vals[L + R >> 1] = poly[0];
        return;
    }
    divide(p << 1, L, L + R >> 1, poly, vals);
    divide(p << 1 | 1, (L + R >> 1) + 1, R, poly, vals);
}

void testdivmod() {
    int n = 1000 + rand() % 100, m = 100 + rand() % 10;
    vector<int> a, b;
    for (int i = 0; i < n; i++) {
        a.push_back(rand() % mod);
    }
    for (int i = 0; i < m; i++) {
        b.push_back(rand() % mod);
    }
    pair<vector<int>, vector<int> > res = FFT::divmod(a, b, mod);
    vector<int> d = res.first;
    vector<int> r = res.second;
    assert(r.size() < b.size());
    vector<int> c = FFT::multiply(b, d, mod);
    for (int i = 0; i < r.size(); i++) {
        c[i] += r[i];
        if (c[i] >= mod) {
            c[i] -= mod;
        }
    }
    for (int i = 0; i < n; i++) {
        assert(a[i] == c[i]);
    }
}

void testmuleval() {
    n = 5000, m = 5000;
    vector<int> poly;
    for (int i = 0; i < n; i++) {
        a[i] = rand() % mod;
    }
    for (int i = 0; i < m; i++) {
        poly.push_back(rand() % mod);
    }
    build(1, 0, n - 1);
    vector<int> vals(n);
    divide(1, 0, n - 1, poly, vals);
    for (int i = 0; i < n; i++) {
        int t = 0;
        for (int j = (int) poly.size() - 1; j >= 0; j--) {
            t = ((long long) t * a[i] + poly[j]) % mod;
        }
        assert(t == vals[i]);
    }
}

void testchirpz_transform() {
    int n = 1234;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % mod;
    }
    int z = rand() % mod;
    vector<int> r = FFT::chirpz_transform(a, z, n, mod);
    for (int i = 0; i < n; i++) {
        int x = FFT::fpow(z, i + i, mod);
        int y = 0;
        for (int j = 0; j < n; j++) {
            y += (long long) a[j] * FFT::fpow(x, j, mod) % mod;
            if (mod <= y) y -= mod;
        }
        assert(y == r[i]);
    }
}

int main() {
    srand(time(0));
    testdivmod();
    testmuleval();
    testchirpz_transform();
    cerr << "Correct!\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
