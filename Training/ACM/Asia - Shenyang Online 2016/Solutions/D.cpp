#include <bits/stdc++.h>
using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define FORall(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define sz(a) int((a).size())
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define prec(n) fixed<<setprecision(n)
#define bit(n, i) (((n) >> (i)) & 1)
#define bitcount(n) __builtin_popcountll(n)
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
const int MOD = (int) 1e9 + 7;
const int INF = (int) 1e9;
const ll LINF = (ll) 1e18;
const ld PI = acos((ld) -1);
const ld EPS = 1e-9;
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
template<class T> inline int chkmin(T& a, const T& val) {return val < a ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
template<class T> inline T isqrt(T k) {T r = sqrt(k) + 1; while (r * r > k) r--; return r;}
template<class T> inline T icbrt(T k) {T r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}

typedef long long T;
const int MAXN = 100000 + 10;
long long p[MAXN], r[MAXN], b[MAXN], x[MAXN];
T mulmod64(T a, T b, T p) {
	T q = T((long double) a * b / p);
    T r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
}
T powmod64(T n, T k, T p) {
	if (!n) return 0;
	T r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = mulmod64(r, n, p);
		n = mulmod64(n, n, p);
	}
	return r;
}
pair<T, T> euclid(T a, T b) {
	if (b == 0) return make_pair(1, 0);
	pair<T, T> r = euclid(b, a % b);
	return make_pair(r.second, r.first - a / b * r.second);
}
T chineseRemainder(int n, int p[], int r[]) {
	T M = 1;
	for (int i = 0; i < n; i++) M *= p[i];
	T N = 0;
	for (int i = 0; i < n; i++) {
		b[i] = M / p[i];
		x[i] = (euclid(b[i], p[i]).first % p[i] + p[i]) % p[i];
		N += mulmod64(r[i] * b[i], x[i], M);
		if (N >= M) N -= M;
	}
	return N;
}

struct matrix {
	static const int MAXN = 3;
	int mod;
	int x[MAXN][MAXN];
	
	matrix(int mod) : mod(mod) {
		memset(x, 0, sizeof(x));
	}
	matrix unit() {
		matrix res(mod);
		for (int i = 0; i < MAXN; i++) res.x[i][i] = 1;
		return res;
	}
	matrix operator + (matrix A) {
		matrix res(mod);
		for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
			res.x[i][j] = x[i][j] + A.x[i][j];
			if (res.x[i][j] >= mod) res.x[i][j] -= mod;
		}
		return res;
	}
	matrix operator * (matrix A) {
		matrix res(mod);
		for (int i = 0; i < MAXN; i++) for (int k = 0; k < MAXN; k++) for (int j = 0; j < MAXN; j++) {
			res.x[i][j] = (res.x[i][j] + (long long) x[i][k] * A.x[k][j]) % mod;
		}
		return res;
	}
	matrix operator ^ (long long k) {
		if (!k) return unit();
		matrix res(mod), tmp(mod);
		for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
			res.x[i][j] = tmp.x[i][j] = x[i][j];
		}
		k--;
		while (k) {
			if (k & 1) res = res * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return res;
	}
	friend matrix sumpower(matrix A, long long k) {
		if (k == 1) return A;
		vector<int> bit;
		while (k) {
			bit.push_back(k & 1);
			k >>= 1;
		}
		matrix res = A, tmp = A;
		for (int i = bit.size() - 2; i >= 0; i--) {
			res = res + (res * tmp);
			tmp = tmp * tmp;
			if (bit[i] & 1) {
				tmp = tmp * A;
				res = res + tmp;
			}
		}
		return res;
	}
};

const int maxn = 100 + 10;
long long f[maxn];
long long g[maxn];
int pp[maxn];
int rr[maxn];

void solve() {
	f[0] = 0, f[1] = 1;
	FOR(i, 2, maxn) f[i] = f[i - 2] + 2 * f[i - 1];
	FOR(i, 1, maxn) g[i] = g[i - 1] + f[i] * f[i];
	int test; cin >> test;
	while (test--) {
		int n, y, x, s; cin >> n >> y >> x >> s; s++;
		map<int, int> hs;
		for (int i = 2; i * i <= s; i++) {
			if (s % i) continue;
			while (s % i == 0) hs[i]++, s /= i;
		}
		if (s > 1) hs[s]++;
		int tot = 0;
		FORall(it, hs) {
			int d = it->fi;
			int cnt = it->se;
			int pr = d;
			int phi = d - 1;
			FOR(i, 0, cnt - 1) phi *= d, pr *= d;
			if (__gcd(x, d) == 1) {
				matrix A(phi);
				A.x[0][0] = 5, A.x[0][1] = 5, A.x[0][2] = phi - 1;
				A.x[1][0] = 1;
				A.x[2][1] = 1;
				A = sumpower(A, (long long) n * y);
				int tmp = A.x[2][1];
				addmod(tmp, mult(A.x[2][0], 4, phi), phi);
				pp[tot] = pr;
				rr[tot] = fpow(x, tmp, pr);
				tot++;
			}
			else {
				if ((long long) n * y >= 10) {
					pp[tot] = pr;
					rr[tot] = 0;
				}
				else {
					pp[tot] = pr;
					rr[tot] = fpow(x, g[n * y], pr);
				}
				tot++;
			}
		}
		cout << chineseRemainder(tot, pp, rr) << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef _LOCAL_
	freopen("in.txt", "r", stdin); //freopen("out.txt", "w", stdout);
#endif
	solve();
#ifdef _LOCAL_
	//printf("\nTime elapsed: %dms", 1000 * clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
