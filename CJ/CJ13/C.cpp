#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); --i)
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
const int FFTMOD = 119 << 23 | 1;
const int INF = (int) 1e9 + 23111992;
const ll LINF = (ll) 1e18 + 23111992;
const ld PI = acos((ld) -1);
const ld EPS = 1e-6;
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
template<class T> inline int chkmin(T& a, const T& val) {return val < a ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
inline ull isqrt(ull k) {ull r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}
inline int sign(ld x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(ld x, ld y) {return sign(x - y);}
mt19937 mt(chrono::high_resolution_clock::now().time_since_epoch().count());
inline int mrand() {return abs((int) mt());}
inline int mrand(int k) {return abs((int) mt()) % k;}
#define db(x) cerr << "[" << #x << ": " << (x) << "] ";
#define endln cerr << "\n";

#define double long double
#define EPS 1e-9
struct point_t {
    double x, y;
    point_t() : x(0), y(0) {}
    point_t(double x, double y) : x(x), y(y) {}
    point_t(const point_t& p) : x(p.x), y(p.y) {}
    int operator < (const point_t& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
    int operator == (const point_t& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
    int operator != (const point_t& rhs) const {return make_pair(y, x) != make_pair(rhs.y, rhs.x);}
    point_t operator + (const point_t& p) const {return point_t(x + p.x, y + p.y);}
    point_t operator - (const point_t& p) const {return point_t(x - p.x, y - p.y);}
    point_t operator * (double c) const {return point_t(x * c, y * c);}
    point_t operator / (double c) const {return point_t(x / c, y / c);}
};
double cross(point_t p, point_t q) {return p.x * q.y - p.y * q.x;}
double area(point_t a, point_t b, point_t c) {return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;}
double area2(point_t a, point_t b, point_t c) {return cross(a, b) + cross(b, c) + cross(c, a);}
double dot(point_t p, point_t q) {return p.x * q.x + p.y * q.y;}
double dist(point_t p, point_t q) {return sqrt(dot(p - q, p - q));}
double dist2(point_t p, point_t q) {return dot(p - q, p - q);}
point_t RotateCCW90(point_t p) {return point_t(-p.y, p.x);}
point_t RotateCW90(point_t p) {return point_t(p.y, -p.x);}
point_t RotateCCW(point_t p, double t) {return point_t(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));}
ostream& operator << (ostream& os, const point_t& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

vector<pair<point_t, point_t>> divide(vector<point_t> pts) {
    int n = pts.size();
    assert(!(n & 1));
    n >>= 1;

    sort(all(pts), [&] (point_t a, point_t b) {
            return mp(a.x, a.y) < mp(b.x, b.y);
            }
        );
    sort(pts.begin() + 1, pts.end(), [&] (point_t a, point_t b) {
            return 0 < cross(a - pts[0], b - pts[0]);
            }
        );
    int st = 0, ed = n;
    vector<pair<point_t, point_t>> res;
    while (1) {
        int cnt = 1;
        FOR(i, 0, n + n) {
            if (0 < cross(pts[ed] - pts[i], pts[st] - pts[i])) {
                cnt++;
            }
        }
        if (cnt == n) {
            res.push_back({pts[st], pts[ed]});
        }
        cnt--;
        if (cnt < n) {
            int ned = -1;
            FOR(i, 0, n + n) if (0 < cross(pts[st] - pts[i], pts[ed] - pts[i])) {
                if (ned == -1 || 0 < cross(pts[i] - pts[st], pts[ned] - pts[st])) {
                    ned = i;
                }
            }
            assert(ned != -1);
            int ned2 = -1;
            FOR(i, 0, n + n) if (0 < cross(pts[ed] - pts[i], pts[st] - pts[i])) {
                if (ned2 == -1 || 0 < cross(pts[i] - pts[st], pts[ned2] - pts[st])) {
                    ned2 = i;
                }
            }
            if (ned2 != -1 && 0 < cross(pts[st] - pts[ned2], pts[ned] - pts[st])) {
                ed = st, st = ned2;
            }
            else {
                ed = ned;
            }
        }
        else {
            int nst = -1;
            FOR(i, 0, n + n) if (0 < cross(pts[ed] - pts[i], pts[st] - pts[i])) {
                if (nst == -1 || 0 < cross(pts[i] - pts[ed], pts[nst] - pts[ed])) {
                    nst = i;
                }
            }
            assert(nst != -1);
            int nst2 = -1;
            FOR(i, 0, n + n) if (0 < cross(pts[st] - pts[i], pts[ed] - pts[i])) {
                if (nst2 == -1 || 0 < cross(pts[i] - pts[ed], pts[nst2] - pts[ed])) {
                    nst2 = i;
                }
            }
            if (nst2 != -1 && 0 < cross(pts[ed] - pts[nst2], pts[nst] - pts[ed])) {
                st = ed, ed = nst2;
            }
            else {
                st = nst;
            }
        }
        if (st == 0 && ed == n) {
            break;
        }
    }
    return res;
}

void chemthan() {
    auto solve = [&] () {
        int n; cin >> n; n <<= 2;
        vector<point_t> pts(n);
        FOR(i, 0, n) {
            int x, y; cin >> x >> y;
            pts[i] = point_t(x, y);
        }
        auto clusters = divide(pts);
        for (auto e : clusters) {
            point_t p = e.fi;
            point_t q = e.se;
            point_t x(-INF, -INF);
            FOR(i, 0, n) if (pts[i] != p && pts[i] != q) {
                if (0 < cross(q - p, pts[i] - p)) {
                    if (0 < cross(pts[i] - p, x) || x == point_t(-INF, -INF)) {
                        x = pts[i] - p;
                    }
                }
                if (0 < cross(q - p, p - pts[i]) || x == point_t(-INF, -INF)) {
                    if (0 < cross(p - pts[i], x)) {
                        x = p - pts[i];
                    }
                }
            }
            double lo = 0, hi = 1;
            auto calc = [&] (double mi) {
                point_t w = (q - p) * (1 - mi) + x * mi;
                double a = atan2(w.y, w.x);
                vector<double> alls, ups;
                alls.pb(0);
                ups.pb(0);
                alls.pb(dist(point_t(), RotateCCW(q - p, -a)));
                FOR(i, 0, n) if (pts[i] != p && pts[i] != q) {
                    point_t t = p + RotateCCW(pts[i] - p, -a);
                    if (0 < cross(q - p, pts[i] - p)) {
                        ups.pb(t.x);
                    }
                    alls.pb(t.x);
                }
                sort(all(alls));
                double xx = (alls[n / 2 - 1] + alls[n / 2]) / 2;
                int total = 0;
                for (auto e : ups) {
                    if (e < xx) {
                        total++;
                    }
                }
                return total;
            };
            if (n / 4 < calc(lo) || calc(hi) < n / 4) {
                continue;
            }
            FOR(it, 0, 100) {
                double mi = (lo + hi) / 2;
                int total = calc(mi);
                if (total < n / 4) {
                    lo = mi;
                }
                else if (n / 4 < total) {
                    hi = mi;
                }
                else if (mrand(2)) {
                    lo = mi;
                }
                else {
                    hi = mi;
                }
            }
            double mi = (lo + hi) / 2;
            point_t w = (q - p) * (1 - mi) + x * mi;
            double a = atan2(w.y, w.x);
            vector<double> alls, ups;
            alls.pb(0);
            ups.pb(0);
            alls.pb(dist(point_t(), RotateCCW(q - p, -a)));
            double mx = RotateCCW(q - p, -a).y;
            FOR(i, 0, n) if (pts[i] != p && pts[i] != q) {
                point_t t = RotateCCW(pts[i] - p, -a);
                if (0 < cross(q - p, pts[i] - p)) {
                    ups.pb(t.x);
                }
                else {
                    chkmax(mx, t.y);
                }
                alls.pb(t.x);
            }
            assert(sz(ups) == n / 2);
            sort(all(alls));
            double xx = (alls[n / 2 - 1] + alls[n / 2]) / 2;
            int total = 0;
            for (auto e : ups) {
                if (e < xx) {
                    total++;
                }
            }
            if (total == n / 4) {
                point_t t = p + RotateCCW(point_t(xx, mx / 2), a);
                point_t pp = p + RotateCCW(point_t(0, mx / 2), a);
                cout << prec(9) << t.x << " " << t.y << " " << pp.x << " " << pp.y << "\n";
                return;
            }
        }
        cout << "IMPOSSIBLE\n";
    };
    int test; cin >> test;
    FOR(it, 1, test + 1) {
        cout << "Case #" << it << ": ";
        db(it) endln;
        solve();
    }
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0), cin.tie(0);
    if (argc > 1) {
        assert(freopen(argv[1], "r", stdin));
    }
    if (argc > 2) {
        assert(freopen(argv[2], "wb", stdout));
    }
    chemthan();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
