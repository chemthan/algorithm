#include <bits/stdc++.h>
using namespace std;

template<class T, class mul, class dvd, class mod> struct FiniteField {
    T x;
    template<class G> T normalize(G x) {
        T p = mod().get();
        if (x >= 0 && x < p) return x;
        x %= p;
        if (x < 0) x += p;
        else if (x >= p) x -= p;
        return x;
    }
    FiniteField() : x(0) {}
    template<class G> FiniteField(const G& y) {
        x = normalize(y);
    }
    FiniteField(const FiniteField& rhs) : x(rhs.x) {
    }
    template<class G> FiniteField operator = (const G& y) {
        x = normalize(y);
        return *this;
    }
    int operator == (const FiniteField& rhs) const {
        return x == rhs.x;
    }
    int operator != (const FiniteField& rhs) const {
        return x != rhs.x;
    }
    int operator < (const FiniteField& rhs) const {
        return x < rhs.x;
    }
    FiniteField operator ++(int) {
        T p = mod().get();
        FiniteField res = *this;
        if ((++x) >= p) x -= p;
        return res;
    }
    FiniteField operator ++() {
        T p = mod().get();
        if ((++x) >= p) x -= p;
        return *this;
    }
    FiniteField operator --(int) {
        T p = mod().get();
        FiniteField res = *this;
        if ((--x) < 0) x += p;
        return res;
    }
    FiniteField operator --() {
        T p = mod().get();
        if ((--x) < 0) x += p;
        return *this;
    }
    template<class G> FiniteField operator += (const G& y) {
        T p = mod().get();
        if ((x += normalize(y)) >= p) x -= p;
        return *this;
    }
    template<class G> FiniteField operator -= (const G& y) {
        T p = mod().get();
        if ((x -= normalize(y)) < 0) x += p;
        return *this;
    }
    FiniteField operator += (const FiniteField& rhs) {
        T p = mod().get();
        if ((x += rhs.x) >= p) x -= p;
        return *this;
    }
    FiniteField operator -= (const FiniteField& rhs) {
        T p = mod().get();
        if ((x -= rhs.x) < 0) x += p;
        return *this;
    }
    FiniteField operator + (const FiniteField& rhs) const {
        T p = mod().get();
        FiniteField res;
        res.x = x + rhs.x;
        if (res.x >= p) res.x -= p;
        return res;
    }
    FiniteField operator - (const FiniteField& rhs) const {
        T p = mod().get();
        FiniteField res;
        res.x = x - rhs.x;
        if (res.x < 0) res.x += p;
        return res;
    }
    template<class G> FiniteField operator *= (const G& y) {
        T p = mod().get();
        x = mul()(x, normalize(y), p);
        return *this;
    }
    template<class G> FiniteField operator /= (const G& y) {
        T p = mod().get();
        x = dvd()(x, normalize(y), p);
        return *this;
    }
    FiniteField operator *= (const FiniteField& rhs) {
        T p = mod().get();
        x = mul()(x, rhs.x, p);
        return *this;
    }
    FiniteField operator /= (const FiniteField& rhs) {
        T p = mod().get();
        x = dvd()(x, rhs.x, p);
        return *this;
    }
    template<class G> FiniteField operator * (const G& y) const {
        T p = mod().get();
        FiniteField res;
        res.x = mul()(x, res.normalize(y), p);
        return res;
    }
    template<class G> FiniteField operator / (const G& y) const {
        T p = mod().get();
        FiniteField res;
        res.x = dvd()(x, res.normalize(y), p);
        return res;
    }
    FiniteField operator * (const FiniteField& rhs) const {
        T p = mod().get();
        FiniteField res;
        res.x = mul()(x, rhs.x, p);
        return res;
    }
    FiniteField operator / (const FiniteField& rhs) const {
        T p = mod().get();
        FiniteField res;
        res.x = dvd()(x, rhs.x, p);
        return res;
    }
    template<class G> friend FiniteField operator + (const G& y, const FiniteField& rhs) {
        FiniteField res;
        res.x = res.normalize(y);
        return res + rhs;
    }
    template<class G> friend FiniteField operator - (const G& y, const FiniteField& rhs) {
        FiniteField res;
        res.x = res.normalize(y);
        return res - rhs;
    }
    template<class G> friend FiniteField operator * (const G& y, const FiniteField& rhs) {
        FiniteField res;
        res.x = res.normalize(y);
        return res * rhs;
    }
    template<class G> friend FiniteField operator / (const G& y, const FiniteField& rhs) {
        FiniteField res;
        res.x = res.normalize(y);
        return res / rhs;
    }
    template<class G> FiniteField operator ^= (G k) {
        T p = mod().get();
        if (k == 0) {
            x = 1;
            return *this;
        }
        T t = x; k--;
        while (k > 0) {
            if (k & 1) x = mul()(x, t, p);
            t = mul()(t, t, p);
            k >>= 1;
        }
        return *this;
    }
    template<class G> FiniteField operator ^ (G k) const {
        T p = mod().get();
        if (k == 0) return 1;
        T r = x, t = x; k--;
        while (k > 0) {
            if (k & 1) r = mul()(r, t, p);
            t = mul()(t, t, p);
            k >>= 1;
        }
        return r;
    }
    friend istream& operator >> (istream& is, FiniteField& rhs) {
        is >> rhs.x;
        rhs.x = rhs.normalize(rhs.x);
        return is;
    }
    friend ostream& operator << (ostream& os, const FiniteField& rhs) {
        os << rhs.x;
        return os;
    }
};
template<class T> class mul {
public:
    T operator () (const T& x, const T& y, const T& p) {
        return (long long) x * y % p;
    }
};
template<class T> class dvd {
public:
    T operator () (const T& x, const T& y, const T& p) {
        pair<T, T> r = euclid(y, p);
        return mul<T>()(x, (r.first % p + p) % p, p);
    }
private:
    pair<T, T> euclid(T a, T b) {
        if (b == 0) return make_pair(1, 0);
        pair<T, T> r = euclid(b, a % b);
        return make_pair(r.second, r.first - a / b * r.second);
    }
};
template<class T> class mod {
public:
    T get() {
        return (T) 1e9 + 7;
    }
};
typedef FiniteField<int, mul<int>, dvd<int>, mod<int> > FF;

int main() {
    FF a = 7, b = 3;
    cout << a / 11 * 11 << "\n";
    cout << a + a << "\n";
    cout << a++ << "\n";
    cout << ++a << "\n";
    a *= b;
    cout << a << "\n";
    a /= b;
    cout << a << "\n";
    return 0;
}
