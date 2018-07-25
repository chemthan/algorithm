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
	PT(const PT& p) : x(p.x), y(p.y) {}
	PT operator + (const PT& p) const {return PT(x + p.x, y + p.y);}
	PT operator - (const PT& p) const {return PT(x - p.x, y - p.y);}
};
int cross(PT p, PT q) {return p.x * q.y - p.y * q.x;}

const int maxn = 2000 + 10;
int x, y, r;
int n;
PT p[maxn];

int compare(pair<PT, int> a, pair<PT, int> b) {
	return cross(a.fi, b.fi) > 0;
}

double dist(PT a, PT b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double calc(PT a, PT b) {
	PT cen = PT(x, y) - a; a = PT(0, 0);
	double h = abs(cross(a, b) + cross(b, cen) + cross(cen, a)) / dist(a, b);
	double angle = 2.0 * acos(h / r);
	if (cross(a - cen, b - cen) > 0) {
		return (angle - sin(angle)) / 2 / PI;
	}
	else {
		return 1.0 - (angle - sin(angle)) / 2 / PI;
	}
}

double work(int u) {
	vector<pair<PT, int> > vp;
	int c1 = 0, c2 = 0;
	FOR(i, 0, n) if (i != u) {
		PT q = p[i] - p[u];
		if (q.y < 0 || (q.y == 0 && q.x < 0)) {
			q.x *= -1, q.y *= -1;
			vp.pb(mp(q, -1));
			c2++;
		}
		else {
			vp.pb(mp(q, +1));
			c1++;
		}
	}
	if (p[u].x != x || p[u].y != y) {
		PT q = PT(y - p[u].y, -x + p[u].x);
		if (q.y < 0 || (q.y == 0 && q.x < 0)) {
			q.x *= -1, q.y *= -1;
		}
		vp.pb(mp(q, 0));
	}
	sort(all(vp), compare);
	int tot1 = 0, tot2 = 0;
	double res = 0.0;
	FOR(i, 0, sz(vp)) {
		int tmp1 = 0, tmp2 = 0;
		if (vp[i].se == +1) {
			tmp1++;
		}
		if (vp[i].se == -1) {
			tmp2++;
		}
		double r = calc(p[u], vp[i].fi);
		int sum = tot1 + c2 - tot2;
		FOR(x, 0, 2) FOR(y, 0, tmp1 + 1) FOR(z, 0, tmp2 + 1) {
			chkmax(res, fabs(r - (double) (sum + x + y - z) / n));
		}
		tot1 += tmp1, tot2 += tmp2;
	}
	return res;
}

void solve() {
	int test = 1;
	while (1) {
		cin >> x >> y >> r >> n;
		if (!n) break;
		cout << "Scenario " << (test++) << ": ";
		FOR(i, 0, n) {
			int u, v; cin >> u >> v;
			p[i] = PT(u, v);
		}
		double ans = 0.0;
		FOR(i, 0, n) chkmax(ans, work(i));
		cout << prec(6) << ans << "\n";
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
