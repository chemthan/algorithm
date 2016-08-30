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

#define RL long long
struct PT {
	RL x, y;
	PT() : x(0), y(0) {}
	PT(RL x, RL y) : x(x), y(y) {}
	PT(const PT& p) : x(p.x), y(p.y) {}
	int operator < (const PT& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
	int operator == (const PT& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
	PT operator + (const PT& p) const {return PT(x + p.x, y + p.y);}
	PT operator - (const PT& p) const {return PT(x - p.x, y - p.y);}
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
ostream& operator << (ostream& os, const PT& p) {
  os << "(" << p.x << "," << p.y << ")"; 
}
int Between(PT a, PT b, PT c) {
	if (cross(a - b, a - c)) return 0;
	return dist2(a, c) >= dist2(a, b) + dist2(b, c);
}
int PointOnPolygon(const vector<PT>& p, PT q) {
	for (int i = 0; i < p.size(); i++) if (Between(p[i], q, p[(i + 1) % p.size()])) return 1;
	return 0;
}
int PointInPolygon(const vector<PT>& p, PT q) {
	int c = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		if (p[i].y <= q.y && q.y < p[j].y) {
			if (q.x * (p[j].y - p[i].y) < p[i].x * (p[j].y - p[i].y) + (p[j].x - p[i].x) * (q.y - p[i].y)) {
				c = !c;
			}
		}
		else if (p[j].y <= q.y && q.y < p[i].y) {
			if (q.x * (p[j].y - p[i].y) > p[i].x * (p[j].y - p[i].y) + (p[j].x - p[i].x) * (q.y - p[i].y)) {
				c = !c;
			}
		}
	}
	return c;
}

typedef long long T;
const int maxn = 200000 + 10;
const T oo = (T) 1e18;
int n;
int x[maxn];
int y[maxn];
pair<PT, int> p[maxn];
int ti[maxn];
int tx[maxn];
int ty[maxn];
vector<pair<T, int> > vbest;

int cmpX(const pair<PT, int>& a, const pair<PT, int>& b) {return a.first.x < b.first.x;}
int cmpY(const pair<PT, int>& a, const pair<PT, int>& b) {return a.first.y < b.first.y;}
T dist(int x, int y, int z, int t) {return (T) (x - z) * (x - z) + (T) (y - t) * (y - t);}

int compare(pair<T, int> a, pair<T, int> b) {
	if (a.fi != b.fi) return a.fi < b.fi;
	return a.se < b.se;
}

void build(int l, int r, int divX, pair<PT, int> p[]) {
	if (l >= r) return;
	int m = l + r >> 1;
	nth_element(p + l, p + m, p + r, divX ? cmpX : cmpY);
	ti[m] = p[m].second;
	tx[m] = p[m].first.x;
	ty[m] = p[m].first.y;
	build(l, m, !divX, p);
	build(m + 1, r, !divX, p);
}
void query(int l, int r, int x, int y, int divX) {
	if (l >= r) return;
	int m = l + r >> 1;
	vbest.pb(mp(dist(x, y, tx[m], ty[m]), ti[m]));
	sort(all(vbest), compare);
	while (sz(vbest) > 2) vbest.pop_back();
	T best = +oo;
	if (sz(vbest) == 2) best = vbest[1].fi;
	int delta = divX ? x - tx[m] : y - ty[m];
	if (delta <= 0) {
		query(l, m, x, y, !divX);
		if (dist(delta, 0, 0, 0) <= best) query(m + 1, r, x, y, !divX);
	}
	else {
		query(m + 1, r, x, y, !divX);
		if (dist(delta, 0, 0, 0) <= best) query(l, m, x, y, !divX);
	}
}
vector<pair<T, int> > query(int x, int y, int cnt) {
	vbest.clear();
	query(0, cnt, x, y, 1);
	return vbest;
}

void solve() {
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case #" << it << ":\n";
		cin >> n;
		FOR(i, 0, n) cin >> x[i] >> y[i];
		int r; cin >> r;
		FOR(ir, 1, r + 1) {
			cout << "Region " << ir << "\n";
			int b; cin >> b;
			vector<PT> vp(b);
			reverse(all(vp));
			FOR(i, 0, b) cin >> vp[i].x >> vp[i].y;
			int cnt = 0;
			FOR(i, 0, n) {
				if (PointOnPolygon(vp, PT(x[i], y[i])) || PointInPolygon(vp, PT(x[i], y[i]))) {
					p[cnt++] = mp(PT(x[i], y[i]), i);
				}
			}
			build(0, cnt, 1, p);
			int m; cin >> m;
			while (m--) {
				int u, v; cin >> u >> v;
				query(u, v, cnt);
				cout << vbest[0].se + 1 << " " << vbest[1].se + 1 << "\n";
			}
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
