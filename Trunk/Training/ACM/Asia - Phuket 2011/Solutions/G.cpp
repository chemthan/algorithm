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
inline ll isqrt(ll k) {ll r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}

const int maxn = 20 + 1;
int a[maxn][maxn];
int b[maxn][maxn];
int vis[maxn][maxn];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int xmn, xmx, ymn, ymx;
vii v;
int f[maxn];
pi pos[maxn];
pi des[maxn];
int ans;

int inside(int u, int v) {
	if (!(u >= 0 && u < 20)) return 0;
	if (!(v >= 0 && v < 20)) return 0;
	return a[u][v] && !vis[u][v];
}

void dfs(int u, int v) {
	vis[u][v] = 1;
	chkmin(xmn, u), chkmax(xmx, u);
	chkmin(ymn, v), chkmax(ymx, v);
	FOR(i, 0, 4) {
		int nu = u + dx[i];
		int nv = v + dy[i];
		if (inside(nu, nv)) {
			dfs(nu, nv);
		}
	}
}

pi find() {
	FOR(i, 0, 5) FOR(j, 0, 5) {
		if (!b[i][j]) {
			return mp(i, j);
		}
	}
}
int check(int u, int v, int n, int m) {
	if (u + n - 1 >= 5) return 0;
	if (v + m - 1 >= 5) return 0;
	FOR(i, u, u + n) FOR(j, v, v + m) {
		if (b[i][j]) {
			return 0;
		}
	}
	return 1;
}
int add(int u, int v, int n, int m) {
	FOR(i, u, u + n) FOR(j, v, v + m) {
		b[i][j] = 1;
	}
}
int rem(int u, int v, int n, int m) {
	FOR(i, u, u + n) FOR(j, v, v + m) {
		b[i][j] = 0;
	}
}

void go(int step) {
	if (step == sz(v)) {
		FOR(i, 0, 20 - 4) FOR(j, 0, 20 - 4) {
			int tot = 0;
			FOR(k, 0, sz(v)) {
				tot += abs(pos[k].fi - (i + des[k].fi)) + abs(pos[k].se - (j + des[k].se));
			}
			chkmin(ans, tot);
		}
		return;
	}
	FOR(i, 0, sz(v)) if (!f[i]) {
		f[i] = 1;
		pi r = find();
		if (check(r.fi, r.se, v[i].fi, v[i].se)) {
			des[i] = r;
			add(r.fi, r.se, v[i].fi, v[i].se);
			go(step + 1);
			rem(r.fi, r.se, v[i].fi, v[i].se);
		}
		f[i] = 0;
	}
}

void solve() {
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case " << it << ": ";
		ms(a, 0), ms(b, 0), ms(vis, 0);
		v.clear();
		FOR(i, 0, 20) {
			string s; cin >> s;
			FOR(j, 0, 20) {
				a[i][j] = s[j] == 'x';
			}
		}
		FOR(i, 0, 20) FOR(j, 0, 20) if (a[i][j] && !vis[i][j]) {
			xmn = ymn = +INF;
			xmx = ymx = -INF;
			dfs(i, j);
			pos[sz(v)] = mp(xmn, ymn);
			v.pb(mp(xmx - xmn + 1, ymx - ymn + 1));
		}
		ans = INF;
		go(0);
		if (ans == INF) {
			cout << "invalid data\n";
		}
		else {
			cout << ans << "\n";
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
