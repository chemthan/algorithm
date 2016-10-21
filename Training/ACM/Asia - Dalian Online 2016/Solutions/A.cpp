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

struct matrix {
	static const int MAXN = 2;
	static const int MOD = (int) 1e9 + 7;
	int x[MAXN][MAXN];
	
	matrix() {
		memset(x, 0, sizeof(x));
	}
	matrix unit() {
		matrix res;
		for (int i = 0; i < MAXN; i++) res.x[i][i] = 1;
		return res;
	}
	matrix operator + (matrix A) {
		matrix res;
		for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
			res.x[i][j] = x[i][j] + A.x[i][j];
			if (res.x[i][j] >= MOD) res.x[i][j] -= MOD;
		}
		return res;
	}
	matrix operator * (matrix A) {
		matrix res;
		for (int i = 0; i < MAXN; i++) for (int k = 0; k < MAXN; k++) for (int j = 0; j < MAXN; j++) {
			res.x[i][j] = (res.x[i][j] + (long long) x[i][k] * A.x[k][j]) % MOD;
		}
		return res;
	}
	matrix operator ^ (long long k) {
		if (!k) return unit();
		matrix res, tmp;
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

vi dvs;
int phi(int d) {
	int res = 1;
	for (int i = 0; i < dvs.size() && dvs[i] <= d; i++) {
		if (d % dvs[i] == 0) {
			int cnt = 0;
			while (d % dvs[i] == 0) d /= dvs[i], cnt++;
			res *= dvs[i] - 1;
			FOR(j, 0, cnt - 1) res *= dvs[i];
		}
	}
	return res;
}

void solve() {
	matrix fib;
	fib.x[0][0] = fib.x[0][1] = fib.x[1][0] = 1;
	int n;
	while (cin >> n) {
		int ans = 0;
		dvs.clear();
		int tmp = n;
		for (int i = 2; i * i <= tmp; i++) {
			if (tmp % i) continue;
			dvs.pb(i);
			while (tmp % i == 0) tmp /= i;
		}
		if (tmp > 1) dvs.pb(tmp);
		sort(all(dvs));
		for (int i = 2; i * i <= n; i++) {
			if (n % i == 0) {
				int tmp = 0;
				int d = i;
				addmod(tmp, (fib ^ d).x[0][0]);
				if (d >= 2) {
					addmod(tmp, (fib ^ (d - 2)).x[0][0]);
				}
				addmod(ans, mult(tmp, phi(n / d)));
				if (n / i != i) {
					tmp = 0;
					d = n / i;
					addmod(tmp, (fib ^ d).x[0][0]);
					if (d >= 2) {
						addmod(tmp, (fib ^ (d - 2)).x[0][0]);
					}
					addmod(ans, mult(tmp, phi(n / d)));
				}
			}
		}
		addmod(ans, (fib ^ n).x[0][0]);
		if (n >= 2) {
			addmod(ans, (fib ^ (n - 2)).x[0][0]);
		}
		addmod(ans, phi(n));
		cout << mult(ans, inv(n)) << "\n";
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
