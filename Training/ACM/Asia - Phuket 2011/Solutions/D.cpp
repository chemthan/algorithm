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

const int BASE = 1000000000;
const int NBLOCK = 9;
struct Bigint {
	vector<int> data;
	Bigint() {data.push_back(0);}
	Bigint(long long x) {
		if (!x) data.push_back(0);
		while (x) data.push_back(x % BASE), x /= BASE;
	}
	void trim() {while (data.size() > 1 && !data.back()) data.pop_back();}
	int& operator[] (int i) {return data[i];}
	int len() {return data.size();}
	int iszero() const {return data.empty() || (data.size() == 1 && !data[0]);}
};
Bigint operator + (Bigint a, Bigint b) {
	if (a.len() < b.len()) swap(a, b);
	Bigint c; c.data = a.data, c.data.push_back(0);
	int r = 0;
	for (int i = 0; i < c.len(); i++) {
		c[i] += ((i < b.len()) ? b[i] : 0) + r;
		if ((r = (c[i] >= BASE))) c[i] -= BASE;
	}
	c.trim();
	return c;
}
Bigint operator * (Bigint a, int m) {
	long long r = 0;
	for (int i = 0; i < a.len(); i++) {
		r += (long long) a[i] * m;
		a[i] = r % BASE;
		r /= BASE;
	}
	while (r) a.data.push_back(r % BASE), r /= BASE;
	a.trim();
	return a;
}
pair<Bigint, int> divmod(Bigint a, int m) {
	long long r = 0;
	for (int i = a.len() - 1; i >= 0; i--) {
		r = r * BASE + a[i];
		a[i] = r / m;
		r %= m;
	}
	a.trim();
	return make_pair(a, (int) r);
}
Bigint operator / (Bigint a, int m) {
	return divmod(a, m).first;
}
int operator % (Bigint a, int m) {
	return divmod(a, m).second;
}
Bigint operator * (const Bigint& a, const Bigint& b) {
	Bigint res;
	res.data.assign(a.data.size() + b.data.size(), 0);
	for (int i = 0; i < a.data.size(); i++) {
		long long carry = 0;
		for (int j = 0; j < b.data.size() || carry > 0; j++) {
			long long s = res[i + j] + carry + (long long) a.data[i] * (j < b.data.size() ? (long long) b.data[j] : 0);
			res[i + j] = s % BASE;
			carry = s / BASE;
		}
	}
	res.trim();
	return res;
}
string tostring (Bigint& B) {
	string ans = "";
	int tmp = B.data.back();
	string tt = "";
	FOR(j, 0, 9) {
		tt += '0' + tmp % 10;
		tmp /= 10;
	}
	reverse(all(tt));
	ans += tt;
	for (int i = (int) B.data.size() - 2; i >= 0; i--) {
		int tmp = B.data[i];
		string tt = "";
		FOR(j, 0, 9) {
			tt += '0' + tmp % 10;
			tmp /= 10;
		}
		reverse(all(tt));
		ans += tt;
	}
	reverse(all(ans));
	while (sz(ans) > 1 && ans[sz(ans) - 1] == '0') ans = ans.substr(0, sz(ans) - 1);
	reverse(all(ans));
	return ans;
}

const int MAXN = 8000 + 10;
int fl[MAXN];
int sp[MAXN];
void Sieve() {
	for (int i = 2; i < MAXN; i += 2) sp[i] = 2;
	for (int i = 3; i < MAXN; i += 2) if (!fl[i]) {
		sp[i] = i;
		for (int j = i; (long long) i * j < MAXN; j += 2) if (!fl[i * j]) {
			fl[i * j] = 1;
			sp[i * j] = i;
		}
	}
}

const int maxn = 8000 + 10;
Bigint A[maxn];
int mx[maxn];

void solve() {
	Sieve();
	A[0] = Bigint(1);
	FOR(i, 1, maxn) {
		int tmp = i;
		map<int, int> hs;
		while (tmp > 1) {
			hs[sp[tmp]]++;
			tmp /= sp[tmp];
		}
		tmp = 1;
		FORall(it, hs) {
			int tot = max(0, it->se - mx[it->fi]);
			while (tot--) tmp *= it->fi;
			chkmax(mx[it->fi], it->se);
		}
		A[i] = A[i - 1] * tmp;
	}
	int n, t;
	while (cin >> n >> t) {
		if (!n && !t) break;
		if (t == 1) {
			FOR(i, 0, n) cout << "1";
			cout << "\n";
		}
		else {
			string ans = tostring(A[t]);
			FORd(i, sz(ans), 0) {
				if (ans[i] != '0') {
					ans[i] = ans[i] - 1;
					break;
				}
				else {
					ans[i] = '9';
				}
			}
			while (sz(ans) < n) ans = ans + "9";
			cout << ans << "\n";
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
