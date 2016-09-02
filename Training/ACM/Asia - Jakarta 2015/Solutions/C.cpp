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

const int maxn = 100000 + 10;
const int logn = 20;
int n, q;
int a[maxn];
int b[maxn];
int c[maxn];
int nxt[logn][maxn];

void solve() {
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case #" << it << ":\n";
		cin >> n >> q;
		FOR(i, 0, n) cin >> a[i];
		FOR(i, 1, n + 1) cin >> b[i];
		map<int, int> lst;
		FORd(i, n, 0) {
			if (lst.count(a[i])) {
				nxt[0][i] = lst[a[i]];
				c[i] = c[nxt[0][i]] + 1;
			}
			else {
				nxt[0][i] = n;
				c[i] = 0;
			}
			lst[a[i]] = i;
		}
		nxt[0][n] = n;
		FOR(i, 1, logn) FOR(j, 0, n + 1) {
			nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
		}
		map<pi, int> mem;
		while (q--) {
			int x, y; cin >> x >> y;
			if (mem.count(mp(x, y))) {
				cout << mem[mp(x, y)] << "\n";
				continue;
			}
			if (!lst.count(x)) {
				cout << 1 << "\n";
			}
			else {
				int ans = 1, ptr = 0, cur = lst[x];
				while (ptr < n - 1) {
					int r = cur;
					FORd(i, logn, 0) {
						int ix = nxt[i][r];
						if (ix < n - 1 && (c[cur] - c[ix] + 1 < y || ix - ptr + 1 < b[y])) {
							r = ix;
						}
					}
					if (c[cur] - c[r] + 1 < y || r - ptr + 1 < b[y]) {
						r = nxt[0][r];
					}
					if (r < n - 1) {
						ans++;
						cur = nxt[0][r];
						ptr = r + 1;
					}
					else {
						break;
					}
				}
				cout << (mem[mp(x, y)] = ans) << "\n";
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
