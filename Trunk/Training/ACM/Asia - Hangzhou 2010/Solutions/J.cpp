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

const int maxn = 1000 + 10;
int n, m;
double p[maxn];
char s[maxn];
int nsz;
int link[maxn];
double f[maxn][maxn];

void build() {
	nsz = strlen(s);
	int cur = link[0] = -1;
	for (int i = 1; i < nsz; i++) {
		while (cur >= 0 && s[i] != s[cur + 1]) cur = link[cur];
		if (s[i] == s[cur + 1]) cur++;
		link[i] = cur;
	}
}

void solve() {
	while (cin >> n >> m) {
		if (!n && !m) break;
		ms(p, 0); ms(f, 0);
		FOR(i, 0, n) {
			string c; cin >> c; cin >> p[c[0]];
		}
		cin >> s;
		build();
		f[0][0] = 1.0;
		FOR(i, 0, m) FOR(j, 0, nsz) {
			FOR(k, 'a', 'z' + 1) {
				int cur = j - 1;
				while (cur >= 0 && k != s[cur + 1]) cur = link[cur];
				if (k == s[cur + 1]) cur++;
				f[i + 1][cur + 1] += f[i][j] * p[k];
			}
		}
		double ans = 0.0;
		FOR(i, 1, m + 1) {
			ans += f[i][nsz];
		}
		cout << prec(2) << ans * 100 << "%\n";
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
