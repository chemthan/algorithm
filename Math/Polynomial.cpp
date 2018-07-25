#include <bits/stdc++.h>
using namespace std;

int fpow(int n, int k, int p) {
    int r = 1;
    for (; k; k >>= 1) {
        if (k & 1) r = (long long) r * n % p;
        n = (long long) n * n % p;
    }
    return r;
}

struct Polynomial {
    //nirjhor's code
    static const int maxn = 1e3 + 5;
    static const int limit = 1e3;
    static const int mod = (int) 1e9 + 7;
    int deg;
    vector<int> cof;
    Polynomial(int deg = 0) : deg(deg){
        cof.resize(deg + 1, 0);
    }
    void init(int deg) {
        this->deg = deg;
        cof.resize(deg + 1, 0);
        for (int i = 0; i <= deg; i++) {
            cof[i] = 0;
        }
    }
    void shrink() {
        cof.resize(deg + 1);
    }
    friend Polynomial product(Polynomial f, Polynomial g) {
        Polynomial h(f.deg + g.deg);
        for (int i = 0; i <= f.deg; i++) {
            for (int j = 0; j <= g.deg; j++) {
                h.cof[i + j] = (h.cof[i + j] + (long long) f.cof[i] * g.cof[j]) % mod;
            }
        }
        return h;
    }
    //Assuming deg f >= deg g
    friend Polynomial quotient(Polynomial f, Polynomial g) {
        Polynomial q(f.deg - g.deg);
        for (int i = q.deg; i >= 0; i--) {
            q.cof[i] = (long long) f.cof[g.deg + i] * fpow(g.cof[g.deg], mod - 2, mod) % mod;
            for (int j = g.deg; j >= 0; j--) {
                f.cof[i + j] = (f.cof[i + j] - (long long) q.cof[i] * g.cof[j] % mod + mod) % mod;
            }
        }
        return q;
    }
    friend Polynomial remainder(Polynomial f, Polynomial g) {
        if (f.deg < g.deg) return f;
        for (int i = f.deg - g.deg; i >= 0; i--) {
            int c = (long long) f.cof[g.deg + i] * fpow(g.cof[g.deg], mod - 2, mod) % mod;
            for (int j = g.deg; j >= 0; j--) {
                f.cof[i + j] = (f.cof[i + j] - (long long) c * g.cof[j] % mod + mod) % mod;
            }
        }
        f.deg = g.deg - 1;
        while (!f.cof[f.deg]) f.deg--;
        f.deg = max(f.deg, 0);
        f.shrink();
        return f;
    }
    //Assuming deg f >= deg g
    friend Polynomial gcd(Polynomial f, Polynomial g) {
        if (!g.deg && !g.cof[0]) return f;
        return gcd(g, remainder(f, g));
    }
    //Cantor-Zassenhaus Algorithm
    friend vector<int> findroots(Polynomial f) {
        srand(time(NULL));
        vector<int> res;
        if (f.deg == 1) {
            int root = (mod - (long long) f.cof[0] * fpow(f.cof[1], mod - 2, mod) % mod) % mod;
            res.push_back(root);
            return res;
        }
        int it = 0;
        while (it++ < limit) {
            int d = rand() % mod;
            Polynomial a(1), r(0);
            a.cof[1] = 1, a.cof[0] = d;
            r.cof[0] = 1;
            int k = (mod - 1) >> 1;
            while (k) {
                if (k & 1) r = remainder(product(r, a), f);
                a = remainder(product(a, a), f);
                k >>= 1;
            }
            r.cof[0]--;
            a = gcd(f, r);
            if (a.deg > 0 && a.deg < f.deg) {
                r = quotient(f, a);
                res = findroots(a);
                vector<int> res2 = findroots(r);
                res.insert(res.end(), res2.begin(), res2.end());
                it = 0;
                return res;
            }
        }
        return res;
    }
} poly;

const int mod = (int) 1e9 + 7;

int main() {
    poly.init(3);
    poly.cof[0] = 1;
    poly.cof[1] = mod - 3;
    poly.cof[2] = 3;
    poly.cof[3] = mod - 1;
    vector<int> root = findroots(poly);
    for (int i = 0; i < (int) root.size(); i++) {
        cout << root[i] << " \n"[i == (int) root.size() - 1]; //Expected: 1 1 1
    }
    return 0;
}
