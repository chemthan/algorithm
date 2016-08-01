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

const int maxn = 20000 + 10;
const int mod = 1234567;
int n, m;
int p[maxn];
vii adj[maxn];
map<int, int> f[maxn];
map<int, int> g[maxn];
map<int, int> h[maxn];
map<int, int> dp1[maxn];
int dp2[maxn * 50];
int vis[maxn * 50];
vi nxt[maxn * 50];
int bg[maxn * 50];

int st[maxn << 1];
void upd(int p, int val) {
	for (st[p += n] = val; p > 1; ) p >>= 1, st[p] = mult(st[p << 1], st[p << 1 | 1], mod);
}

void solve(int u, int hs) {
	vii his;
	for (int i = bg[hs]; i < sz(adj[u]) && adj[u][i].fi == hs; i++) {
		int v = adj[u][i].se;
		his.pb(mp(v, st[v + n]));
		upd(v, dp1[v][hs]);
	}
	dp2[hs] = st[1];
	FOR(i, 0, sz(nxt[hs])) {
		solve(u, nxt[hs][i]);
	}
	FOR(i, 0, sz(his)) {
		int v = his[i].fi;
		int w = his[i].se;
		upd(v, w);
	}
}

void solve() {
	if (fopen("code.in", "r")) {
		freopen("code.in", "r", stdin);
		freopen("code.out", "w", stdout);
	}
	cin >> n >> m;
	FOR(i, 1, n) {
		int u; cin >> u;
		p[i] = u, adj[u].pb(mp(0, i));
	}
	FOR(i, 0, n) g[i][0], h[i][0];
	FOR(i, 0, m) {
		int u; string s; cin >> u >> s;
		int hs = 0;
		FOR(j, 0, 5) hs <<= 4, hs |= s[j] - '0' + 1;
		f[u][hs];
		for (int j = 4; j > 0; j--) {
			hs = hs & (1 << 4 * j) - 1;
			adj[p[u]].pb(mp(hs, u));
			g[p[u]][hs], h[u][hs];
			u = p[u];
		}
	}
	FOR(i, 0, n) sort(all(adj[i])), uni(adj[i]);
	fill_n(st, n << 1, 1);
	FORd(i, n, 0) {
		vi his;
		FORall(it, g[i]) {
			int hs = it->fi;
			while (hs && !vis[hs]) {
				vis[hs] = 1, his.pb(hs);
				nxt[hs >> 4].pb(hs);
				hs >>= 4;
			}
		}
		FOR(j, 0, sz(adj[i])) {
			if (!j || adj[i][j].fi != adj[i][j - 1].fi) {
				bg[adj[i][j].fi] = j;
			}
		}
		solve(i, 0);
		FOR(j, 0, sz(his)) {
			int hs = his[j];
			vis[hs] = 0;
			nxt[hs >> 4].clear();
		}
		FORall(it, h[i]) {
			int hs = it->fi;
			int d = 0, tmp = hs;
			while (tmp) tmp >>= 4, d++;
			FOR(j, 0, 10) {
				int nhs = hs + (1 << 4 * d) * (j + 1);
				if (!f[i].count(nhs)) {
					while (!g[i].count(nhs)) nhs >>= 4;
					addmod(dp1[i][hs], dp2[nhs], mod);
				}
			}
		}
	}
	int ans = fpow(10, n, mod);
	submod(ans, dp1[0][0], mod);
	cout << ans << "\n";
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
