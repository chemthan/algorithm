#include <bits/stdc++.h>
using namespace std;

template<class T> struct ChineseRemainder {
    static const int MAXN = 1e5 + 5;
    int n;
    T p[MAXN], r[MAXN];
    T b[MAXN], x[MAXN];
    
    void init() {
        n = 0;
    }
    void add(T pr, T rm) {
        p[n] = pr, r[n++] = rm;
    }
    T mulmod(T a, T b, T p) {
    	a %= p, b %= p;
    	T q = (T) ((long double) a * b / p);
        T r = a * b - q * p;
        while (r < 0) r += p;
        while (r >= p) r -= p;
        return r;
    }
    pair<T, T> euclid(T a, T b) {
    	if (!b) return make_pair(1, 0);
    	pair<T, T> r = euclid(b, a % b);
    	return make_pair(r.second, r.first - a / b * r.second);
    }
    T calc() {
    	T M = 1;
    	for (int i = 0; i < n; i++) M *= p[i];
    	T N = 0;
    	for (int i = 0; i < n; i++) {
    		b[i] = M / p[i];
    		x[i] = (euclid(b[i], p[i]).first % p[i] + p[i]) % p[i];
    		N += mulmod(r[i] * b[i], x[i], M);
    		if (N >= M) N -= M;
    	}
    	return N;
    }
};
ChineseRemainder<int> crt;

int main() {
	int p[] = {2, 3, 5};
	int r[] = {1, 2, 3};
	for (int i = 0; i < 3; i++) {
	    crt.add(p[i], r[i]);
	}
	cout << crt.calc() << "\n"; //Expected 23
	return 0;
}
