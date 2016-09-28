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

struct Lehmer {
	static const int MAXX = 100 + 10;
	static const int MAXY = 10000 + 10;
	static const int MAXN = 1000000 + 10;
	static const int MAXP = 100000 + 10;
	int np;
	int fl[MAXN], sp[MAXN];
	int pr[MAXP], cn[MAXN];
	long long f[MAXX][MAXY];

	Lehmer() {
		for (int i = 2; i < MAXN; i += 2) sp[i] = 2;
		for (int i = 3; i < MAXN; i += 2) if (!fl[i]) {
			sp[i] = i;
			for (int j = i; (long long) i * j < MAXN; j += 2) if (!fl[i * j]) {
				fl[i * j] = 1;
				sp[i * j] = i;
			}
		}
		np = 0;
		for (int i = 2; i < MAXN; i++) {
			if (sp[i] == i) {
				pr[np++] = i;
			}
			cn[i] = np;
		}
		for (int i = 0; i < MAXX; i++) {
			for (int j = 0; j < MAXY; j++) {
				if (!i) f[i][j] = j;
				else f[i][j] = f[i - 1][j] - f[i - 1][j / pr[i - 1]];
			}
		}
	}
	long long LegendreSum(long long m, int n) {
		if (!n) return m;
		if (pr[n - 1] >= m) return 1;
		if (m < MAXY && n < MAXX) return f[n][m];
		return LegendreSum(m, n - 1) - LegendreSum(m / pr[n - 1], n - 1);
	}
	long long calc(long long m) {
		if (m < MAXN) return cn[m];
		int x = sqrt(m + 0.9), y = cbrt(m + 0.9);
		int a = cn[y];
		long long res = LegendreSum(m, a) + a - 1;
		for (int i = a; pr[i] <= x; i++) res = res - calc(m / pr[i]) + calc(pr[i]) - 1;
		return res;
	}
} lehmer;

void solve() {
	long long n;
	while (cin >> n) {
		cout << lehmer.calc(n) << "\n";
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
