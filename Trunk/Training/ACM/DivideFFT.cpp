#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: N(logN)^2
* Solve dp formula: a[i] = a[i - 1] * b[0] + a[i - 2] * b[1] + ... + a[0] * b[i - 1]
* Problems:
* 1. http://codeforces.com/contest/553/problem/E
* 2. http://codeforces.com/gym/100959/status/H
* 3. https://www.bnuoj.com/v3/problem_show.php?pid=52248
*/
typedef long double db;
struct cp {
    db x, y;
    cp(db x = 0, db y = 0) : x(x), y(y) {}
    cp operator + (const cp& rhs) {return cp(x + rhs.x, y + rhs.y);}
    cp operator - (const cp& rhs) {return cp(x - rhs.x, y - rhs.y);}
    cp operator * (const cp& rhs) {return cp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);}
    cp operator !() {return cp(x, -y);}
};
void fft(cp a[], int n, int invert) {
    static const db PI = acos((db) -1);
    cp w = cp(cos(2 * PI / n), sin(2 * PI / n));
    if (invert) w = !w;
    for (int k = n / 2; k >= 1; k >>= 1, w = w * w) {
        cp t = cp(1, 0);
        for (int i = 0; i < k; i++, t = t * w) {
            for (int j = i; j + k < n; j += k + k) {
                cp x = a[j];
                cp y = a[j + k];
                a[j] = x + y;
                a[j + k] = (x - y) * t;
            }
        }
    }
    int k = __lg(n);
    for (int msk = 0; msk < n; msk++) {
        int nmsk = 0;
        for (int i = 0; i < k; i++) {
            if ((msk >> i) & 1) {
                nmsk |= 1 << k - i - 1;
            }
        }
        if (msk < nmsk) {
            swap(a[msk], a[nmsk]);
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++) {
            a[i].x /= n;
            a[i].y /= n;
        }
    }
}
void multiply(int a[], int b[], int c[], int na, int nb, int mod = (int) 1e9 + 7) {
    static cp fa[1 << 20], fb[1 << 20];
    static cp fc[1 << 20], fd[1 << 20];
    int n = na + nb - 1;
    while (n != (n & -n)) n += n & -n;
    for (int i = 0; i < n; i++) fa[i] = fb[i] = cp(0, 0);
    for (int i = 0; i < na; i++) fa[i] = cp(a[i] >> 15, a[i] & (1 << 15) - 1);
    for (int i = 0; i < nb; i++) fb[i] = cp(b[i] >> 15, b[i] & (1 << 15) - 1);
    fft(fa, n, 0), fft(fb, n, 0);
    for (int i = 0; i < n; i++) {
        int j = (n - i) % n;
        cp x = fa[i] + !fa[j];
        cp y = fb[i] + !fb[j];
        cp z = !fa[j] - fa[i];
        cp t = !fb[j] - fb[i];
        fc[i] = (x * t + y * z) * cp(0, 0.25);
        fd[i] = x * y * cp(0, 0.25) + z * t * cp(-0.25, 0);
    }
    fft(fc, n, 1), fft(fd, n, 1);
    for (int i = 0; i < n; i++) {
        long long u = ((long long) floor(fc[i].x + 0.5)) % mod;
        long long v = ((long long) floor(fd[i].x + 0.5)) % mod;
        long long w = ((long long) floor(fd[i].y + 0.5)) % mod;
        c[i] = ((u << 15) + v + (w << 30)) % mod;
    }
}

const int maxn = 1 << 20;
const int mod = (int) 1e9 + 7;
int n;
int a[maxn];
int b[maxn];
int c[maxn << 1];
int d[maxn];

int main() {
    srand(time(NULL));
    n = 1000;
    a[0] = d[0] = rand();
    for (int i = 0; i < n; i++) {
        b[i] = rand();
    }
    for (int i = 0; i < n; i++) {
        //a[i] has been computed
        for (int k = 1; (i + 1) % k == 0; k <<= 1) {
            multiply(a + i - k + 1, b + k - 1, c, k, k, mod);
            for (int j = i + 1; j < i + 2 * k; j++) {
                a[j] = (a[j] + c[j - i - 1]) % mod;
            }
        }
        for (int j = 0; j < i; j++) {
            d[i] = (d[i] + (long long) d[j] * b[i - j - 1]) % mod;
        }
        cout << a[i] << " " << d[i] << "\n";
        assert(a[i] == d[i]);
    }
    cout << "Correct!\n";
    return 0;
}
