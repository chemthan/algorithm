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
	int x, y, c;
	PT() : x(0), y(0), c(0) {}
	PT(int x, int y, int c) : x(x), y(y), c(c) {}
	PT(const PT& p) : x(p.x), y(p.y), c(p.c) {}
	PT operator - (const PT& p) const {return PT(x - p.x, y - p.y, c);}
	PT operator + (const PT& p) const {return PT(x + p.x, y + p.y, 0);}
};

long long cross(PT a, PT b) {
	return (long long) a.x * b.y - (long long) a.y * b.x;
}

int compare(PT a, PT b) {
	return cross(a, b) > 0;
}

const int maxn = 250 + 10;
int n;
PT p[maxn];

int work(int u) {
	vector<PT> vp;
	int w1 = 0, w2 = 0, t1 = 0, t2 = 0;
	FOR(i, 0, n) if (i != u) {
		if (mp(p[i].x, p[i].y) == mp(p[u].x, p[u].y)) {
			if (p[i].c != p[u].c) {
				return 0;
			}
			continue;
		}
		PT q = p[i] - p[u];
		if (q.y < 0 || (q.y == 0 && q.x < 0)) {
			if (q.c == 1) {
				t1++;
			}
			else {
				t2++;
			}
			q.x *= -1;
			q.y *= -1;
			q.c *= -1;
		}
		else {
			if (q.c == 1) {
				w1++;
			}
			else {
				w2++;
			}
		}
		vp.pb(q);
	}
	sort(all(vp), compare);
	vector<PT> tmp; tmp.pb(PT(1, 0, 0));
	FOR(i, 0, sz(vp) - 1) {
		if (cross(vp[i], vp[i + 1])) {
			tmp.pb(vp[i] + vp[i + 1]);
		}
	}
	vp.insert(vp.end(), all(tmp));
	sort(all(vp), compare);
	int ww1 = 0, ww2 = 0, tt1 = 0, tt2 = 0;
	FOR(i, 0, sz(vp)) {
		if (vp[i].c == 1) {
			ww1++;
		}
		else if (vp[i].c == 2) {
			ww2++;
		}
		else if (vp[i].c == -1) {
			tt1++;
		}
		else if (vp[i].c == -2) {
			tt2++;
		}
		else {
			if (ww1 == w1 && tt1 == 0 && ww2 == 0 && tt2 == t2) {
				return 1;
			}
			if (ww2 == w2 && tt2 == 0 && ww1 == 0 && tt1 == t1) {
				return 1;
			}
		}
	}
	return 0;
}

void solve() {
	int test; cin >> test;
	while (test--) {
		cin >> n;
		FOR(i, 0, n) {
			cin >> p[i].x >> p[i].y >> p[i].c;
			p[i].c++;
		}
		int ans = 0;
		FOR(i, 0, n) {
			ans |= work(i);
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
