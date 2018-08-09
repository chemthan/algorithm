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
template<class T> inline T isqrt(T k) {T r = sqrt(k) + 1; while (r * r > k) r--; return r;}
template<class T> inline T icbrt(T k) {T r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}

const int maxn = 1000000 + 10;
int n, q;
int a[maxn];
int mn[maxn];
int ans[maxn];

struct RMQ {
	static const int MAXN = 100000 + 10;
	static const int LOGN = 20;
	int n;
	int a[MAXN];
	int f[MAXN][LOGN];
	void build() {
		for (int i = 0; i < n; i++) f[i][0] = a[i];
		for (int l = 0, k; (k = 1 << l) < n; l++) {
			for (int i = 0; i + k < n; i++) {
				f[i][l + 1] = __gcd(f[i][l], f[i + k][l]);
			}
		}
	}
	int query(int a, int b) {
		int l = a == b ? 0 : __lg(b - a);
		return __gcd(f[a][l], f[b - (1 << l) + 1][l]);
	}
} rmq;

int fen[maxn];
vi his;
void clear() {
	while (sz(his)) {
		fen[his.back()] = 0;
		his.pop_back();
	}
}
void update(int p, int val) {
	p++;
	for (; p < maxn; p += p & -p) {
		his.pb(p);
		fen[p] += val;
	}
}
int query(int p) {
	p++;
	int res = 0;
	for (; p > 0; p -= p & -p) {
		res += fen[p];
	}
	return res;
}

void solve() {
	while (cin >> n >> q) {
		clear();
		FOR(i, 0, n) cin >> a[i];
		rmq.n = n;
		FOR(i, 0, n) rmq.a[i] = a[i];
		rmq.build();
		vector<pair<pi, int> > seg;
		FOR(i, 0, n) {
			int cur = i;
			while (cur < n) {
				int k = rmq.query(i, cur);
				seg.pb(mp(mp(i, cur), k));
				mn[k] = INF;
				int l = cur + 1, r = n;
				while (l < r) {
					int m = l + r >> 1;
					if (rmq.query(i, m) == rmq.query(i, cur)) {
						l = m + 1;
					}
					else {
						r = m;
					}
				}
				cur = l;
			}
		}
		vector<pair<pi, int> > que;
		FOR(i, 0, q) {
			int l, r; cin >> l >> r; l--, r--;
			que.pb(mp(mp(l, r), i));
		}
		sort(all(seg)), sort(all(que));
		reverse(all(seg)), reverse(all(que));
		int ptr1 = 0, ptr2 = 0;
		FORd(i, n, 0) {
			while (ptr1 < sz(seg) && seg[ptr1].fi.fi >= i) {
				int ix = seg[ptr1].se;
				int r = seg[ptr1].fi.se;
				if (mn[ix] < INF) {
					update(mn[ix], -1);
				}
				chkmin(mn[ix], r);
				update(mn[ix], +1);
				ptr1++;
			}
			while (ptr2 < sz(que) && que[ptr2].fi.fi == i) {
				int ix = que[ptr2].se;
				int r = que[ptr2].fi.se;
				ans[ix] = query(r);
				ptr2++;
			}
		}
		FOR(i, 0, q) {
			cout << ans[i] << "\n";
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
