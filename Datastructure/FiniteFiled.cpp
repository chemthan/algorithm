#include <bits/stdc++.h>
using namespace std;

template<class T, T p, class mul, class dvd> struct FiniteField {
	T x;
	template<class G> T normalize(G x) {
		if (x >= 0 && x < p) return x;
		x %= p;
		if (x < 0) x += p;
		else if (x >= p) x -= p;
		return x;
	}
	FiniteField() {
		x = 0;
	}
	template<class G> FiniteField(const G& y) {
		x = normalize(y);
	}
	FiniteField(const FiniteField& rhs) {
		x = rhs.x;
	}
	template<class G> FiniteField operator () (const G& y) {
		x = normalize(y);
		return *this;
	}
	template<class G> FiniteField operator = (const G& y) {
		x = normalize(y);
		return *this;
	}
	FiniteField operator ++(int) {
		FiniteField res = *this;
		if ((++x) >= p) x -= p;
		return res;
	}
	FiniteField operator ++() {
		if ((++x) >= p) x -= p;
		return *this;
	}
	FiniteField operator --(int) {
		FiniteField res = *this;
		if ((--x) < 0) x += p;
		return res;
	}
	FiniteField operator --() {
		if ((--x) < 0) x += p;
		return *this;
	}
	template<class G> FiniteField operator += (const G& y) {
		if ((x += normalize(y)) >= p) x -= p;
		return *this;
	}
	template<class G> FiniteField operator -= (const G& y) {
		if ((x -= normalize(y)) < 0) x += p;
		return *this;
	}
	FiniteField operator += (const FiniteField& rhs) {
		if ((x += rhs.x) >= p) x -= p;
		return *this;
	}
	FiniteField operator -= (const FiniteField& rhs) {
		if ((x -= rhs.x) < 0) x += p;
		return *this;
	}
	FiniteField operator + (const FiniteField& rhs) const {
		FiniteField res;
		res.x = x + rhs.x;
		if (res.x >= p) res.x -= p;
		return res;
	}
	FiniteField operator - (const FiniteField& rhs) const {
		FiniteField res;
		res.x = x - rhs.x;
		if (res.x < 0) res.x += p;
		return res;
	}
	template<class G> FiniteField operator *= (const G& y) {
		x = mul()(x, normalize(y), p);
		return *this;
	}
	template<class G> FiniteField operator /= (const G& y) {
		x = dvd()(x, normalize(y), p);
		return *this;
	}
	template<class G> FiniteField operator * (const G& y) const {
		FiniteField res;
		res.x = mul()(x, res.normalize(y), p);
		return res;
	}
	template<class G> FiniteField operator / (const G& y) const {
		FiniteField res;
		res.x = dvd()(x, res.normalize(y), p);
		return res;
	}
	FiniteField operator * (const FiniteField& rhs) const {
		FiniteField res;
		res.x = mul()(x, rhs.x, p);
		return res;
	}
	FiniteField operator / (const FiniteField& rhs) const {
		FiniteField res;
		res.x = dvd()(x, rhs.x, p);
		return res;
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
		if (k == 0) return 1;
		T r = x, t = x; k--;
		while (k > 0) {
			if (k & 1) r = mul()(r, t, p);
			t = mul()(t, t, p);
			k >>= 1;
		}
		return r;
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
typedef FiniteField<int, 30, mul<int>, dvd<int> > FF;

int main() {
	FF a = 7;
	cout << a / 11 * 11 << "\n";
	cout << a + a << "\n";
	cout << a++ << "\n";
	cout << ++a << "\n";
	return 0;
}
