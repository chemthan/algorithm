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

const int maxn = 100000 + 10;
int n;
int a[maxn];

struct RMQ {
	static const int MAXN = 100000 + 10;
	static const int LOGN = 20;
	int n;
	int a[MAXN];
	int f[MAXN][LOGN];
	void build() {
		for (int i = 0; i < n; i++) f[i][0] = a[i];
		for (int l = 0, k; (k = 1 << l) < n; l++) {
			for (int i = 0; i + k < n; i++) {
				f[i][l + 1] = min(f[i][l], f[i + k][l]);
			}
		}
	}
	int query(int a, int b) {
		int l = a == b ? 0 : __lg(b - a);
		return min(f[a][l], f[b - (1 << l) + 1][l]);
	}
} rmq;

void solve() {
	int test; cin >> test;
	while (test--) {
		cin >> n;
		FOR(i, 0, n) cin >> a[i];
		rmq.n = n;
		FOR(i, 0, n) rmq.a[i] = a[i];
		rmq.build();
		int q; cin >> q;
		while (q--) {
			int l, r; cin >> l >> r; l--, r--;
			int cur = a[l];
			while (l < r) {
				int ll = l + 1, rr = r;
				while (ll < rr) {
					int mm = ll + rr >> 1;
					if (rmq.query(l + 1, mm) > cur) {
						ll = mm + 1;
					}
					else {
						rr = mm;
					}
				}
				cur %= rmq.query(l + 1, ll);
				l = ll;
			}
			cout << cur << "\n";
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
