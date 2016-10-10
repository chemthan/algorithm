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

const int maxn = 10;
int n;
long long ar[2][maxn][maxn];
int vis[maxn][maxn][maxn][maxn];
pair<int, string> ans;

int dx[] = {0, +1, 0, -1};
int dy[] = {-1, 0, +1, 0};
string dir[] = {"L", "D", "R", "U"};
int od[] = {1, 0, 2, 3};

int inside(int u, int v, int ix) {
	if (!(u >= 0 && u < 6)) return 0;
	if (!(v >= 0 && v < 6)) return 0;
	return bit(ar[ix][u][v], 4);
}

void work() {
	int x[2] = {}, y[2] = {}, z[2] = {}, t[2] = {};
	FOR(it, 0, 2) {
		FOR(i, 0, 6) FOR(j, 0, 6) {
			if (bit(ar[it][i][j], 5)) {
				x[it] = i;
				y[it] = j;
			}
			if (bit(ar[it][i][j], 6)) {
				z[it] = i;
				t[it] = j;
			}
		}
	}
	ms(vis, 0); ans = mp(INF, "");
	queue<pair<pi, pair<pi, string> > > que;
	que.push(mp(mp(x[0], y[0]), mp(mp(x[1], y[1]), "")));
	vis[x[0]][y[0]][x[1]][y[1]] = 1;
	while (sz(que)) {
		int a = que.front().fi.fi;
		int b = que.front().fi.se;
		int c = que.front().se.fi.fi;
		int d = que.front().se.fi.se;
		string cmd = que.front().se.se;
		que.pop();
		if (mp(a, b) == mp(z[0], t[0]) && mp(c, d) == mp(z[1], t[1])) {
			chkmin(ans, mp(sz(cmd), cmd));
		}
		FOR(j, 0, 4) {
			int i = od[j];
			int na, nb, nc, nd;
			if (bit(ar[0][a][b], i)) {
				na = a;
				nb = b;
			}
			else {
				na = a + dx[i];
				nb = b + dy[i];
				if (!inside(na, nb, 0)) continue;
			}
			if (bit(ar[1][c][d], i)) {
				nc = c;
				nd = d;
			}
			else {
				nc = c + dx[i];
				nd = d + dy[i];
				if (!inside(nc, nd, 1)) continue;
			}
			if (!vis[na][nb][nc][nd]) {
				vis[na][nb][nc][nd] = 1;
				que.push(mp(mp(na, nb), mp(mp(nc, nd), cmd + dir[i])));
			}
		}
	}
	if (ans.fi == INF) {
		cout << "-1\n";
	}
	else {
		cout << ans.se << "\n";
	}
}

void solve() {
	cin >> n;
	FOR(it, 0, n) {
		FOR(i, 0, 6) FOR(j, 0, 6) cin >> ar[it % 2][i][j];
		if (it) {
			work();
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
