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

const int maxn = 2000 + 10;
int n, m, k;
int cnt;
int a[maxn];
string s;
int f[maxn][maxn];
int g[maxn];

void solve() {
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case #" << it << ": ";
		cin >> n >> m >> k;
		cin >> s;
		int prv = -1, tot = 0;
		cnt = 0;
		FOR(i, 0, sz(s)) {
			if (s[i] != prv) {
				if (tot) {
					a[cnt++] = tot;
					tot = 0;
				}
				prv = s[i];
			}
			tot++;
		}
		a[cnt++] = tot;
		FOR(i, 0, n + 1) FOR(j, 0, m + 1) f[i][j] = 0;
		FORd(i, cnt, 0) {
			FOR(j, 1, m + 1) g[j] = g[j - 1] + f[i + 1][j];
			FOR(j, 1, m + 1) {
				if (j > a[i]) {
					int l = max(0, j - a[i] * k);
					int r = j - a[i];
					int w = g[r] - (l ? g[l - 1] : 0);
					if (w == r - l + 1) {
						f[i][j] = 0;
					}
					else {
						f[i][j] = 1;
					}
				}
				else {
					f[i][j] = 1;
				}
			}
		}
		if (s[0] == 'A') {
			if (f[0][m]) {
				cout << "A" << "\n";
			}
			else {
				cout << "B" << "\n";
			}
		}
		else {
			if (f[0][m]) {
				cout << "B" << "\n";
			}
			else {
				cout << "A" << "\n";
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
