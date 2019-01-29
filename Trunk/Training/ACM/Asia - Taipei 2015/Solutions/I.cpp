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

const int maxn = 100000 + 10;
int n;
string s;
int dj[maxn];
int mx[maxn];
int sum[maxn];

void init() {
	FOR(i, 0, n) dj[i] = i, mx[i] = 1;
}
int find(int u) {
	return dj[u] == u ? dj[u] : dj[u] = find(dj[u]);
}
int join(int u, int v, int d) {
	int p = find(u);
	int q = find(v);
	dj[q] = p;
	if (!d) {
		mx[p] += mx[q];
	}
	else {
		chkmax(mx[p], mx[q]);
	}
	return p;
}

int solve(int l, int r) {
	if (s[l] != '(') {
		stringstream ss(s.substr(l, r - l + 1));
		int k; ss >> k;
		return k;
	}
	FOR(i, l, r + 1) {
		int tot = sum[i] - (l ? sum[l - 1] : 0);
		if (tot == 0) {
			int x = solve(l + 1, i - 1);
			int y = solve(i + 3, r - 1);
			if (s[i + 1] == 'J') {
				return join(x, y, 1);
			}
			else {
				return join(x, y, 0);
			}
		}
	}
}

void solve() {
	int test; cin >> test;
	while (test--) {
		cin >> n;
		init();
		cin >> s;
		stack<int> st;
		int tot = 0;
		FOR(i, 0, sz(s)) {
			if (s[i] == '(') {
				tot++;
			}
			else if (s[i] == ')') {
				tot--;
			}
			sum[i] = tot;
		}
		int r = solve(0, sz(s) - 1);
		cout << n - mx[r] + 1 << "\n";
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
