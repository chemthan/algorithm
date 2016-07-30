#include <bits/stdc++.h>
using namespace std;

const int BASE = 1000000000;
const int NBLOCK = 9;
struct Bigint {
	vector<int> data;
	Bigint() {data.push_back(0);}
	Bigint(long long x) {
		if (!x) data.push_back(0);
		while (x) data.push_back(x % BASE), x /= BASE;
	}
	void trim() {while (data.size() > 1 && !data.back()) data.pop_back();}
	int& operator[] (int i) {return data[i];}
	int len() {return data.size();}
	int iszero() const {return data.empty() || (data.size() == 1 && !data[0]);}
};
Bigint operator + (Bigint a, Bigint b) {
	if (a.len() < b.len()) swap(a, b);
	Bigint c; c.data = a.data, c.data.push_back(0);
	int r = 0;
	for (int i = 0; i < c.len(); i++) {
		c[i] += ((i < b.len()) ? b[i] : 0) + r;
		if ((r = (c[i] >= BASE))) c[i] -= BASE;
	}
	c.trim();
	return c;
}
Bigint operator * (Bigint a, int m) {
	long long r = 0;
	for (int i = 0; i < a.len(); i++) {
		r += (long long) a[i] * m;
		a[i] = r % BASE;
		r /= BASE;
	}
	while (r) a.data.push_back(r % BASE), r /= BASE;
	a.trim();
	return a;
}
pair<Bigint, int> divmod(Bigint a, int m) {
	long long r = 0;
	for (int i = a.len() - 1; i >= 0; i--) {
		r = r * BASE + a[i];
		a[i] = r / m;
		r %= m;
	}
	a.trim();
	return make_pair(a, (int) r);
}
Bigint operator / (Bigint a, int m) {
	return divmod(a, m).first;
}
int operator % (Bigint a, int m) {
	return divmod(a, m).second;
}
ostream& operator << (ostream& stream, const Bigint& a) {
	stream << (a.data.empty() ? 0 : a.data.back());
	for (int i = (int) a.data.size() - 2; i >= 0; i--) stream << setw(NBLOCK) << setfill('0') << a.data[i];
	return stream;
}

int main() {
	Bigint a(1);
	for (int i = 1; i <= 20; i++) a = a * i;
	cout << a << "\n"; //Expected: 2432902008176640000
	return 0;
}
