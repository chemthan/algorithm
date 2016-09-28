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

const int MAXN = 3000 + 10;
long long fen[4][MAXN][MAXN];
void upd(int x, int y, long long val) {
	for (int xx = x; xx < MAXN; xx += xx & -xx) {
		for (int yy = y; yy < MAXN; yy += yy & -yy) {
			fen[0][xx][yy] ^= val;
			if (x & 1) {
				fen[1][xx][yy] ^= val;
			}
			if (y & 1) {
				fen[2][xx][yy] ^= val;
			}
			if (x * y & 1) {
				fen[3][xx][yy] ^= val;
			}
		}
	}
}
void upd(int x, int y, int z, int t, long long val) {
	upd(x, y, val);
	upd(x, t + 1, val);
	upd(z + 1, y, val);
	upd(z + 1, t + 1, val);
}
long long query(int x, int y) {
	long long res = 0;
	for (int xx = x; xx > 0; xx -= xx & -xx) {
		for (int yy = y; yy > 0; yy -= yy & -yy) {
			if ((x + 1) * (y + 1) & 1) {
				res ^= fen[0][xx][yy];
			}
			if (y + 1 & 1) {
				res ^= fen[1][xx][yy];
			}
			if (x + 1 & 1) {
				res ^= fen[2][xx][yy];
			}
			res ^= fen[3][xx][yy];
		}
	}
	return res;
}

int n, q;

void solve() {
	cin >> n >> q;
	while (q--) {
		string op; cin >> op;
		if (op == "P") {
			int x[2], y[2];
			FOR(i, 0, 2) cin >> x[i] >> y[i];
			int k; cin >> k;
			long long val = 0;
			while (k--) {
				int u, v; cin >> u >> v; u--;
				if (v & 1) {
					val ^= 1LL << u;
				}
			}
			upd(x[0], y[0], x[1], y[1], val);
		}
		else if (op == "Q") {
			int x[2], y[2];
			FOR(i, 0, 2) cin >> x[i] >> y[i];
			long long res = query(x[1], y[1]);
			res ^= query(x[0] - 1, y[1]);
			res ^= query(x[1], y[0] - 1);
			res ^= query(x[0] - 1, y[0] - 1);
			FOR(i, 0, 50) cout << bit(res, i) + 1 << " ";
			cout << "\n";
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
