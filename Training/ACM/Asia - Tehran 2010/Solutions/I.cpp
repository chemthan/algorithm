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
int n, m;
int a[maxn][maxn];
int cnt1[maxn][maxn];
int cnt2[maxn][maxn];
int cnt3[maxn][maxn];
pi nxt[maxn][maxn];

void solve() {
	string s;
	while (cin >> s) {
		n = 0;
		int u, v;
		while (1) {
			if (s == "$") break;
			m = sz(s);
			FOR(i, 0, m) {
				a[n][i] = s[i];
				if (s[i] == '@') {
					u = n, v = i;
				}
			}
			n++;
			cin >> s;
		}
		FOR(i, 0, n) FOR(j, 0, m) if (i != u || j != v) {
			int ni = i, nj = j;
			if (i > u) ni = i - 1;
			else if (i < u) ni = i + 1;
			if (j > v) nj = j - 1;
			else if (j < v) nj = j + 1;
			nxt[i][j] = mp(ni, nj);
		}
		vii v1, v2;
		FOR(i, 0, n) FOR(j, 0, m) {
			if (a[i][j] == '+') {
				v1.pb(mp(i, j));
			}
			else if (a[i][j] == '#') {
				v2.pb(mp(i, j));
			}
		}
		int ans = 0;
		while (sz(v1) + sz(v2)) {
			vii his1, his2, his3;
			FOR(i, 0, sz(v1)) {
				int x = v1[i].fi;
				int y = v1[i].se;
				int nx = nxt[x][y].fi;
				int ny = nxt[x][y].se;
				if (a[nx][ny] == '*') continue;
				if (mp(nx, ny) == mp(u, v)) {
					ans++;
				}
				else {
					cnt1[nx][ny]++;
					his1.pb(mp(nx, ny));
				}
			}
			FOR(i, 0, sz(v2)) {
				int x = v2[i].fi;
				int y = v2[i].se;
				int nx = nxt[x][y].fi;
				int ny = nxt[x][y].se;
				if (a[nx][ny] == '*') continue;
				if (mp(nx, ny) == mp(u, v)) {
					ans++;
				}
				else {
					cnt2[nx][ny]++;
					his2.pb(mp(nx, ny));
				}
			}
			FOR(i, 0, sz(his2)) {
				int x = his2[i].fi;
				int y = his2[i].se;
				if (cnt1[x][y] || cnt2[x][y] > 1) {
					a[x][y] = '*';
					continue;
				}
				int nx = nxt[x][y].fi;
				int ny = nxt[x][y].se;
				if (a[nx][ny] == '*') continue;
				if (mp(nx, ny) == mp(u, v)) {
					ans++;
				}
				else {
					cnt3[nx][ny]++;
					his3.pb(mp(nx, ny));
				}
			}
			vii nv1, nv2;
			FOR(i, 0, sz(his1)) {
				int x = his1[i].fi;
				int y = his1[i].se;
				if (a[x][y] == '*') continue;
				if (cnt1[x][y] == 1 && !cnt2[x][y] && !cnt3[x][y]) {
					nv1.pb(mp(x, y));
				}
				else {
					a[x][y] = '*';
				}
			}
			FOR(i, 0, sz(his3)) {
				int x = his3[i].fi;
				int y = his3[i].se;
				if (a[x][y] == '*') continue;
				if (!cnt1[x][y] && cnt3[x][y] == 1) {
					nv2.pb(mp(x, y));
				}
				else {
					a[x][y] = '*';
				}
			}
			v1 = nv1, v2 = nv2;
			FOR(i, 0, sz(his1)) {
				int x = his1[i].fi;
				int y = his1[i].se;
				cnt1[x][y] = 0;
			}
			FOR(i, 0, sz(his2)) {
				int x = his2[i].fi;
				int y = his2[i].se;
				cnt2[x][y] = 0;
			}
			FOR(i, 0, sz(his3)) {
				int x = his3[i].fi;
				int y = his3[i].se;
				cnt3[x][y] = 0;
			}
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
