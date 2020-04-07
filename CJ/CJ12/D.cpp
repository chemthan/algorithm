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

#define int long long
struct point_t {
    int x, y;
    point_t() : x(0), y(0) {}
    point_t(int x, int y) : x(x), y(y) {}
    point_t(const point_t& rhs) : x(rhs.x), y(rhs.y) {}
    int operator < (const point_t& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
    int operator == (const point_t& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
    int operator != (const point_t& rhs) const {return make_pair(y, x) != make_pair(rhs.y, rhs.x);}
    point_t operator - (const point_t& rhs) const {return point_t(x - rhs.x, y - rhs.y);}
};
long long cross(point_t a, point_t b) {
    return (long long) a.x * b.y - (long long) a.y * b.x;
}
long long area(point_t a, point_t b, point_t c) {
    return cross(a, b) + cross(b, c) + cross(c, a);
}
long long dist(point_t a, point_t b) {
    return (long long) (a.x - b.x) * (a.x - b.x) + (long long) (a.y - b.y) * (a.y - b.y);
}
void ConvexHull(vector<point_t>& pts) {
    vector<point_t> up, dn;
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area(up[up.size() - 2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area(dn[dn.size() - 2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
}
#undef int

void chemthan() {
    /*
       (x, y) -> (a + (y - b), b + (a - x))
              -> (a - b + y, a + b - x)
              -> ((c - d) + (a + b) - x, (c + d) - (a - b) - y)
              -> opposite through ((a + b) + (c - d), (c + d) - (a - b)) / 2
     */
    auto solve = [&] () {
        int n, m; cin >> n >> m;
        vector<point_t> pts(n);
        FOR(i, 0, n) cin >> pts[i].x >> pts[i].y, pts[i].x *= 2, pts[i].y *= 2;
        vector<point_t> hull;
        FOR(i, 0, n) FOR(j, 0, n) {
            long long a = pts[i].x;
            long long b = pts[i].y;
            long long c = pts[j].x;
            long long d = pts[j].y;
            point_t q((a + b + c - d) / 2, (c + d - a + b) / 2);
            hull.pb(q);
        }
        ConvexHull(hull);
        vector<point_t> thull;
        FOR(i, 0, sz(hull)) FOR(j, 0, sz(hull)) {
            thull.pb(hull[i] - hull[j]);
            thull.back().x *= 2;
            thull.back().y *= 2;
        }
        ConvexHull(thull);
        swap(hull, thull);
        long double res = 0;
        for (int i = 0; i < 4 && 0 <= m; i++, m--) {
            auto hull1 = hull;
            for (auto& q : hull1) q.x *= m / 4, q.y *= m / 4;
            vector<point_t> hull2;
            hull2.pb(point_t());
            if (1 <= m % 4) {
                FOR(i, 0, n) {
                    point_t q(-pts[i].x + pts[i].y, -pts[i].x - pts[i].y);
                    hull2.pb(q);
                }
            }
            if (2 <= m % 4) {
                for (auto& w : thull) {
                    hull2.pb(point_t(-2 * w.x, -2 * w.y));
                }
            }
            if (m % 4 == 3) {
                FOR(i, 0, n) {
                    point_t q(pts[i].x - pts[i].y, pts[i].x + pts[i].y);
                    for (auto& w : thull) {
                        hull2.pb(point_t(-2 * w.x + q.x, -2 * w.y + q.y));
                    }
                }
            }
            ConvexHull(hull2);
            for (auto& q1 : hull1) for (auto& q2 : hull2) {
                chkmax(res, (long double) (q1.x - q2.x) * (q1.x - q2.x) + (long double) (q1.y - q2.y) * (q1.y - q2.y));
            }
        }
        cout << prec(9) << sqrt(res) / 2 << "\n";
    };
    int test; cin >> test;
    FOR(it, 1, test + 1) {
        db(it) endln;
        cout << "Case #" << it << ": ";
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
