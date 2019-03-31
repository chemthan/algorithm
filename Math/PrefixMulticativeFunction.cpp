#include <bits/stdc++.h>
using namespace std;
#define db(x) cerr << #x << " = " << (x) << " ";
#define endln cerr << "\n";

#define PSMF PrefixSumMulticativeFunction
namespace PrefixSumMulticativeFunction {
    //for prime p
    inline long long func(int p, int e) {
        if (!e) return 1;
        return p;
    }
    //func(2, 1) + func(3, 1) + ... + func(n, 1)
    inline long long accfunc(long long n) {
        /*
           long long res = 0;
           for (int i = 2; i <= n; i++) res += func(i, 1); //Can be computed in O(1)?
           return res;
         */
        return n * (n + 1) / 2 - 1;
    }
    //func(1) + func(2) + ... + func(n)
    long long calc(long long n) {
        int magic = sqrt(n) + 1;
        while (n < (long long) magic * magic) magic--;
        vector<int> ispr(magic + 1, 1);
        vector<int> prs;
        for (int i = 2; i <= magic; i++) if (ispr[i]) {
            for (int j = i + i; j <= magic; j += i) {
                ispr[j] = 0;
            }
            prs.push_back(i);
        }
        vector<long long> vals;
        for (int i = 1; i <= magic; i++) {
            vals.push_back(i);
        }
        for (int i = 1; i <= n / magic; i++) {
            if (magic < n / i) {
                vals.push_back(n / i);
            }
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        vector<int> idx(n / magic + 1);
        for (int i = 0; i < vals.size(); i++) {
            if (magic < vals[i]) {
                int lo = (n + vals[i]) / (vals[i] + 1);
                int hi = n / vals[i];
                for (int j = lo; j <= hi; j++) {
                    idx[j] = i;
                }
            }
        }
        int k = vals.size();
        vector<long long> f(k);
        for (int i = 0; i < k; i++) {
            f[i] = accfunc(vals[i]);
        }
        for (int p : prs) {
            for (int i = k - 1; i >= 0; i--) {
                long long j = vals[i];
                long long t = j / p;
                if ((long long) p * p <= j) {
                    if (t <= magic) {
                        f[i] -= (f[j / p - 1] - f[p - 2]) * func(p, 1);
                    }
                    else {
                        int w = idx[n / t];
                        assert(vals[w] == t);
                        f[i] -= (f[w] - f[p - 2]) * func(p, 1);
                    }
                }
                else {
                    break;
                }
            }
        }
        long long res = f[k - 1] + func(1, 0);
        function<void(int, long long, long long, int)> rec = [&] (int st, long long val, long long fval, int num) {
            long long nfval = fval * func(prs[st], num);
            if (num) {
                if (val * prs[st] < n) {
                    long long sum = 0;
                    if (n / val <= magic) {
                        sum = f[n / val - 1];
                    }
                    else {
                        int w = idx[val];
                        assert(vals[w] == n / val);
                        sum = f[w];
                    }
                    sum -= f[prs[st] - 1];
                    res += nfval * sum;
                }
                if (1 < num) {
                    res += nfval;
                }
            }
            long long lim = sqrt(n / val) + 1;
            for (int i = st + 1; i < prs.size() && prs[i] <= lim; i++) {
                int nnum = 1;
                for (long long nval = val * prs[i]; ; nval *= prs[i], nnum++) {
                    if (1 < nnum || nval < n / prs[i]) {
                        rec(i, nval, nfval, nnum);
                    }
                    if (n / prs[i] < nval) {
                        break;
                    }
                }
            }
        };
        rec(-1, 1, 1, 0);
        return res;
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));
    long long n = 1e5 - rand() % 12345;
    long long t = PSMF::calc(n);
    if (1) {
        vector<int> sp(n + 1);
        for (int i = 1; i < sp.size(); i++) sp[i] = i;
        for (int i = 2; i < sp.size(); i++)  if (sp[i] == i) {
            for (int j = i + i; j < sp.size(); j += i) {
                sp[j] = min(sp[j], i);
            }
        }
        vector<long long> f(n + 1, 1);
        for (int i = 1; i < f.size(); i++) {
            map<int, int> hs;
            int t = i;
            while (1 < t) {
                hs[sp[t]]++;
                t /= sp[t];
            }
            for (auto e : hs) {
                f[i] *= PSMF::func(e.first, e.second);
            }
        }
        long long res = 0;
        for (int i = 1; i < f.size(); i++) {
            res += f[i];
        }
        cout << res << " ";
        assert(t == res);
    }
    cout << t << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
