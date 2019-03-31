#include <bits/stdc++.h>
using namespace std;

#define double long double
namespace FFT {
    const int maxf = 1 << 18; //Up to one million digits
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
    void multiply(int a[], int b[], int na, int nb, int c[], int& nc, int base, int dup) {
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
        nc = 0;
        long long carry = 0;
        for (int i = 0; i < n; i++) {
            long long u = (long long) round(fc[i].x);
            long long v = (long long) round(fd[i].x);
            long long w = (long long) round(fd[i].y);
            long long ncarry = (u / base << 15) + (u % base << 15) / base + v / base + (w / base << 30) + (w % base << 30) / base;
            assert(0 <= ncarry && ncarry < 2e18);
            long long t = (u % base << 15) % base + v % base + (w % base << 30) % base + carry;
            carry = ncarry + t / base;
            assert(carry < 2e18);
            c[nc++] = t % base;
        }
        while (carry) {
            c[nc++] = carry % base;
            carry /= base;
        }
    }
    vector<int> multiply(vector<int> a, vector<int> b, int base) {
        static int fa[maxf], fb[maxf], fc[maxf + 5];
        int na = a.size(), nb = b.size();
        for (int i = 0; i < na; i++) fa[i] = a[i];
        for (int i = 0; i < nb; i++) fb[i] = b[i];
        int nc = 0;
        multiply(fa, fb, na, nb, fc, nc, base, a == b);
        vector<int> res(nc);
        for (int i = 0; i < nc; i++) res[i] = fc[i];
        while (1 < res.size() && !res.back()) res.pop_back();
        return res;
    }
}
#undef double

const int base = 10;
const int nblock = 9;
const int blockbase = (int) round(pow(base, nblock));
struct Bignum {
    vector<int> a;
    int sign;
    Bignum() : sign(1) {}
    Bignum(long long v) {*this = v;}
    Bignum(const string& s) {read(s);}
    void operator = (const Bignum& v) {sign = v.sign; a = v.a;}
    void operator = (long long v) {
        a.clear();
        sign = 1;
        if (v < 0)
            sign = -1, v = -v;
        for (; v > 0; v = v / blockbase)
            a.push_back(v % blockbase);
    }
    Bignum operator + (const Bignum& v) const {
        if (sign == v.sign) {
            Bignum res = v;
            for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; i++) {
                if (i == (int) res.a.size()) res.a.push_back(0);
                res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
                carry = res.a[i] >= blockbase;
                if (carry) res.a[i] -= blockbase;
            }
            return res;
        }
        return *this - (-v);
    }
    Bignum operator - (const Bignum& v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                Bignum res = *this;
                for (int i = 0, carry = 0; i < (int) v.a.size() || carry; i++) {
                    res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry) res.a[i] += blockbase;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }
    void operator *= (int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; i++) {
            if (i == (int) a.size()) a.push_back(0);
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / blockbase);
            a[i] = (int) (cur % blockbase);
        }
        trim();
    }
    void operator *= (long long v) {
        if (v >= (long long) blockbase * blockbase) {
            *this *= Bignum(v);
        }
        int a = v / blockbase;
        int b = v % blockbase;
        *this = *this * a * blockbase + *this * b;
    }
    Bignum operator * (int v) const {
        Bignum res = *this;
        res *= v;
        return res;
    }
    Bignum operator * (long long v) const {
        Bignum res = *this;
        res *= v;
        return res;
    }
    friend pair<Bignum, Bignum> divmod(const Bignum& a1, const Bignum& b1) {
        int norm = blockbase / (b1.a.back() + 1);
        Bignum a = a1.abs() * norm;
        Bignum b = b1.abs() * norm;
        Bignum q, r;
        q.a.resize(a.a.size());
        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= blockbase;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long) blockbase * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0)
                r += b, d--;
            q.a[i] = d;
        }
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
    Bignum operator / (const Bignum& v) const {
        return divmod(*this, v).first;
    }
    Bignum operator % (const Bignum& v) const {
        return divmod(*this, v).second;
    }
    void operator /= (int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; i--) {
            long long cur = a[i] + rem * (long long) blockbase;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }
    void operator /= (long long v) {
        *this /= Bignum(v);
    }
    Bignum operator / (int v) const {
        Bignum res = *this;
        res /= v;
        return res;
    }
    Bignum operator / (long long v) const {
        Bignum res = *this;
        res /= v;
        return res;
    }
    int operator % (int v) const {
        if (v < 0) v = -v;
        int m = 0;
        for (int i = a.size() - 1; i >= 0; i--) m = (a[i] + m * (long long) blockbase) % v;
        return m * sign;
    }
    long long operator % (long long v) const {
        return (*this % Bignum(v)).longValue();
    }
    void operator += (const Bignum& v) {
        *this = *this + v;
    }
    void operator -= (const Bignum& v) {
        *this = *this - v;
    }
    void operator *= (const Bignum& v) {
        *this = *this * v;
    }
    void operator /= (const Bignum& v) {
        *this = *this / v;
    }
    bool operator < (const Bignum& v) const {
        if (sign != v.sign) return sign < v.sign;
        if (a.size() != v.a.size()) return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--) if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
        return false;
    }
    bool operator > (const Bignum& v) const {
        return v < *this;
    }
    bool operator <= (const Bignum& v) const {
        return !(v < *this);
    }
    bool operator >= (const Bignum& v) const {
        return !(*this < v);
    }
    bool operator == (const Bignum& v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator != (const Bignum& v) const {
        return *this < v || v < *this;
    }
    void trim() {
        while (!a.empty() && !a.back()) a.pop_back();
        if (a.empty()) sign = 1;
    }
    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }
    Bignum operator - () const {
        Bignum res = *this;
        res.sign = -sign;
        return res;
    }
    Bignum abs() const {
        Bignum res = *this;
        res.sign *= res.sign;
        return res;
    }
    long long longValue() const {
        long long res = 0;
        for (int i = a.size() - 1; i >= 0; i--) res = res * blockbase + a[i];
        return res * sign;
    }
    friend Bignum gcd(const Bignum& a, const Bignum& b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    friend Bignum lcm(const Bignum& a, const Bignum& b) {
        return a / gcd(a, b) * b;
    }
    void read(const string& s) {
        sign = 1; a.clear(); int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {if (s[pos] == '-') sign = -sign; pos++;}
        for (int i = s.size() - 1; i >= pos; i -= nblock) {
            int x = 0;
            for (int j = max(pos, i - nblock + 1); j <= i; j++) x = x * base + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    friend istream& operator>>(istream& stream, Bignum& v) {
        string s; stream>>s; v.read(s);
        return stream;
    }
    friend ostream& operator<<(ostream& stream, const Bignum& v) {
        if (v.sign == -1) stream << '-';
        stream<<(v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; i--) stream << setw(nblock) << setfill('0') << v.a[i];
        return stream;
    }
    static vector<int> convert_base(const vector<int>& a, int old_digits, int new_digits) {
        vector<long long> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int) p.size(); i++) p[i] = p[i - 1] * base;
        vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int) a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back(int(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int) cur);
        while (!res.empty() && !res.back()) res.pop_back();
        return res;
    }
    static vector<long long> karatsuba(vector<long long>& a, vector<long long>& b) {
        int n = a.size();
        vector<long long> res(n << 1);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }
        int k = n >> 1;
        vector<long long> a1(a.begin(), a.begin() + k);
        vector<long long> a2(a.begin() + k, a.end());
        vector<long long> b1(b.begin(), b.begin() + k);
        vector<long long> b2(b.begin() + k, b.end());
        vector<long long> a1b1 = karatsuba(a1, b1);
        vector<long long> a2b2 = karatsuba(a2, b2);
        for (int i = 0; i < k; i++) a2[i] += a1[i];
        for (int i = 0; i < k; i++) b2[i] += b1[i];
        vector<long long> r = karatsuba(a2, b2);
        for (int i = 0; i < (int) a1b1.size(); i++) r[i] -= a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++) r[i] -= a2b2[i];
        for (int i = 0; i < (int) r.size(); i++) res[i + k] += r[i];
        for (int i = 0; i < (int) a1b1.size(); i++) res[i] += a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++) res[i + n] += a2b2[i];
        return res;
    }
    Bignum operator * (const Bignum& v) const {
        if ((max(this->a.size(), v.a.size()) * 9 + 5) / 6 <= 8192) {
            int r = 6;
            int t = round(pow(base, r));
            vector<int> ar = convert_base(this->a, nblock, r);
            vector<int> br = convert_base(v.a, nblock, r);
            vector<long long> a(ar.begin(), ar.end());
            vector<long long> b(br.begin(), br.end());
            while (a.size() < b.size()) a.push_back(0);
            while (b.size() < a.size()) b.push_back(0);
            while (a.size() & (a.size() - 1)) a.push_back(0), b.push_back(0);
            vector<long long> c = karatsuba(a, b);
            Bignum res;
            res.sign = sign * v.sign;
            long long carry = 0;
            for (int i = 0; i < (int) c.size(); i++) {
                long long ncarry = c[i] + carry;
                res.a.push_back(ncarry % t);
                carry = ncarry / t;
            }
            while (carry) {
                res.a.push_back(carry % t);
                carry /= t;
            }
            res.a = convert_base(res.a, r, nblock);
            res.trim();
            return res;
        }
        else {
            vector<int> c = FFT::multiply(this->a, v.a, blockbase);
            Bignum res;
            res.sign = sign * v.sign;
            int carry = 0;
            for (int i = 0; i < (int) c.size(); i++) {
                int ncarry = c[i] + carry;
                res.a.push_back(ncarry % blockbase);
                carry = ncarry / blockbase;
            }
            assert(!carry);
            while (carry) {
                res.a.push_back(carry % blockbase);
                carry /= blockbase;
            }
            res.trim();
            return res;
        }
    }
    friend Bignum sqrt(const Bignum& a) {
        Bignum x0 = a, x1 = (a + 1) / 2;
        while (x1 < x0) {
            x0 = x1;
            x1 = (x1 + a / x1) / 2;
        }
        return x0;
    }
    friend Bignum pow(Bignum a, Bignum b) {
        if (b == Bignum(0)) return Bignum(1);
        Bignum T = pow(a, b / 2);
        if (b % 2 == 0) return T * T;
        return T * T * a;
    }
    friend Bignum pow(Bignum a, int b) {
        return pow(a, (Bignum(b)));
    }
    friend int log(Bignum a, int n) {
        int res = 0;
        while (a > Bignum(1)) {
            res++;
            a /= n;
        }
        return res;
    }
    template<class T> friend Bignum operator + (const T& v, const Bignum& a) {
        return a + v;
    }
    template<class T> friend Bignum operator - (const T& v, const Bignum& a) {
        return -a + v;
    }
    template<class T> friend Bignum operator * (const T& v, const Bignum& a) {
        return a * v;
    }
    template<class T> friend Bignum operator / (const T& v, const Bignum& a) {
        return Bignum(v) / a;
    }
    Bignum operator ++() {
        (*this) += 1;
        return *this;
    }
    Bignum operator ++(int) {
        (*this) += 1;
        return *this - 1;
    }
    Bignum operator --() {
        (*this) -= 1;
        return *this;
    }
    Bignum operator --(int) {
        (*this) -= 1;
        return *this + 1;
    }
};

int main() {
    Bignum n = Bignum("123456789");
    Bignum m = Bignum("987654321");
    cout << n * m << "\n";
    cout << 5 + m << "\n";
    cout << 5 - m << "\n";
    cout << 5 * m << "\n";
    cout << 5 / m << "\n";
    Bignum k = 1;
    cout << ++k << "\n";
    cout << k++ << "\n";
    cout << --k << "\n";
    cout << k-- << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
