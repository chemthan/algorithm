#include <bits/stdc++.h>
using namespace std;

#define BS BitSet
#define num_t unsigned long long
#define WS 6
#define MS 63
const num_t unit = (num_t) 1;
struct BitSet {
    int n, len;
    num_t* mem;

    BitSet() {
        n = len = 0;
    }
    BitSet(int _len) {
        n = _len + MS >> WS;
        len = n << WS;
        mem = (num_t*) calloc(n, sizeof(num_t));
    }
    BitSet(const BitSet& rhs) {
        n = rhs.n;
        len = rhs.len;
        mem = (num_t*) malloc(sizeof(num_t) * n);
        memcpy(mem, rhs.mem, sizeof(num_t) * n);
    }
    ~BitSet() {
        if (n) {
            free(mem);
        }
    }
    BitSet& operator = (const BitSet& rhs) {
        if (n) {
            free(mem);
        }
        n = rhs.n;
        len = rhs.len;
        mem = (num_t*) malloc(sizeof(num_t) * n);
        memcpy(mem, rhs.mem, sizeof(num_t) * n);
        return *this;
    }
    BitSet operator >> (const int k) {
        BitSet res(len);
        int d = k >> WS;
        int r = k & MS;
        num_t msk = (unit << r) - 1;
        int shift = MS - r + 1;
        for (int i = 0; i < n - d - 1; i++) {
            res.mem[i] = ((mem[i + d + 1] & msk) << shift) | (mem[i + d] >> r);
        }
        if (d < n) {
            res.mem[n - d - 1] = mem[n - 1] >> r;
        }
        return res;
    }
    BitSet& operator >>= (const int k) {
        int d = k >> WS;
        int r = k & MS;
        num_t msk = (unit << r) - 1;
        int shift = MS - r + 1;
        for (int i = 0; i < n - d - 1; i++) {
            mem[i] = ((mem[i + d + 1] & msk) << shift) | (mem[i + d] >> r);
        }
        if (d < n) {
            mem[n - d - 1] = mem[n - 1] >> r;
        }
        memset(mem + n - d, 0, sizeof(num_t) * d);
        return *this;
    }
    BitSet operator << (const int k) {
        BitSet res(len);
        int d = k >> WS;
        int r = k & MS;
        num_t msk = ((unit << r) - 1) << MS - r + 1;
        int shift = MS - r + 1;
        for (int i = d + 1; i < n; i++) {
            res.mem[i] = (mem[i - d] << r) | ((mem[i - d - 1] & msk) >> shift);
        }
        if (d < n) {
            res.mem[d] = mem[0] << r;
        }
        return res;
    }
    BitSet& operator <<= (const int k) {
        int d = k >> WS;
        int r = k & MS;
        num_t msk = ((unit << r) - 1) << MS - r + 1;
        int shift = MS - r + 1;
        for (int i = n; i > d; i--) {
            mem[i] = (mem[i - d] << r) | ((mem[i - d - 1] & msk) >> shift);
        }
        if (d < n) {
            mem[d] = mem[0] << r;
        }
        memset(mem, 0, sizeof(num_t) * d);
        return *this;
    }
    BitSet gets(int l, int r) {
        BitSet res(len);
        int x = l + MS >> WS;
        int y = r >> WS;
        if (x <= y) {
            memcpy(res.mem + x, mem + x, sizeof(num_t) * (y - x));
        }
        for (int i = l; i < min(x << WS, r + 1); i++) {
            res.set(i, get(i));
        }
        if (x <= y) {
            for (int i = (y << WS); i <= r; i++) {
                res.set(i, get(i));
            }
        }
        return res;
    }
    void resize(int _len) {
        int nn = _len + MS >> WS;
        if (n ^ nn) {
            int nlen = nn << WS;
            num_t* nmem = (num_t*) calloc(nn, sizeof(num_t));
            memcpy(nmem, mem, sizeof(num_t) * min(n, nn));
            if (n) {
                free(mem);
            }
            n = nn, len = nlen, mem = nmem;
        }
    }
    inline int get(int k) {
        if (len <= k) return 0;
        return (mem[k >> WS] >> (k & MS)) & 1;
    }
    inline void set(int k, int v) {
        if (len <= k) return;
        ((mem[k >> WS] |= unit << (k & MS)) ^= unit << (k & MS)) |= v * (unit << (k & MS));
    }
    inline void reset(int v = 0) {
        memset(mem, !v ? 0 : -1, sizeof(num_t) * n);
    }
    inline int count() {
        int res = 0;
        for (int i = 0; i < n; i++) {
            res += __builtin_popcountll(mem[i]);
        }
        return res;
    }
    inline int firstBit() {
        for (int i = 0; i < n; i++) {
            if (mem[i]) {
                return (i << WS) + __lg(mem[i] & -mem[i]);
            }
        }
        return len;
    }
    inline int lastBit() {
        for (int i = n - 1; i >= 0; i--) {
            if (mem[i]) {
                return (i << WS) + __lg(mem[i]);
            }
        }
        return -1;
    }
    inline int nextBit(int k) {
        k++;
        if (k < 0) k = 0;
        if (len <= k) return len;
        int d = k >> WS;
        int r = k & MS;
        num_t t = (mem[d] >> r) << r;
        if (t) {
            return (d << WS) + __lg(t & -t);
        }
        for (int i = d + 1; i < n; i++) {
            if (mem[i]) {
                return (i << WS) + __lg(mem[i] & -mem[i]);
            }
        }
        return len;
    }
    inline int prevBit(int k) {
        k--;
        if (k < 0) return -1;
        if (len <= k) k = len - 1;
        int d = k >> WS;
        int r = k & MS;
        num_t t = (mem[d] << MS - r) >> MS - r;
        if (t) {
            return (d << WS) + __lg(t);
        }
        for (int i = d - 1; i >= 0; i--) {
            if (mem[i]) {
                return (i << WS) + __lg(mem[i]);
            }
        }
        return -1;
    }
    friend ostream& operator << (ostream& os, const BitSet& bs) {
        for (int i = 0; i < bs.len; i++) {
            os << bs.mem[i];
        }
        return os;
    }
#define MAKE(OP)\
    BitSet operator OP (const BitSet& rhs) const {\
        int mx = max(len, rhs.len);\
        BitSet res(mx);\
        memcpy(res.mem, mem, sizeof(num_t) * n);\
        for (int i = 0; i < rhs.n % 4; i++) {\
            res.mem[i] = res.mem[i] OP rhs.mem[i];\
        }\
        for (int i = rhs.n % 4; i < rhs.n; i += 4) {\
            res.mem[i] = res.mem[i] OP rhs.mem[i];\
            res.mem[i + 1] = res.mem[i + 1] OP rhs.mem[i + 1];\
            res.mem[i + 2] = res.mem[i + 2] OP rhs.mem[i + 2];\
            res.mem[i + 3] = res.mem[i + 3] OP rhs.mem[i + 3];\
        }\
        return res;\
    }
#define MAKE2(OP)\
    BitSet& operator OP (const BitSet& rhs) {\
        int mx = max(len, rhs.len);\
        resize(mx);\
        for (int i = 0; i < rhs.n % 4; i++) {\
            mem[i] OP rhs.mem[i];\
        }\
        for (int i = rhs.n % 4; i < rhs.n; i += 4) {\
            mem[i] OP rhs.mem[i];\
            mem[i + 1] OP rhs.mem[i + 1];\
            mem[i + 2] OP rhs.mem[i + 2];\
            mem[i + 3] OP rhs.mem[i + 3];\
        }\
        return *this;\
    }
    MAKE(&) MAKE(|) MAKE(^) MAKE2(&=) MAKE2(|=) MAKE2(^=)
};

int main() {
    BS bs1(2e5), bs2(2e5);
    bs1 ^ bs2;
    for (int i = 0; i < 2e5; i++) {
        BS bs3 = bs1 ^ bs2;
    }
    int ar[] = {1, 2, 7, 100, 200, bs1.len - 2, bs2.len - 1};
    for (int i = 0; i < 7; i++) {
        bs1.set(ar[i], 1);
    }
    int st = bs1.firstBit();
    while (st < bs1.len) {
        cout << st << " ";
        st = bs1.nextBit(st);
    }
    cout << "\n";
    int ed = bs1.lastBit();
    while (-1 < ed) {
        cout << ed << " ";
        ed = bs1.prevBit(ed);
    }
    cout << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
