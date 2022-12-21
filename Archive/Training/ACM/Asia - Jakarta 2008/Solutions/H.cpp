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
template<class T> inline int chkmin(T& a, const T& val) {return a > val ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
inline ll isqrt(ll k) {ll r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}

const int maxm = 10000 + 10;
int f[maxm];

int calc(int a, int n, int m) {
	if (m == 1) return 0;
	if (n == 0) return 1 % m;
	if (n == 1) return a % m;
	if (n == 2) return fpow(a, a, m);
	if (n == 3 && a <= 5) return fpow(a, fpow(a, a), m);
	if (n == 4 && a == 2) return fpow(a, 16, m);
	int r = calc(a, n - 1, f[m]);
	r += 2 * maxm - (2 * maxm % f[m]);
	return fpow(a, r, m);
}

int gg(int a, int b, int n) {
	if (n == 0) return min(20, b + 1);
	if (n == 1 && b == 0) return min(20, a);
	if (n == 2 && b == 0) return 0;
	if (n >= 3 && b == 0) return 1;
	if (n == 1) return min(20, a + b);
	if (n == 2) return min(20, a * b);
	if (n == 3) return (int) round(min(20.0, pow(a, min(5, b))));
	if (n == 4) {
		if (b == 1) return min(20, a);
		if (b == 2) return (int) round(min(20.0, pow(a, min(5, a))));
		if (a == 2 && b == 2) return 4;
		if (a == 2 && b == 3) return 16;
		if (a == 3 && b == 2) return 9;
		if (a == 4 && b == 2) return 16;
		return 20;
	}
	if (gg(a, b - 1, n) >= 20) return 20;
	return gg(a, gg(a, b - 1, n), n - 1);
}

int ff(int a, int b, int n, int m) {
	if (n == 4) return calc(a, b, m);
	if (b == 0) return 1 % m;
	return ff(a, gg(a, b - 1, n), n - 1, m);
}

void solve() {
	FOR(i, 0, maxm) f[i] = i;
	FOR(i, 1, maxm) {
		for (int j = i + i; j < maxm; j += i) {
			f[j] -= f[i];
		}
	}
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case #" << it << ": ";
		int m, n, a, b; cin >> m >> n >> a >> b;
		if (n == 0) {
			cout << (b + 1) % m << "\n";
		}
		else if (n == 1 && b == 0) {
			cout << a % m << "\n";
		}
		else if (n == 2 && b == 0) {
			cout << 0 % m << "\n";
		}
		else if (n >= 3 && b == 0) {
			cout << 1 % m << "\n";
		}
		else if (n == 1) {
			cout << (a + b) % m << "\n";
		}
		else if (n == 2) {
			cout << a * b % m << "\n";
		}
		else if (n == 3) {
			cout << fpow(a, b, m) << "\n";
		}
		else {
			if (a == 0) {
				if (b & 1) {
					cout << 0 % m << "\n";
				}
				else {
					cout << 1 % m << "\n";
				}
			}
			else if (a == 1) {
				cout << 1 % m << "\n";
			}
			else {
				if (n > 4 && b < 20) {
					cout << ff(a, b, n, m) << "\n";
				}
				else {
					cout << calc(a, min(20, b), m) << "\n";
				}
			}
		}
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
