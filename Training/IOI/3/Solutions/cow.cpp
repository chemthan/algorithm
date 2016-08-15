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

struct PT {
	int x, y, z;
	PT() : x(0), y(0), z(0) {}
	PT(int x, int y, int z) : x(x), y(y), z(z) {}
	PT(const PT& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
	int operator < (const PT& rhs) const {
		if (y != rhs.y) return y < rhs.y;
		return z > rhs.z;
	}
};

const int maxn = 500 + 10;
int n;
PT p[maxn];

pi work(int l, int r) {
	vector<PT> vp;
	FOR(i, 0, n) if (p[i].x >= l && p[i].x <= r) {
		vp.pb(p[i]);
	}
	sort(all(vp));
	if (!sz(vp)) return mp(0, 0);
	int tot = 0, prv = vp[0].y;
	pi best = mp(0, -INF);
	int ptr = 0;
	FOR(i, 0, sz(vp)) {
		while (ptr < sz(vp) && vp[ptr].y == vp[i].y) {
			if (!vp[ptr].z) tot = 0, prv = (ptr == sz(vp) - 1) ? 0 : vp[ptr + 1].y;
			else tot++;
			ptr++;
		}
		chkmax(best, mp(tot, prv - vp[ptr - 1].y));
	}
	return best;
}

void solve() {
	if (fopen("cowrect.in", "r")) {
		freopen("cowrect.in", "r", stdin);
		freopen("cowrect.out", "w", stdout);
	}
	cin >> n;
	vi vx;
	FOR(i, 0, n) {
		cin >> p[i].x >> p[i].y;
		string t; cin >> t;
		p[i].z = t == "H";
		vx.pb(p[i].x);
	}
	sort(all(vx)), uni(vx);
	int ans = 0, mn = 0;
	FOR(i, 0, sz(vx)) FOR(j, i, sz(vx)) {
		pi rr = work(vx[i], vx[j]);
		if (chkmax(ans, rr.fi)) {
			mn = (vx[j] - vx[i]) * -rr.se;
		}
		else if (ans == rr.fi) {
			chkmin(mn, (vx[j] - vx[i]) * -rr.se);
		}
	}
	cout << ans << "\n";
	cout << mn << "\n";
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
