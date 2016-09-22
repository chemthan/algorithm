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

typedef long long T;
T mulmod64(T a, T b, T p) {
	T q = T((long double) a * b / p);
    T r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
}
T powmod64(T n, T k, T p) {
	if (!n) return 0;
	T r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = mulmod64(r, n, p);
		n = mulmod64(n, n, p);
	}
	return r;
}
int rabin(T n) {
	if (n == 2) return 1;
	if (n < 2 || !(n & 1)) return 0;
	const T p[] = {2, 3, 5, 7};
	T a, d = n - 1, mx = 4;
	int i, r, s = 0;
	while (!(d & 1)) {++s; d >>= 1;}
	for (i = 0; i < mx; i++) {
		if (n == p[i]) return 1;
		if (!(n % p[i])) return 0;
		a = powmod64(p[i], d, n);
		if (a != 1) {
			for (r = 0; r < s && a != n - 1; r++) a = mulmod64(a, a, n);
			if (r == s) return 0;
		}
	}
	return 1;
}
T pollardrho(T n) {
	int it = 0, k = 2;
	T x = 3, y = 3;
	while (1) {
		it++;
		x = (mulmod64(x, x, n) + n - 1) % n;
		T d = __gcd(abs(y - x), n);
		if (d != 1 && d != n) return d;
		if (it == k) y = x, k <<= 1;
	}
}

map<long long, int> hs;
long long k;

void calc(long long k) {
	while (k > 1) {
		if (k <= 10000000) {
			for (int i = 2; i * i <= k; i++) {
				if (k % i) continue;
				while (k % i == 0) {
					hs[i]++;
					k /= i;
				}
			}
			if (k > 1) hs[k]++;
			k = 1;
		}
		else if (rabin(k)) {
			hs[k]++;
			k = 1;
		}
		else {
			long long pr = pollardrho(k);
			if(rabin(pr)) {
				hs[pr]++;
			}
			else {
				calc(pr);
			}
			k /= pr;
		}
	}
}

void solve() {
	while (cin >> k) {
		if (!k) break;
		hs.clear();
		while (!(k & 1)) k >>= 1;
		calc(k);
		long long ans = 1;
		FORall(it, hs) {
			ans *= 2 * it->se + 1;
		}
		ans <<= 1;
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
