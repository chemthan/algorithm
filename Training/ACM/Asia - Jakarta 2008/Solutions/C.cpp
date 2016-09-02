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
const int maxl = 30 + 5;
int l, n;
int p[maxl];
int k[maxn];
int b[maxn][maxl];

int ntrie;
map<int, int> node[maxn * maxl];
int val[maxn * maxl];

void add(int ix) {
	int cur = 0;
	FOR(i, 0, k[ix]) {
		if (!node[cur][b[ix][i]]) {
			node[cur][b[ix][i]] = ++ntrie;
			val[ntrie] = 0;
		}
		cur = node[cur][b[ix][i]];
	}
	val[cur] += p[k[ix]];
}

pair<int, string> best;

string get(string s) {
	int msk = 0;
	FOR(i, 0, sz(s)) msk |= 1 << (s[i] - '0');
	FOR(i, 1, l + 1) if (!bit(msk, i)) {
		s += char('0' + i);
	}
	return s;
}

void trace(int cur, int tot, string s, int msk) {
	if (bitcount(msk) == l) {
		chkmin(best, mp(tot, get(s)));
		return;
	}
	FOR(i, 1, l + 1) if (!bit(msk, i)) {
		if (!node[cur][i]) {
			chkmin(best, mp(tot, get(s + char('0' + i))));
		}
		else {
			trace(node[cur][i], tot + val[node[cur][i]], s + char('0' + i), msk | (1 << i));
		}
	}
}

void solve() {
	int test; cin >> test;
	while (test--) {
		cin >> l >> n;
		FOR(i, 0, ntrie + 1) node[i].clear();
		fill_n(val, ntrie + 1, 0);
		ntrie = 0;
		FOR(i, 1, l + 1) cin >> p[i];
		FOR(i, 0, n) {
			cin >> k[i];
			FOR(j, 0, k[i]) {
				cin >> b[i][j];
			}
			add(i);
		}
		best = mp(INF, "");
		trace(0, 0, "", 0);
		FOR(i, 0, l) cout << best.se[i] - '0' << " \n"[i == l - 1];
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
