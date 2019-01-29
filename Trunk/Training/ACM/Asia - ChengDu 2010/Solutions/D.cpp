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
PT ProjectPointLine(PT a, PT b, PT c) {
	return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
	b = b - a; d = c - d; c = c - a;
	return a + b * cross(c, d) / cross(b, d);
}

PT a, b;
PT p[3];
RL u;

pair<PT, PT> calc(int i, int j, PT a, PT b, RL u) {
	PT q = ComputeLineIntersection(a, b, p[i], p[j]);
	PT q1 = q + RotateCW90(p[i] - q);
	PT q2 = ProjectPointLine(q, q1, a);
	PT q3 = q * 2 - q2;
	RL alpha = asin(dist(a, q2) / dist(a, q) / u);
	PT q4;
	if (cross(q2 - q, a - q) > 0) {
		q4 = q + RotateCCW(q3 - q, +alpha);
	}
	else {
		q4 = q + RotateCCW(q3 - q, -alpha);
	}
	return mp(q, q4);
}

void work() {
	pair<RL, pi> best = mp(1e18, mp(0, 0));
	FOR(i, 0, 3) FOR(j, i + 1, 3) {
		RL x = cross(p[i] - a, p[i] - b);
		RL y = cross(p[j] - a, p[j] - b);
		if (sign(x) * sign(y) == -1) {
			PT q = ComputeLineIntersection(a, b, p[i], p[j]);
			if (sign(dist(a, q) + dist(a, b), dist(q, b))) {
				chkmin(best, mp(dist(a, q), mp(i, j)));
			}
		}
	}
	if (best.fi == 1e18) {
		if (sign(a.y, b.y) <= 0) {
			cout << "Error\n";
		}
		else {
			PT q = ComputeLineIntersection(a, b, PT(0.0, 0.0), PT(1.0, 0.0));
			cout << prec(3) << q.x << "\n";
		}
		return;
	}
	int i = best.se.fi;
	int j = best.se.se;
	int k; FOR(x, 0, 3) if (x != i && x != j) k = x;
	pair<PT, PT> r = calc(i, j, a, b, u);
	if (sign(r.fi.y, (RL) 0.0) == 0) {
		cout << prec(3) << r.fi.x << "\n";
		return;
	}
	RL x = cross(p[i] - a, p[i] - b);
	RL y = cross(p[k] - a, p[k] - b);
	if (sign(x) * sign(y) == -1) {
		pair<PT, PT> rr = calc(i, k, r.fi, r.se, 1.0 / u);
		if (sign(rr.fi.y, rr.se.y) <= 0) {
			cout << "Error\n";
			return;
		}
		PT q = ComputeLineIntersection(rr.fi, rr.se, PT(0.0, 0.0), PT(1.0, 0.0));
		cout << prec(3) << q.x << "\n";
	}
	else {
		pair<PT, PT> rr = calc(j, k, r.fi, r.se, 1.0 / u);
		if (sign(rr.fi.y, rr.se.y) <= 0) {
			cout << "Error\n";
			return;
		}
		PT q = ComputeLineIntersection(rr.fi, rr.se, PT(0.0, 0.0), PT(1.0, 0.0));
		cout << prec(3) << q.x << "\n";
	}
}	

void solve() {
	int test; cin >> test;
	while (test--) {
		cin >> a.x >> a.y >> b.x >> b.y;
		FOR(i, 0, 3) cin >> p[i].x >> p[i].y;
		cin >> u;
		work();
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
