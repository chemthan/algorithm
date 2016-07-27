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
int n, a, b;
int x[maxn];
map<int, int> cnt;
map<int, int> ans;

void solve() {
	int test; cin >> test;
	FOR(it, 1, test + 1) {
		cout << "Case #" << it << ":\n";
		cnt.clear(), ans.clear();
		cin >> n >> a >> b;
		FOR(i, 0, n) {
			cin >> x[i];
			cnt[x[i]]++;
		}
		int sig = 1, tot = 0;
		FOR(i, 0, b) {
			if (cnt[2]) ans[2]++, cnt[2]--, tot++;
			else if (cnt[-2]) ans[-2]++, cnt[-2]--, sig *= -1, tot++;
			else if (cnt[1]) ans[1]++, cnt[1]--, tot++;
			else if (cnt[-1]) ans[-1]++, cnt[-1]--, sig *= -1, tot++;
		}
		while (tot < a) ans[0]++, cnt[0]--, tot++, sig = 0;
		if (sig == -1) {
			if (ans[2] && cnt[-2]) {
				ans[2]--, cnt[2]++;
				ans[-2]++, cnt[-2]--;
				sig *= -1;
			}
			else if (ans[1] && cnt[-1]) {
				ans[1]--, cnt[1]++;
				ans[-1]++, cnt[-1]--;
				sig *= -1;
			}
			else if (ans[2] && cnt[-1]) {
				ans[2]--, cnt[2]++;
				ans[-1]++, cnt[-1]--;
				sig *= -1;
			}
			else if (ans[-2] && cnt[1]) {
				ans[-2]--, cnt[-2]++;
				ans[1]++, cnt[1]--;
				sig *= -1;
			}
		}
		if (sig == -1 && tot > a) {
			if (ans[-1]) ans[-1]--, cnt[-1]++, sig *= -1, tot--;
			else if (ans[-2]) ans[-2]--, cnt[-2]++, sig *= -1, tot--;
		}
		if (sig == -1) {
			if (cnt[0]) {
				FOR(i, -2, 3) if (i && ans[i]) {
					ans[i]--, cnt[i]++;
					ans[0]++, cnt[0]--;
					sig = 0;
					break;
				}
			}
			else {
				while (ans[2] && tot > a) ans[2]--, cnt[2]++, tot--;
				while (ans[2] && cnt[1]) {
					ans[2]--, cnt[2]++;
					ans[1]++, cnt[1]--;
				}
				while (ans[-2] && cnt[-1]) {
					ans[-2]--, cnt[-2]++;
					ans[-1]++, cnt[-1]--;
				}
			}
		}
		vi vans;
		FOR(i, 0, n) {
			if (ans[x[i]]) {
				vans.pb(i);
				ans[x[i]]--;
			}
		}
		cout << sz(vans) << "\n";
		FOR(i, 0, sz(vans)) cout << vans[i] + 1 << " \n"[i == sz(vans) - 1];
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
