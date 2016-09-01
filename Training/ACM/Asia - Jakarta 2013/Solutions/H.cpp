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

const int maxn = 1250 + 10;
int n, m;
int c[maxn];
int w[maxn];
int visf[maxn][maxn];
int visg[maxn][maxn];
double f[maxn][maxn];
double g[maxn][maxn];

void calcf(int, int);
void calcg(int, int);

void calcf(int pos, int k) {
	if (visf[pos][k]) return;
	visf[pos][k] = 1;
	if (pos == n) {
		f[pos][k] = 1.0;
		return;
	}
	double& res = f[pos][k];
	calcf(pos + 1, k), calcg(pos + 1, k);
	if (50 >= w[pos]) {
		res = (1.0 - w[pos] / 50.0) * f[pos + 1][k] + w[pos] / 100.0;
	}
	else {
		res = (1.0 - w[pos] / 50.0) * g[pos + 1][k] + w[pos] / 100.0;
	}
	if (k) {
		calcf(pos + 1, k - 1), calcg(pos + 1, k - 1);
		if (c[pos] >= 50) {
			chkmin(res, (c[pos] / 50.0 - 1.0) * f[pos + 1][k - 1] + 1 - c[pos] / 100.0);
		}
		else {
			chkmin(res, (c[pos] / 50.0 - 1.0) * g[pos + 1][k - 1] + 1 - c[pos] / 100.0);
		}
	}
}

void calcg(int pos, int k) {
	if (visg[pos][k]) return;
	visg[pos][k] = 1;
	if (pos == n) {
		g[pos][k] = 1.0;
		return;
	}
	double& res = g[pos][k];
	calcf(pos + 1, k), calcg(pos + 1, k);
	if (50 >= w[pos]) {
		res = (1.0 - w[pos] / 50.0) * g[pos + 1][k] + w[pos] / 100.0;
	}
	else {
		res = (1.0 - w[pos] / 50.0) * f[pos + 1][k] + w[pos] / 100.0;
	}
	if (k) {
		calcf(pos + 1, k - 1), calcg(pos + 1, k - 1);
		if (c[pos] >= 50) {
			chkmax(res, (c[pos] / 50.0 - 1.0) * g[pos + 1][k - 1] + 1 - c[pos] / 100.0);
		}
		else {
			chkmax(res, (c[pos] / 50.0 - 1.0) * f[pos + 1][k - 1] + 1 - c[pos] / 100.0);
		}
	}
}

void solve() {
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case #" << it << ": ";
		cin >> n >> m;
		FOR(i, 0, n) cin >> c[i];
		FOR(i, 0, n) cin >> w[i];
		FOR(i, 0, n + 1) FOR(j, 0, m + 1) {
			f[i][j] = 0.0;
			g[i][j] = 1.0;
			visf[i][j] = visg[i][j] = 0;
		}
		calcf(0, m);
		cout << prec(3) << 15000.0 * (2 * f[0][m] - 1) << "\n";
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
