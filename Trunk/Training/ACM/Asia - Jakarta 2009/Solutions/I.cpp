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

const int maxn = 4000000 + 10;
const int maxm = 10 + 1;
int n, a, b, m;
int f[maxm][maxm][maxm][maxm];
int x[maxn];
int pos[maxn];
int neg[maxn];

void solve() {
	FOR(i, 0, maxm) FOR(j, 0, maxm) FOR(k, 0, maxm) FOR(l, 1, maxm) {
		f[i][j][k][l] = (i * j + k) % l;
	}
	while (cin >> n) {
		cin >> x[0] >> a >> b >> m;
		pos[0] = x[0];
		FOR(i, 1, 2 * n + 2) {
			x[i] = f[x[i - 1]][a][b][m];
			if (!(i & 1)) {
				pos[i >> 1] = x[i];
			}
			else {
				neg[i >> 1] = x[i];
			}
		}
		FOR(i, 1, n + 1) {
			pos[i] += pos[i - 1];
			neg[i] += neg[i - 1];
		}
		if (pos[n] == 0) {
			cout << prec(6) << 1.0 << "\n";
			continue;
		}
		double ans = 0.0;
		FOR(i, 0, min(10, n + 1)) {
			FOR(j, i, min(i + 10, n + 1)) {
				int t1 = neg[j] - (i ? neg[i - 1] : 0);
				int t2 = pos[j] - (i ? pos[i - 1] : 0);
				ans = max(ans, 2.0 * t2 / (pos[n] + t1 + t2));
			}	
		}
		FOR(i, 0, min(10, n + 1)) {
			FOR(j, max(i, n - 10), n + 1) {
				int t1 = neg[j] - (i ? neg[i - 1] : 0);
				int t2 = pos[j] - (i ? pos[i - 1] : 0);
				ans = max(ans, 2.0 * t2 / (pos[n] + t1 + t2));
			}	
		}
		FOR(i, max(0, n - 10), n + 1) {
			FOR(j, i, min(i + 10, n + 1)) {
				int t1 = neg[j] - (i ? neg[i - 1] : 0);
				int t2 = pos[j] - (i ? pos[i - 1] : 0);
				ans = max(ans, 2.0 * t2 / (pos[n] + t1 + t2));
			}	
		}
		cout << prec(6) << ans << "\n";
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
