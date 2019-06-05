#include <bits/stdc++.h>
using namespace std;

template<const int maxn, const int mod>
struct linear_solver {
    static const long long sqmod = (long long) mod * mod;
    int n;
    int a[maxn], h[maxn], s[maxn], t[maxn];
    long long t_[maxn];

    inline int fpow(int a, long long b) {
        int res = 1;
        while (b) {
            if (b & 1) res = (long long) res * a % mod;
            a = (long long) a * a % mod;
            b >>= 1;
        }
        return res;
    }
    inline vector<int> BM(vector<int> x) {
        vector<int> ls, cur;
        int lf, ld;
        for (int i = 0; i < (int) x.size(); i++) {
            long long t = 0;
            for (int j = 0; j < (int) cur.size(); j++) {
                t += (long long) x[i - j - 1] * cur[j];
                t -= sqmod <= t ? sqmod : 0;
            }
            t %= mod;
            if ((t - x[i]) % mod == 0) continue;
            if (!cur.size()) {
                cur.resize(i + 1);
                lf = i;
                ld = t - x[i];
                ld += ld < 0 ? mod : 0;
                continue;
            }
            int k = (long long) (t - x[i] + mod) * fpow(ld, mod - 2) % mod;
            vector<int> c(i - lf - 1);
            c.push_back(k);
            for (int j = 0; j < (int) ls.size(); j++) {
                c.push_back((long long) k * (mod - ls[j]) % mod);
            }
            if (c.size() < cur.size()) c.resize(cur.size());
            for (int j = 0; j < (int) cur.size(); j++) {
                c[j] += cur[j];
                c[j] -= mod <= c[j] ? mod : 0;
            }
            if (i - lf + (int) ls.size() >= (int) cur.size()) {
                ls = cur, lf = i;
                ld = t - x[i];
                ld += ld < 0 ? mod : 0;
            }
            cur = c;
        }
        for (int i = 0; i < (int) cur.size(); i++) {
            cur[i] = (cur[i] % mod + mod) % mod;
        }
        return cur;
    }
    inline void mult(int* p, int* q) {
        for (int i = 0; i < n + n; i++) t_[i] = 0;
        for (int i = 0; i < n; i++) if (p[i]) {
            for (int j = 0; j < n; j++) {
                t_[i + j] += (long long) p[i] * q[j];
                t_[i + j] -= sqmod <= t_[i + j] ? sqmod : 0;
            }
        }
        for (int i = n + n - 1; n <= i; i--) if (t_[i]) {
            t_[i] %= mod;
            for (int j = n - 1; ~j; j--) {
                t_[i - j - 1] += t_[i] * h[j];
                t_[i - j - 1] -= sqmod <= t_[i - j - 1] ? sqmod : 0;
            }
        }
        for (int i = 0; i < n; i++) p[i] = t_[i] % mod;
    }
    inline long long calc(long long k) {
        for (int i = n; ~i; i--) {
            s[i] = t[i] = 0;
        }
        s[0] = 1;
        if (n != 1) {
            t[1] = 1;
        }
        else {
            t[0] = h[0];
        }
        while (k) {
            if (k & 1) mult(s, t);
            mult(t, t); k >>= 1;
        }
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum = (sum + (long long) s[i] * a[i]) % mod;
        }
        return (sum % mod + mod) % mod;
    }
    inline int calc(vector<int> x, long long k) {
        if (k < (int) x.size()) return x[k];
        vector<int> v = BM(x);
        n = v.size();
        if (!n) return 0;
        for (int i = 0; i < n; i++) h[i] = v[i], a[i] = x[i];
        return calc(k);
    }
};
linear_solver<1 << 18, (int) 1e9 + 7> ls;

const int mod = (int) 1e9 + 7;
const int maxn = 1 << 20;
int a[maxn];
int sa[maxn];

int main() {
    a[1] = 1;
    for (int i = 2; i < maxn; i++) {
        a[i] = ((long long) a[i - 1] * 3 + (long long) a[i - 2] * 5) % mod;
    }
    vector<int> sample;
    for (int i = 0; i < maxn; i++) {
        if (i) sa[i] = sa[i - 1];
        sa[i] = (sa[i] + a[i]) % mod;
        if (i < 2 * 1 + 4) {
            sample.push_back(sa[i]);
        }
    }
    cerr << ls.calc(sample, 50000) << " " << sa[50000] << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
