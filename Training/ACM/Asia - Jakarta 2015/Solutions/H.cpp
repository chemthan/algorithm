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

const int maxn = 100 + 10;
const int maxm = 500 + 10;
int n, m, a, b;
int z[maxn];
int x[maxm];
int y[maxm];
long long sum[maxm];
long long f[maxn][maxm];
long long g[maxn][maxm][maxm];

long long query(int l, int r) {
	return sum[r] - (l ? sum[l - 1] : 0);
}

long long calc(int u, int v) {
	if (v == m) return 0;
	if (u == n) return LINF;
	long long& res = f[u][v];
	if (~res) return res;
	res = LINF;
	chkmin(res, calc(u + 1, v));
	FOR(i, v, m) {
		chkmin(res, g[u][v][i] + calc(u + 1, i + 1));
	}
	return res;
}

void solve() {
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case #" << it << ": ";
		cin >> n >> m >> a >> b;
		FOR(i, 0, n) cin >> z[i];
		FOR(i, 0, m) cin >> x[i] >> y[i];
		sort(z, z + n), sort(x, x + m);
		FOR(i, 0, m) {
			if (!i) sum[i] = x[i];
			else sum[i] = sum[i - 1] + x[i];
		}
		FOR(i, 0, n) {
			int l = upper_bound(x, x + m, z[i]) - x - 1;
			FOR(j, 0, m) {
				int ptr = j;
				FOR(k, j, m) {
					g[i][j][k] = LINF;
					while (ptr < k && 2 * ((long long) b * (ptr - j + 1) + (x[ptr] >= z[i]) * a) < (long long) b * (k - j + 1) + a) ptr++;
					if (l < j) {
						chkmin(g[i][j][k], b * (query(j, k) - (long long) z[i] * (k - j + 1)));
					}
					else if (l <= k) {
						chkmin(g[i][j][k], b * ((long long) z[i] * (l - j + 1) - query(j, l) + query(l + 1, k) - (long long) z[i] * (k - l)));
					}
					else {
						chkmin(g[i][j][k], b * ((long long) z[i] * (k - j + 1) - query(j, k)));
					}
					chkmin(g[i][j][k], b * ((long long) x[ptr] * (ptr - j + 1) - query(j, ptr) + query(ptr + 1, k) - (long long) x[ptr] * (k - ptr)) + (long long) a * abs(x[ptr] - z[i]));
				}
			}
		}
		FOR(i, 0, n) FOR(j, 0, m) f[i][j] = -1;
		long long ans = calc(0, 0);
		FOR(i, 0, m) {
			ans += (long long) y[i] * b;
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
