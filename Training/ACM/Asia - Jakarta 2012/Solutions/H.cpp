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

const int maxn = 100000 + 10;
int n, q, w, h;
int x[maxn];
int y[maxn];

set<pi> st[maxn << 2];
void add(int p, int i, int L, int R, pi val) {
	if (i < L || i > R) return;
	st[p].insert(val);
	if (L < R) {
		add(p << 1, i, L, L + R >> 1, val);
		add(p << 1 | 1, i, (L + R >> 1) + 1, R, val);
	}
}
void rem(int p, int i, int L, int R, pi val) {
	if (i < L || i > R) return;
	st[p].erase(val);
	if (L < R) {
		rem(p << 1, i, L, L + R >> 1, val);
		rem(p << 1 | 1, i, (L + R >> 1) + 1, R, val);
	}
}
int query(int p, int l, int r, int L, int R, int x, int y) {
	if (l > R || r < L) return -1;
	if (l <= L && r >= R) {
		set<pi>::iterator it = st[p].lower_bound(mp(x, -INF));
		if (it == st[p].end() || it->fi > y) return -1;
		return it->se;
	}
	int res = query(p << 1, l, r, L, L + R >> 1 , x, y);
	if (~res) return res;
	return query(p << 1 | 1, l, r, (L + R >> 1) + 1, R, x, y);
}

void solve() {
	int test; scanf("%d", &test);
	FOR(it, 1, test + 1) {
		printf("Case #%d:\n", it);
		scanf("%d%d%d%d", &n, &q, &w, &h);
		FOR(i, 0, maxn << 2) st[i].clear();
		FOR(i, 0, n) {
			scanf("%d%d", x + i, y + i);
			add(1, x[i] + y[i], 0, maxn - 1, mp(x[i] - y[i], i));
		}
		while (q--) {
			int xk, yk, ek, a, b, c, d, e, f;
			scanf("%d%d%d%d%d%d%d%d%d", &xk, &yk, &ek, &a, &b, &c, &d, &e, &f);
			vi his;
			while (1) {
				int r = query(1, max(0, xk + yk - ek), min(maxn - 1, xk + yk + ek), 0, maxn - 1, xk - yk - ek, xk - yk + ek);
				if (~r) {
					rem(1, x[r] + y[r], 0,  maxn - 1, mp(x[r] - y[r], r));
					int X = 0;
					addmod(X, mult(x[r], a, w), w);
					addmod(X, mult(y[r], b, w), w);
					addmod(X, mult(r + 1, c, w), w);
					int Y = 0;
					addmod(Y, mult(x[r], d, h), h);
					addmod(Y, mult(y[r], e, h), h);
					addmod(Y, mult(r + 1, f, h), h);
					x[r] = X, y[r] = Y;
					his.pb(r);
				}
				else {
					break;
				}
			}
			FOR(i, 0, sz(his)) {
				int r = his[i];
				add(1, x[r] + y[r], 0,  maxn - 1, mp(x[r] - y[r], r));
			}
		}
		FOR(i, 0, n) printf("%d %d\n", x[i], y[i]);
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
