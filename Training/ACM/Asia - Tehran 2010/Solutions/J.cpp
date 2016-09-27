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

struct PT {
	int x, y;
	PT() : x(0), y(0) {}
	PT(int x, int y) : x(x), y(y) {}
	PT(const PT& rhs) : x(rhs.x), y(rhs.y) {}
	PT operator - (const PT& rhs) const {return PT(x - rhs.x, y - rhs.y);}
};

long long cross(PT a, PT b) {
	return (long long) a.x * b.y - (long long) a.y * b.x;
}

int insect(PT a, PT b, PT c, PT d) {
	int sign1 = cross(a - c, a - d) < 0 ? -1 : cross(a - c, a - d) > 0;
	int sign2 = cross(b - c, b - d) < 0 ? -1 : cross(b - c, b - d) > 0;
	int sign3 = cross(c - a, c - b) < 0 ? -1 : cross(c - a, c - b) > 0;
	int sign4 = cross(d - a, d - b) < 0 ? -1 : cross(d - a, d - b) > 0;
	if (sign1 * sign2 == -1 && sign3 * sign4 == -1) return 1;
	return 0;
}

const int maxn = 500 + 10;
const int maxm = 10000 + 10;
int n, m;
int h[maxn];
int st[maxn];
int x[maxm];
PT p[maxm];
int a[maxn];
int f[maxn][maxn][2][2];
int c[maxn][maxn];
int g[maxn][2];

int calc(int u, int v, int fa, int fb) {
	int k = upper_bound(x, x + m, st[u] + h[u]) - x;
	int l = lower_bound(x, x + m, st[v] + h[v]) - x - 1;
	if (k > l) return c[u][v] = 0;
	c[u][v] = 1;
	int res = 0, ptr = u + 1;
	while (x[k] > st[ptr] + h[ptr]) ptr++;
	int tmp = ptr;
	vi his;
	FOR(i, k, l + 1) {
		while (x[i] > st[ptr] + h[ptr]) ptr++;
		if (fa && !insect(PT(st[u] + h[u], h[u]), p[i], PT(st[ptr - 1], 0), PT(st[ptr - 1] + h[ptr - 1], h[ptr - 1]))) continue;
		if (fb && !insect(PT(st[v] + h[v], h[v]), p[i], PT(st[ptr] + h[ptr], h[ptr]), PT(st[ptr] + 2 * h[ptr], 0))) continue;
		if (a[ptr - 1]) continue;
		if (!a[ptr]) {
			res++;
			a[ptr] = 1;
			his.pb(ptr);
		}
	}
	FOR(i, 0, sz(his)) a[his[i]] = 0;
	if (ptr == tmp) {
		return 0;
	}
	return res;
}

void solve() {
	while (cin >> n >> m) {
		if (!n && !m) break;
		fill_n(a, n + 2, 0);
		FOR(i, 0, n + 2) FOR(j, 0, n + 2) c[i][j] = 0;
		FOR(i, 1, n + 1) cin >> h[i];
		h[0] = h[n + 1] = 100, n += 2;
		FOR(i, 0, m) cin >> x[i], x[i] += 200;
		int cur = 0;
		FOR(i, 0, n) {
			st[i] = cur;
			cur += 2 * h[i];
		}
		int cnt = 0;
		FOR(i, 0, m) {
			int k = upper_bound(st, st + n, x[i]) - st - 1;
			if (st[k] + h[k] == x[i]) {
				a[k] = 1;
			}
			else if (st[k] + h[k] > x[i]) {
				p[cnt++] = PT(x[i], x[i] - st[k]);
			}
			else {
				p[cnt++] = PT(x[i], st[k] + 2 * h[k] - x[i]);
			}
		}
		m = cnt;
		FOR(i, 0, m) x[i] = p[i].x;
		vi v;
		FOR(i, 0, n) if (h[i] == 100) {
			v.pb(i);
			FOR(j, i + 1, n) if (h[j] == 100) {
				FOR(fa, 0, 2) FOR(fb, 0, 2) {
					f[i][j][fa][fb] = calc(i, j, fa, fb);
				}
				i = j - 1;
				break;
			}
		}
		FOR(i, 0, sz(v)) g[i][0] = g[i][1] = INF;
		g[0][0] = cnt = 0;
		int tmp = INF;
		FOR(k, 0, sz(v) - 1) {
			int i = v[k];
			int j = v[k + 1];
			if (c[i][j]) {
				cnt++;
				tmp = f[i][j][0][0];
			}
			chkmin(g[k + 1][0], g[k][1] + f[i][j][1][0]);
			if (!c[i][j]) {
				chkmin(g[k + 1][0], g[k][0] + f[i][j][0][0]);
			}
			chkmin(g[k + 1][1], g[k][0] + f[i][j][0][1] + (a[j] == 0));
			chkmin(g[k + 1][1], g[k][1] + f[i][j][1][1] + (a[j] == 0));
		}
		if (cnt == 1 && tmp < INF) {
			cout << tmp << "\n";
		}
		else {
			cout << g[sz(v) - 1][0] << "\n";
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
