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

const int maxn = 1000 + 10;
int n, cnt;
vi adj[maxn];
vi radj[maxn];
vi adj2[maxn];
int vis[maxn];
int com[maxn];
int tot[maxn];
bitset<maxn> f[maxn];
int edge[maxn][maxn];
vi ver;

void dfs(int u) {
	vis[u] = 1;
	FOR(i, 0, sz(adj[u])) {
		int v = adj[u][i];
		if (!vis[v]) {
			dfs(v);
		}
	}
	ver.pb(u);
}

void rdfs(int u, int cnt) {
	vis[u] = 1, com[u] = cnt;
	tot[cnt]++;
	FOR(i, 0, sz(radj[u])) {
		int v = radj[u][i];
		if (!vis[v]) {
			rdfs(v, cnt);
		}
	}
}

void dfs2(int u) {
	vis[u] = 1;
	FOR(i, 0, sz(adj2[u])) {
		int v = adj2[u][i];
		if (!vis[v]) {
			dfs2(v);
		}
	}
	ver.pb(u);
}

void solve() {
	while (cin >> n) {
		if (!n) break;
		cnt = 0;
		FOR(i, 0, n) adj[i].clear(), radj[i].clear(), adj2[i].clear(), vis[i] = 0, f[i].reset();
		FOR(i, 0, n) FOR(j, 0, n) edge[i][j] = 0;
		ver.clear();
		FOR(i, 0, n - 1) {
			string s; cin >> s;
			FOR(j, 0, n - i - 1) {
				if (s[j] == '0') {
					adj[i].pb(i + j + 1);
					radj[i + j + 1].pb(i);
				}
				else {
					adj[i + j + 1].pb(i);
					radj[i].pb(i + j + 1);
				}
			}
		}
		FOR(i, 0, n) if (!vis[i]) dfs(i);
		fill_n(vis, n, 0);
		FORd(k, n, 0) {
			int i = ver[k];
			if (!vis[i]) {
				tot[cnt] = 0;
				rdfs(i, cnt++);
			}
		}
		FOR(u, 0, n) {
			FOR(i, 0, sz(adj[u])) {
				int v = adj[u][i];
				int x = com[u];
				int y = com[v];
				if (!edge[x][y] && x != y) {
					edge[x][y] = 1;
					adj2[x].pb(y);
				}
			}
		}
		ver.clear();
		n = cnt;
		fill_n(vis, n, 0);
		FOR(i, 0, n) if (!vis[i]) {
			dfs2(i);
		}
		FOR(i, 0, n) f[i][i] = 1;
		FOR(k, 0, n) {
			int u = ver[k];
			FOR(i, 0, sz(adj2[u])) {
				int v = adj2[u][i];
				f[v] |= f[u];
			}
		}
		int ans = 0;
		FOR(i, 0, n) {
			ans += (f[i].count() == n) * tot[i];
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
