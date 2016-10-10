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

#define RL double
#define EPS 1e-9
struct PT {
	RL x, y;
	PT() : x(0), y(0) {}
	PT(RL x, RL y) : x(x), y(y) {}
	PT(const PT& p) : x(p.x), y(p.y) {}
	int operator < (const PT& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
	int operator == (const PT& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
	PT operator + (const PT& p) const {return PT(x + p.x, y + p.y);}
	PT operator - (const PT& p) const {return PT(x - p.x, y - p.y);}
	PT operator * (RL c) const {return PT(x * c, y * c);}
	PT operator / (RL c) const {return PT(x / c, y / c);}
};
RL cross(PT p, PT q) {return p.x * q.y - p.y * q.x;}
RL area(PT a, PT b, PT c) {return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;}
RL area2(PT a, PT b, PT c) {return cross(a, b) + cross(b, c) + cross(c, a);}
RL dot(PT p, PT q) {return p.x * q.x + p.y * q.y;}
RL dist(PT p, PT q) {return sqrt(dot(p - q, p - q));}
RL dist2(PT p, PT q) {return dot(p - q, p - q);}
PT RotateCCW90(PT p) {return PT(-p.y, p.x);}
PT RotateCW90(PT p) {return PT(p.y, -p.x);}
PT RotateCCW(PT p, RL t) {return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));}
int sign(RL x) {return x < -EPS ? -1 : x > EPS;}
int sign(RL x, RL y) {return sign(x - y);}

void ConvexHull(vector<PT>& pts) {
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	vector<PT> up, dn;
	for (int i = 0; i < pts.size(); i++) {
		while (up.size() > 1 && area2(up[up.size() - 2], up.back(), pts[i]) >= 0) up.pop_back();
		while (dn.size() > 1 && area2(dn[dn.size() - 2], dn.back(), pts[i]) <= 0) dn.pop_back();
		up.push_back(pts[i]);
		dn.push_back(pts[i]);
	}
	pts = dn;
	for (int i = up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
}

const int maxn = 100 + 10;
double a, b, c, d;
int n;
double x[maxn];
double y[maxn];
double z[maxn];

void solve() {
	while (cin >> a >> b >> c >> d) {
		if (a == 0 && b == 0 && c == 0 && d == 0) break;
		cin >> n;
		FOR(i, 0, n + 1) cin >> x[i] >> y[i] >> z[i];
		if (a != 0) {
			x[n + 1] = d / a;
			y[n + 1] = 0.0;
			z[n + 1] = 0.0;
		}
		else if (b != 0) {
			x[n + 1] = 0.0;
			y[n + 1] = d / b;
			z[n + 1] = 0.0;
		}
		else if (c != 0) {
			x[n + 1] = 0.0;
			y[n + 1] = 0.0;
			z[n + 1] = d / c;
		}
		if (a != 0 || b != 0) {
			double al = -(b == 0 ? PI / 2 : atan(-a / b));
			FOR(i, 0, n + 2) {
				double tx = x[i] * cos(al) - y[i] * sin(al);
				double ty = x[i] * sin(al) + y[i] * cos(al);
				x[i] = tx, y[i] = ty;
			}
			b = sqrt(a * a + b * b), a = 0.0;
			al = -(c == 0 ? PI / 2 : atan(-b / c));
			FOR(i, 0, n + 2) {
				double ty = y[i] * cos(al) - z[i] * sin(al);
				double tz = y[i] * sin(al) + z[i] * cos(al);
				y[i] = ty, z[i] = tz;
			}
			c = sqrt(b * b + c * c), b = 0.0;
		}
		FOR(i, 0, n + 1) {
			z[i] -= z[n + 1];
		}
		if (z[n] < 0) {
			FOR(i, 0, n + 1) z[i] *= -1;
		}
		vector<PT> vp;
		int cnt = 0;
		FOR(i, 0, n) {
			if (z[n] > z[i]) {
				double t = z[n] / (z[n] - z[i]);
				double tx = (x[i] - x[n]) * t + x[n];
				double ty = (y[i] - y[n]) * t + y[n];
				vp.pb(PT(tx, ty));
			}
			else {
				cnt++;
			}
		}
		if (cnt) {
			if (!sz(vp)) {
				cout << prec(2) << 0.0 << "\n";
			}
			else {
				cout << "Infi\n";
			}
		}
		else {
			ConvexHull(vp);
			double ans = 0.0;
			FOR(i, 0, sz(vp)) {
				int j = (i + 1) % sz(vp);
				ans += cross(vp[i], vp[j]);
			}
			cout << prec(2) << fabs(ans) / 2.0 << "\n";
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
