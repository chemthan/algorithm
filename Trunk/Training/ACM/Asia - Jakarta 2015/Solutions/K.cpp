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

const int maxn = 10000 + 10;
int n, k;
int a[maxn];
int b[maxn];
int c[maxn];
int d[maxn];
int f[maxn];

struct Info {
	double mx;
	int l, r;
	Info() : mx(-1e9), l(-1), r(-1) {}
	Info(double mx, int l, int r) : mx(mx), l(l), r(r) {}
	Info(const Info& rhs) : mx(rhs.mx), l(rhs.l), r(rhs.r) {}
	int operator < (const Info& rhs) const {return mx < rhs.mx;}
	Info operator + (const Info& rhs) const {return Info(mx + rhs.mx, l, rhs.r);}
};

struct Node {
	Info it[11], m[11], l[11], r[11];
};

Node merge(Node& x, Node& y) {
	Node z;
	FOR(i, 0, k + 1) {
		z.it[i] = max(x.it[i], y.it[i]);
		z.l[i] = x.l[i];
		z.r[i] = y.r[i];
	}
	FOR(i, 0, k + 1) FOR(j, 0, k - i + 1) {
		chkmax(z.it[i + j], x.r[i] + y.l[j]);
		chkmax(z.m[i + j], x.m[i] + y.m[j]);
		chkmax(z.l[i + j], x.m[i] + y.l[j]);
		chkmax(z.r[i + j], x.r[i] + y.m[j]);
	}
	return z;
}

Node st[maxn << 2];
void build(int p, int L, int R) {
	if (L == R) {
		FOR(i, 0, k + 1) {
			st[p].it[i] = st[p].m[i] = st[p].l[i] = st[p].r[i] = Info();
		}
		st[p].it[0] = st[p].m[0] = st[p].l[0] = st[p].r[0] = Info(log(a[L]) - log(b[L]), L, L);
		st[p].it[1] = st[p].m[1] = st[p].l[1] = st[p].r[1] = Info(0.0, L, L);
		return;
	}
	build(p << 1, L, L + R >> 1);
	build(p << 1 | 1, (L + R >> 1) + 1, R);
	st[p] = merge(st[p << 1], st[p << 1 | 1]);
}

int compare1(int i, int j) {
	return c[i] * d[j] >= c[j] * d[i];
}

int compare2(pair<int, pi> a, pair<int, pi> b) {
	return a.se.fi * b.se.se < a.se.se * b.se.fi;
}

void solve() {
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case #" << it << ":\n";
		cin >> n >> k;
		FOR(i, 0, n) {
			string s; cin >> s;
			FOR(j, 0, sz(s)) if (s[j] == '/') s[j] = ' ';
			stringstream ss(s);
			ss >> a[i] >> b[i];
		}
		FOR(i, 0, k) {
			string s; cin >> s;
			FOR(j, 0, sz(s)) if (s[j] == '/') s[j] = ' ';
			stringstream ss(s);
			ss >> c[i] >> d[i];
		}
		build(1, 0, n - 1);
		vi v; FOR(i, 0, k) v.pb(i);
		sort(all(v), compare1);
		Info ans;
		double mx = 0.0;
		int tot = 0;
		FOR(i, 0, k + 1) {
			st[1].it[i].mx += mx;
			if (chkmax(ans, st[1].it[i])) {
				tot = i;
			}
			if (i < k) {
				mx += log(c[v[i]]) - log(d[v[i]]);
			}
		}
		cout << ans.l + 1 << " " << ans.r + 1 << "\n";
		vector<pair<int, pi> > v1, v2;
		FOR(i, 0, k) {
			v1.pb(mp(i, mp(-c[i], d[i])));
		}
		FOR(i, ans.l, ans.r + 1) {
			v2.pb(mp(i, mp(a[i], b[i])));
		}
		sort(all(v1), compare2);
		sort(all(v2), compare2);
		fill_n(f, k, 0);
		FOR(i, 0, tot) f[v1[i].fi] = v2[i].fi + 1;
		FOR(i, 0, k) cout << f[i] << " \n"[i == k - 1];
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
