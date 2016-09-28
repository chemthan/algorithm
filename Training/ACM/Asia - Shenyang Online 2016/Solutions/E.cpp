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

const int MAXN = 1 << 19;
int fa[MAXN];
int fb[MAXN];
int fc[MAXN << 1];

void fft(int a[], int p, int r, int n) {
	for (int m = n, h; h = m / 2, m >= 2; r = (long long) r * r % p, m = h) {
		for (int i = 0, w = 1; i < h; i++, w = (long long) w * r % p) {
			for (int j = i; j < n; j += m) {
				int k = j + h, x = a[j] - a[k];
				if (x < 0) x += p;
				a[j] += a[k];
				if (a[j] >= p) a[j] -= p;
				a[k] = (long long) w * x % p;
			}
		}
	}
	for (int i = 0, j = 1; j < n - 1; j++) {
		for (int k = n / 2; k > (i ^= k); k /= 2);
		if (j < i) swap(a[i], a[j]);
	}
}
void multiply(int a[], int b[], int c[], int na, int nb) {
	int len = na + nb - 1;
	int k = 0; while ((1 << k) <= 2 * max(na, nb)) k++;
	for (int i = 0; i < (1 << k); i++) fa[i] = fb[i] = 0;
	for (int i = 0; i < na; i++) fa[i] = a[i];
	for (int i = 0; i < nb; i++) fb[i] = b[i];
	int p = 1004535809;
	int w = fpow(3, (p - 1) / (1 << k), p);
	fft(fa, p, w, 1 << k);
	fft(fb, p, w, 1 << k);
	for (int i = 0; i < (1 << k); i++) fc[i] = (long long) fa[i] * fb[i] % p;
	fft(fc, p, inv(w, p), 1 << k);
	int rem = inv(1 << k, p);
	for (int i = 0; i < (1 << k); i++) c[i] = (long long) fc[i] * rem % p;
}

const int maxn = 1 << 19;
const int mod = 1004535809;
int n;
int a[maxn];
int b[maxn];
int c[maxn << 1];
int fac[maxn];
int ifac[maxn];

void solve() {
	fac[0] = 1; FOR(i, 1, maxn) fac[i] = mult(fac[i - 1], i, mod);
	FOR(i, 0, maxn) ifac[i] = inv(fac[i], mod);
	FOR(i, 0, maxn) {
		if (!i) b[i] = 1;
		else b[i] = mult(fpow(i + 1, i - 1, mod), ifac[i], mod);
	}
	a[0] = 1;
	n = 20000 + 10;
	for (int i = 0; i < n; i++) {
		if (i) {
			a[i] = mult(a[i], inv(i, mod), mod);
		}
		a[i + 1] = (a[i + 1] + (long long) a[i] * b[0]) % mod;
		a[i + 2] = (a[i + 2] + (long long) a[i] * b[1]) % mod;
		for (int k = 2; i && i % k == 0; k <<= 1) {
			multiply(a + i - k, b + k, c, k, k);
			for (int j = i + 1; j < i + 2 * k; j++) {
				a[j] = (a[j] + c[j - i - 1]) % mod;
			}
		}
	}
	int test; cin >> test;
	while (test--) {
		int n; cin >> n;
		int ans = fpow(2, (long long) n * (n - 1) / 2, mod);
		submod(ans, mult(a[n], fac[n], mod), mod);
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
