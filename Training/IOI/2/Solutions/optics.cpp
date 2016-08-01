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

const int maxn = 600000 + 10;
int n, bx, by;
int x[maxn];
int y[maxn];
char d[maxn];
map<int, int> dc;
vii gx[maxn << 1];
vii gy[maxn << 1];
vii hor[2], ver[2];
int vis[maxn][4];

void dfs(int u, int dir, int t) {
	vis[u][dir] = 1;
	if (dir == 0) { //north
		int k = upper_bound(all(gx[x[u]]), mp(y[u], INF)) - gx[x[u]].begin();
		if (k < sz(gx[x[u]])) {
			int v = gx[x[u]][k].se;
			ver[t].pb(mp(min(u, v), max(u, v)));
			if (d[v] == '\\') {
				int ndir = 3;
				if (!vis[v][ndir]) {
					dfs(v, ndir, t);
				}
			}
			else if (d[v] == '/') {
				int ndir = 1;
				if (!vis[v][ndir]) {
					dfs(v, ndir, t);
				}
			}
		}
	}
	else if (dir == 1) { //east
		int k = upper_bound(all(gy[y[u]]), mp(x[u], INF)) - gy[y[u]].begin();
		if (k < sz(gy[y[u]])) {
			int v = gy[y[u]][k].se;
			hor[t].pb(mp(min(u, v), max(u, v)));
			if (d[v] == '\\') {
				int ndir = 2;
				if (!vis[v][ndir]) {
					dfs(v, ndir, t);
				}
			}
			else if (d[v] == '/') {
				int ndir = 0;
				if (!vis[v][ndir]) {
					dfs(v, ndir, t);
				}
			}
		}
	}
	else if (dir == 2) { //south
		int k = lower_bound(all(gx[x[u]]), mp(y[u], -INF)) - gx[x[u]].begin() - 1;
		if (~k) {
			int v = gx[x[u]][k].se;
			ver[t].pb(mp(min(u, v), max(u, v)));
			if (d[v] == '\\') {
				int ndir = 1;
				if (!vis[v][ndir]) {
					dfs(v, ndir, t);
				}
			}
			else if (d[v] == '/') {
				int ndir = 3;
				if (!vis[v][ndir]) {
					dfs(v, ndir, t);
				}
			}
		}
	}
	else if (dir == 3) { //west
		int k = lower_bound(all(gy[y[u]]), mp(x[u], -INF)) - gy[y[u]].begin() - 1;
		if (~k) {
			int v = gy[y[u]][k].se;
			hor[t].pb(mp(min(u, v), max(u, v)));
			if (d[v] == '\\') {
				int ndir = 0;
				if (!vis[v][ndir]) {
					dfs(v, ndir, t);
				}
			}
			else if (d[v] == '/') {
				int ndir = 2;
				if (!vis[v][ndir]) {
					dfs(v, ndir, t);
				}
			}
		}
	}
}

int st[maxn << 1];
void upd(int p, int val) {
	for (st[p += maxn] += val; p > 1; ) p >>= 1, st[p] = st[p << 1] + st[p << 1 | 1];
}
int query(int l, int r) {
	int res = 0;
	for (l += maxn, r += maxn + 1; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += st[l++];
		if (r & 1) res += st[--r];
	}
	return res;
}

int compareX(pi u, pi v) {
	if (x[u.fi] != x[v.fi]) return x[u.fi] < x[v.fi];
	return u < v;
}

int query(vii& hor, vii& ver) {
	sort(all(ver), compareX);
	vector<pair<pi, int> > even;
	FOR(i, 0, sz(hor)) {
		int u = hor[i].fi;
		int v = hor[i].se;
		if (x[u] > x[v]) swap(u, v);
		if (x[u] + 1 < x[v]) {
			even.pb(mp(mp(x[u] + 1, y[u]), +1));
			even.pb(mp(mp(x[v], y[v]), -1));
		}
	}
	sort(all(even));
	fill_n(st, maxn << 1, 0);
	int ans = 0, ptr = 0;
	FOR(i, 0, sz(ver)) {
		int l = ver[i].fi;
		int r = ver[i].se;
		if (y[l] > y[r]) swap(l, r);
		while (ptr < sz(even) && even[ptr].fi.fi <= x[l]) {
			int k = even[ptr].fi.se;
			int v = even[ptr].se;
			upd(k, v);
			ptr++;
		}
		ans += query(y[l], y[r]);
	}
	return ans;
}

void solve() {
	if (fopen("optics.in", "r")) {
		freopen("optics.in", "r", stdin);
		freopen("optics.out", "w", stdout);
	}
	cin >> n;
	cin >> x[n] >> y[n], dc[x[n]], dc[y[n]];
	FOR(i, 0, n) cin >> x[i] >> y[i] >> d[i], dc[x[i]], dc[y[i]];
	dc[x[n + 1]], dc[y[n + 1]];
	dc[-INF << 1], dc[+INF << 1];
	int cnt = 0; FORall(it, dc) it->se = cnt++;
	FOR(i, 0, n + 2) {
		x[i] = dc[x[i]], y[i] = dc[y[i]];
		gx[x[i]].pb(mp(y[i], i));
		gy[y[i]].pb(mp(x[i], i));
	}
	int ptr = n + 2;
	FOR(i, 0, cnt) {
		x[ptr] = i, y[ptr] = 0;
		gx[i].pb(mp(y[ptr], ptr));
		ptr++;
		x[ptr] = i, y[ptr] = cnt - 1;
		gx[i].pb(mp(y[ptr], ptr));
		ptr++;
		x[ptr] = 0, y[ptr] = i;
		gy[i].pb(mp(x[ptr], ptr));
		ptr++;
		x[ptr] = cnt - 1, y[ptr] = i;
		gy[i].pb(mp(x[ptr], ptr));
		ptr++;
		sort(all(gx[i]));
		sort(all(gy[i]));
	}
	dfs(n + 1, 0, 0);
	FOR(i, 0, 4) dfs(n, i, 1);
	FOR(i, 0, 2) {
		sort(all(hor[i])); uni(hor[i]);
		sort(all(ver[i])); uni(ver[i]);
	}
	cout << query(hor[0], ver[1]) + query(hor[1], ver[0]) << "\n";
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
