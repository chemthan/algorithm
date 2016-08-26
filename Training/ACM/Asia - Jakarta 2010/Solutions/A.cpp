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

long long n;
long long x[2];
long long y[2];
long long z;

long long get(long long a, long long b) {
	long long res = n - 1;
	while (a != b) {
		a >>= 1, b >>= 1;
		res--;
	}
	return res;
}

void solve() {
	int test; cin >> test;
	int cnt = 1;
	while (test--) {
		cin >> n;
		FOR(i, 0, 2) cin >> x[i] >> y[i], x[i] += (1LL << n - 1) - 1;
		cin >> z;
		long long k = get(x[0], x[1]);
		long long mx = 0;
		FOR(u, 0, n) FOR(v, 0, n) {
			if (u == v && u < k) {
				long long a = abs(n - u - 1);
				long long b = abs(n - v - 1);
				int uu = u;
				int vv = v;
				if (y[0] > a) a++, uu++;
				if (y[1] > b) b++, vv++;
				if (a <= y[0] && b <= y[1] && n - uu - 1 >= y[0] - a && n - vv - 1 >= y[1] - b) {
					chkmax(mx, abs(uu - vv) + y[0] + y[1] - a - b);
				}
			}
			else if (u == k && v > k) {
				long long d = v - u;
				long long a = abs(n - u - 1);
				long long b = abs(n - v - 1);
				int uu = u;
				int vv = v;
				if (y[0] > a) a++, uu++, d--;
				if (a <= y[0] && b <= y[1] && n - uu - 1 >= y[0] - a && n - vv - 1 >= y[1] - b) {
					chkmax(mx, d + y[0] + y[1] - a - b);
				}
			}
			else if (u > k && v == k) {
				long long d = u - v;
				long long a = abs(n - u - 1);
				long long b = abs(n - v - 1);
				int uu = u;
				int vv = v;
				if (y[1] > b) b++, vv++, d--;
				if (a <= y[0] && b <= y[1] && n - uu - 1 >= y[0] - a && n - vv - 1 >= y[1] - b) {
					chkmax(mx, d + y[0] + y[1] - a - b);
				}
			}
			else {
				long long d = 0;
				if (u <= k && v <= k) {
					d += abs(u - v);
				}
				else {
					d += abs(u - k);
					d += abs(v - k);
				}
				long long a = abs(n - u - 1);
				long long b = abs(n - v - 1);
				if (a <= y[0] && b <= y[1] && n - u - 1 >= y[0] - a && n - v - 1 >= y[1] - b) {
					chkmax(mx, d + y[0] + y[1] - a - b);
				}
			}
		}
		if (mx > z) cout << "YES\n";
		else cout << "NO\n";
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
