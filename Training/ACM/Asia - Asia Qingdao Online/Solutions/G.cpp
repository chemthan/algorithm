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

const int maxn = 100000 + 10;
int n;
long long t;
int a[maxn];

int d;
queue<long long> q[2];

void push(long long k) {
	if (!sz(q[0])) d = 0;
	else if (!sz(q[1])) d = 1;
	q[d].push(k);
}

long long top() {
	if (!sz(q[d])) {
		long long res = q[d ^ 1].front(); q[d ^ 1].pop();
		return res;
	}
	else if (!sz(q[d ^ 1])) {
		long long res = q[d].front(); q[d].pop();
		return res;
	}
	if (q[d].front() < q[d ^ 1].front()) {
		long long res = q[d].front(); q[d].pop();
		return res;
	}
	else {
		long long res = q[d ^ 1].front(); q[d ^ 1].pop();
		return res;
	}
}

int check(int mid) {
	d = 1;
	while (sz(q[0])) q[0].pop();
	while (sz(q[1])) q[1].pop();
	FOR(i, 0, n) q[0].push(a[i]);
	long long sum = 0;
	while (sz(q[0]) + sz(q[1]) >= 2 * mid - 1) {
		long long tot = 0;
		for (int i = 0; i < mid && sz(q[0]) + sz(q[1]) > 0; i++) {
			tot += top();
			chkmin(tot, LINF);
		}
		push(tot);
		sum += tot;
		chkmin(sum, LINF);
	}
	if (sz(q[0]) + sz(q[1]) == mid) {
		while (sz(q[0]) + sz(q[1]) > 0) {
			sum += top();
		}
	}
	else {
		while (sz(q[0]) + sz(q[1]) >= mid) {
			sum += 2 * top();
		}
		while (sz(q[0]) + sz(q[1]) > 0) {
			sum += top();
		}
	}
	return sum <= t;
}

void solve() {
	int test; cin >> test;
	while (test--) {
		cin >> n >> t;
		FOR(i, 0, n) cin >> a[i];
		sort(a, a + n);
		int l = 2, r = n;
		while (l < r) {
			int mid = l + r >> 1;
			if (!check(mid)) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		cout << l << "\n";
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
