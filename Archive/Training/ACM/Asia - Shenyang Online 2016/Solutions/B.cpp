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

const int maxn = 40000 + 10;
int n, q;
vii adj[maxn];
int c[maxn];
int size[maxn];
int lev[maxn];
int p[maxn];
int num[maxn];
int head[maxn];
int cnt;

struct Node {
	int fi, ls, cnt;
	Node() : fi(-1), ls(-1), cnt(0) {}
	Node(int fi, int ls, int cnt) : fi(fi), ls(ls), cnt(cnt) {}
	Node(const Node& rhs) : fi(rhs.fi), ls(rhs.ls), cnt(rhs.cnt) {}
} nil;

Node merge(Node x, Node y) {
	if (x.fi == nil.fi) return y;
	if (y.fi == nil.fi) return x;
	Node res;
	res.fi = x.fi, res.ls = y.ls;
	res.cnt = x.cnt + y.cnt;
	if (x.ls == y.fi) {
		res.cnt--;
	}
	return res;
}

Node st[maxn << 2];
int lz[maxn << 2];
void build(int p, int L, int R) {
	lz[p] = -1;
	if (L < R) {
		build(p << 1, L, L + R >> 1);
		build(p << 1 | 1, (L + R >> 1) + 1, R);
	}
}
void updlz(int p, int L, int R) {
	if (~lz[p]) {
		st[p].fi = st[p].ls = lz[p];
		st[p].cnt = 1;
		if (L < R) {
			lz[p << 1] = lz[p];
			lz[p << 1 | 1] = lz[p];
		}
		lz[p] = -1;
	}
}
void upd(int p, int l, int r, int L, int R, int val) {
	updlz(p, L, R);
	if (l > R || r < L) return;
	if (l <= L && r >= R) {
		lz[p] = val;
		updlz(p, L, R);
		return;
	}
	upd(p << 1, l, r, L, L + R >> 1, val);
	upd(p << 1 | 1, l, r, (L + R >> 1) + 1, R, val);
	st[p] = merge(st[p << 1], st[p << 1 | 1]);
}
Node query(int p, int l, int r, int L, int R) {
	updlz(p, L, R);
	if (l > R || r < L) return nil;
	if (l <= L && r >= R) return st[p];
	return merge(query(p << 1, l, r, L, L + R >> 1), query(p << 1 | 1, l, r, (L + R >> 1) + 1, R));
}

void dfs1(int u, int dad = -1) {
	size[u] = 1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].fi;
		int w = adj[u][i].se;
		if (v != dad) {
			p[v] = u, lev[v] = lev[u] + 1;
			c[v] = w;
			dfs1(v, u);
			size[u] += size[v];
		}
	}
}
void dfs2(int u, int h = 0, int dad = -1) {
	num[u] = cnt++, head[u] = h;
	pair<int, int> best = make_pair(-1, -1);
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].fi;
		if (v != dad) {
			best = max(best, make_pair(size[v], v));
		}
	}
	if (~best.second) {
		dfs2(best.second, h, u);
	}
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].fi;
		if (v != dad && v != best.second) {
			dfs2(v, v, u);
		}
	}
}
void upd(int u, int v, int val) {
	int hu = head[u], hv = head[v];
	while (hu != hv) {
		if (lev[hu] < lev[hv]) swap(u, v), swap(hu, hv);
		upd(1, num[hu], num[u], 0, n - 1, val);
		u = p[hu], hu = head[u];
	}
	if (lev[u] > lev[v]) swap(u, v);
	upd(1, num[u] + 1, num[v], 0, n - 1, val);
}
Node query(int u, int v) {
	Node lres = nil, rres = nil;
	int hu = head[u], hv = head[v];
	int dir = 1;
	while (hu != hv) {
		if (lev[hu] < lev[hv]) swap(u, v), swap(hu, hv), dir ^= 1;
		if (dir) {
			lres = merge(query(1, num[hu], num[u], 0, n - 1), lres);
		}
		else {
			rres = merge(query(1, num[hu], num[u], 0, n - 1), rres);
		}
		u = p[hu], hu = head[u];
	}
	if (lev[u] > lev[v]) swap(u, v), dir ^= 1;
	if (dir) {
		rres = merge(query(1, num[u] + 1, num[v], 0, n - 1), rres);
	}
	else {
		lres = merge(query(1, num[u] + 1, num[v], 0, n - 1), lres);
	}
	swap(lres.fi, lres.ls);
	return merge(lres, rres);
}

void solve() {
	while (cin >> n >> q) {
		cnt = 0;
		FOR(i, 0, n) adj[i].clear();
		FOR(i, 0, n - 1) {
			int u, v, w; cin >> u >> v >> w; u--, v--;
			adj[u].pb(mp(v, w)), adj[v].pb(mp(u, w));
		}
		dfs1(0), dfs2(0);
		build(1, 0, n - 1);
		FOR(i, 0, n) upd(1, num[i], num[i], 0, n - 1, c[i]);
		while (q--) {
			string op; cin >> op;
			if (op == "Change") {
				int u, v, w; cin >> u >> v >> w; u--, v--;
				upd(u, v, w);
			}
			else {
				int u, v; cin >> u >> v; u--, v--;
				cout << query(u, v).cnt << "\n";
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
