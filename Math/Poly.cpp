#include <bits/stdc++.h>
using namespace std;

#define double long double
const int MAXF = 1 << 18;
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
} rts[MAXF + 1];
cp fa[MAXF], fb[MAXF];
cp fc[MAXF], fd[MAXF];

int bitrev[MAXF];
void fftinit() {
    int k = 0; while ((1 << k) < MAXF) k++;
    bitrev[0] = 0;
    for (int i = 1; i < MAXF; i++) {
        bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << k - 1);
    }
    double PI = acos((double) -1.0);
    cp w = cp(cos(2 * PI / MAXF), sin(2 * PI / MAXF));
    rts[0] = rts[MAXF] = cp(1, 0);
    for (int i = 1; i + i <= MAXF; i++) {
        rts[i] = rts[i - 1] * w;
    }
    for (int i = MAXF / 2 + 1; i < MAXF; i++) {
        rts[i] = !rts[MAXF - i];
    }
}
void dft(cp a[], int n, int sign) {
    int d = 0; while ((1 << d) * n != MAXF) d++;
    for (int i = 0; i < n; i++) {
        if (i < (bitrev[i] >> d)) {
            swap(a[i], a[bitrev[i] >> d]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        int delta = MAXF / len * sign;
        for (int i = 0; i < n; i += len) {
            cp *x = a + i,*y = a + i + (len >> 1), *w = sign > 0 ? rts : rts + MAXF;
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
void multiply(int a[], int b[], int na, int nb, long long c[]) {
    int n = na + nb - 1; while (n != (n & -n)) n += n & -n;
    for (int i = 0; i < n; i++) fa[i] = fb[i] = cp();
    for (int i = 0; i < na; i++) fa[i] = cp(a[i]);
    for (int i = 0; i < nb; i++) fb[i] = cp(b[i]);
    dft(fa, n, 1), dft(fb, n, 1);
    for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
    dft(fa, n, -1);
    for (int i = 0; i < n; i++) c[i] = (long long) floor(fa[i].x + 0.5);
}
void multiply(int a[], int b[], int na, int nb, int c[], int mod = (int) 1e9 + 7) {
    int n = na + nb - 1;
    while (n != (n & -n)) n += n & -n;
    for (int i = 0; i < n; i++) fa[i] = fb[i] = cp();
    static const int magic = 15;
    for (int i = 0; i < na; i++) fa[i] = cp(a[i] >> magic, a[i] & (1 << magic) - 1);
    for (int i = 0; i < nb; i++) fb[i] = cp(b[i] >> magic, b[i] & (1 << magic) - 1);
    dft(fa, n, 1), dft(fb, n, 1);
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
        c[i] = ((u << 15) + v + (w << 30)) % mod;
    }
}
vector<int> multiply(vector<int>& a, vector<int>& b, int mod = (int) 1e9 + 7) {
    static int fa[MAXF], fb[MAXF], fc[MAXF];
    int na = a.size(), nb = b.size();
    for (int i = 0; i < na; i++) fa[i] = a[i];
    for (int i = 0; i < nb; i++) fb[i] = b[i];
    multiply(fa, fb, na, nb, fc, mod);
    int k = na + nb - 1;
    vector<int> res(k);
    for (int i = 0; i < k; i++) res[i] = fc[i];
    return res;
}
int fpow(int a, int k, int p) {
    if (!k) return 1;
    int res = a, tmp = a; k--;
    while (k) {
        if (k & 1) res = (long long) res * tmp % p;
        tmp = (long long) tmp * tmp % p;
        k >>= 1;
    }
    return res;
}
vector<int> invert(vector<int> a, int n, int mod) {
    if (n == 1) {
        vector<int> res(1);
        res[0] = fpow(a[0], mod - 2, mod);
        return res;
    }
    int nn = n + 1 >> 1;
    vector<int> b = invert(a, nn, mod);
    vector<int> c = multiply(b, b, mod);
    c = multiply(a, c, mod);
    while (b.size() < n) b.push_back(0);
    while (b.size() > n) b.pop_back();
    for (int i = 0; i < n; i++) {
        b[i] = b[i] + b[i] - c[i];
        if (b[i] >= mod) b[i] -= mod;
        if (b[i] < 0) b[i] += mod;
    }
    return b;
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
    st[p] = multiply(st[p << 1], st[p << 1 | 1]);
    while (st[p].size() > R - L + 2) st[p].pop_back();
}

void divide(int p, int L, int R, vector<int> poly, vector<int>& vals) {
    poly = divmod(poly, st[p], mod).second;
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
    pair<vector<int>, vector<int> > res = divmod(a, b, mod);
    vector<int> d = res.first;
    vector<int> r = res.second;
    assert(r.size() < b.size());
    vector<int> c = multiply(b, d, mod);
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
    n = 50000, m = 50000;
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
    //for (int i = 0; i < n; i++) {
    //    int t = 0;
    //    for (int j = (int) poly.size() - 1; j >= 0; j--) {
    //        t = ((long long) t * a[i] + poly[j]) % mod;
    //    }
    //    assert(t == vals[i]);
    //}
}

int main() {
    srand(time(NULL));
    fftinit();
    testdivmod();
    testmuleval();
    cerr << "Correct!\n";
    cerr << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
