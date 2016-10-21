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

const int maxn = 5000 + 10;
int n, m;
vii adj[maxn];
vector<pair<int, pi> > edge;
int dj[maxn];
int sz[maxn];
int mn[maxn];
int tt[maxn];
set<int>* s[maxn];
vi change;

void init() {
	FOR(i, 0, n) {
		dj[i] = i;
		sz[i] = 1;
		mn[i] = INF;
		tt[i] = sz(adj[i]);
		if (s[i]) s[i]->clear();
		s[i] = new set<int>();
		s[i]->insert(i);
	}
}
int find(int u) {
	return dj[u] == u ? dj[u] : dj[u] = find(dj[u]);
}
void join(int u, int v, int w) {
	int p = find(u);
	int q = find(v);
	if (p != q) {
		if (tt[p] > tt[q]) swap(p, q);
		dj[p] = q;
		sz[q] += sz[p];
		tt[q] += tt[p];
		chkmin(mn[q], mn[p]);
		chkmin(mn[q], w);
		FORall(it, *s[p]) {
			int u = *it;
			FOR(i, 0, sz(adj[u])) {
				int v = adj[u][i].fi;
				int w = adj[u][i].se;
				if (find(u) == find(v)) {
					chkmin(mn[q], w);
				}
			}
		}
		if (sz(*s[p]) > sz(*s[q])) {
			swap(s[p], s[q]);
		}
		FORall(it, *s[p]) {
			s[q]->insert(*it);
		}
		change.pb(q);
	}
}

void solve() {
	int test; cin >> test;
	while (test--) {
		cin >> n >> m;
		FOR(i, 0, n) adj[i].clear();
		edge.clear();
		FOR(i, 0, m) {
			int u, v, w; cin >> u >> v >> w; u--, v--;
			edge.pb(mp(w, mp(u, v)));
			adj[u].pb(mp(v, w));
			adj[v].pb(mp(u, w));
		}
		init();
		sort(all(edge)), reverse(all(edge));
		long long ans = 0;
		int ptr = 0;
		FOR(i, 0, m) {
			while (ptr < m && edge[ptr].fi >= edge[i].fi) {
				int u = edge[ptr].se.fi;
				int v = edge[ptr].se.se;
				int w = edge[ptr].fi;
				join(u, v, w);
				ptr++;
			}
			sort(all(change)), uni(change);
			vi nchange;
			FOR(j, 0, sz(change)) {
				int u = change[j];
				if (dj[u] == u && mn[u] == edge[i].fi) {
					ans += sz[u];
				}
				else if (dj[u] == u) {
					nchange.pb(u);
				}
			}
			change = nchange;
		}
		cout << ans << "\n";
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
