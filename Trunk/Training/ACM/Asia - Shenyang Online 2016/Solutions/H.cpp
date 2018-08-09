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

struct HopcroftKarp {
	static const int MAXV = 1000 + 10;
	static const int MAXE = 1000000 + 10;
	int nx, ny, E, adj[MAXE], next[MAXE], last[MAXV], run[MAXV], level[MAXV], que[MAXV], matx[MAXV], maty[MAXV];
	void init(int _nx, int _ny) {
		nx = _nx; ny = _ny;
		E = 0; memset(last, -1, sizeof(last));
		memset(matx, -1, sizeof(matx)); memset(maty, -1, sizeof(maty));
	}
	void add(int x, int y) {
		adj[E] = y; next[E] = last[x]; last[x] = E++;
	}
	bool bfs() {
		int qsize = 0;
		for (int x = 1; x <= nx; x++) if (matx[x] != -1) level[x] = -1;
		else {
			level[x] = 0;
			que[qsize++] = x;
		}
		bool found = false;
		for (int i = 0; i < qsize; i++) {
			for (int x = que[i], e = last[x]; e != -1; e = next[e]) {
				int y = adj[e];
				if (maty[y] == -1) found = true;
				else if (level[maty[y]] == -1) {
					level[maty[y]] = level[x] + 1;
					que[qsize++] = maty[y];
				}
			}
		}
		return found;
	}
	int dfs(int x) {
		for (int &e = run[x]; e != -1; e = next[e]) {
			int y = adj[e];
			if (maty[y] == -1 || (level[maty[y]] == level[x] + 1 && dfs(maty[y]))) {
				matx[x] = y;
				maty[y] = x;
				return 1;
			}
		}
		return 0;
	}
	int maxmat() {
		int total = 0;
		while (bfs()) {
			for (int x = 1; x <= nx; x++) run[x] = last[x];
			for (int x = 1; x <= nx; x++) if (matx[x] == -1) total += dfs(x);
		}
		return total;
	}
} hopkarp;

const int maxn = 500 + 10;
int n, m, k;
int d[maxn][maxn];
int vis[maxn];
int col[maxn];
int found;
vi ver;

void dfs(int u) {
	vis[u] = 1;
	ver.pb(u);
	FOR(i, 0, n) if (i != u) {
		if (d[u][i] <= k) {
			if (!vis[i]) {
				col[i] = col[u] ^ 1;
				dfs(i);
			}
			else if (col[i] == col[u]) {
				found = 1;
			}
		}
	}
}

vi work() {
	int cnt1 = 0, cnt2 = 0;
	vi v1, v2;
	FOR(i, 0, sz(ver)) {
		int u = ver[i];
		if (col[u]) {
			v1.pb(u);
			cnt1++;
		}
		else {
			v2.pb(u);
			cnt2++;
		}
	}
	sort(all(v1)), sort(all(v2));
	if (cnt1 != cnt2) {
		found = 1;
		return vi();
	}
	hopkarp.init(cnt1, cnt2);
	FOR(i, 0, cnt1) FOR(j, 0, cnt2) {
		if (d[v1[i]][v2[j]] <= k) {
			hopkarp.add(i + 1, j + 1);
		}
	}
	if (hopkarp.maxmat() != cnt1) {
		found = 1;
		return vi();
	}
	return min(v1, v2);
}

void solve() {
	int test; cin >> test;
	while (test--) {
		cin >> n >> m >> k;
		FOR(i, 0, n) FOR(j, 0, n) d[i][j] = INF;
		fill_n(vis, n, 0);
		FOR(i, 0, m) {
			int u, v, w; cin >> u >> v >> w; u--, v--;
			d[u][v] = d[v][u] = w;
		}
		FOR(l, 0, n) FOR(i, 0, n) FOR(j, 0, n) {
			chkmin(d[i][j], d[i][l] + d[l][j]);
		}
		found = 0;
		vi res;
		FOR(i, 0, n) if (!vis[i]) {
			ver.clear();
			dfs(i);
			vi rr = work();
			res.insert(res.end(), all(rr));
			if (found) {
				break;
			}
		}
		if (found) {
			cout << "Impossible\n";
		}
		else {
			cout << sz(res) << "\n";
			FOR(i, 0, sz(res)) cout << res[i] + 1 << " \n"[i == sz(res) - 1];
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
