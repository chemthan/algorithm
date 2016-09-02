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

struct RMQ {
	static const int MAXN = 500000 + 10;
	static const int LOGN = 20;
	int n;
	int a[MAXN];
	int f[MAXN][LOGN];
	void build() {
		for (int i = 0; i < n; i++) f[i][0] = a[i];
		for (int l = 0, k; (k = 1 << l) < n; l++) {
			for (int i = 0; i + k < n; i++) {
				f[i][l + 1] = min(f[i][l], f[i + k][l]);
			}
		}
	}
	int query(int a, int b) {
		int l = a == b ? 0 : __lg(b - a);
		return min(f[a][l], f[b - (1 << l) + 1][l]);
	}
} rmq;

struct SuffixArray {
	static const int MAXN = 500000 + 10;
	char T[MAXN];
	int nsz;
	int RA[MAXN], tmpRA[MAXN];
	int SA[MAXN], tmpSA[MAXN];
	int c[MAXN];
	int Phi[MAXN], PLCP[MAXN];
	int LCP[MAXN];
	void init(char* str) {
		strcpy(T, str);
		nsz = strlen(T);
		for (int i = 0; i < nsz; i++) {
			RA[i] = tmpRA[i] = 0;
			SA[i] = tmpSA[i] = 0;
			Phi[i] = PLCP[i] = LCP[i] = 0;
		}
		constructSA();
		computeLCP();
	}
	void countingsort(int k) {
		int sum = 0, maxi = max(300, nsz);
		memset(c, 0, sizeof(c));
		for (int i = 0; i < nsz; i++) c[i + k < nsz ? RA[i + k] : 0]++;
		for (int i = 0; i < maxi; i++) {
			int t = c[i]; c[i] = sum; sum += t;
		}
		for (int i = 0; i < nsz; i++) tmpSA[c[SA[i] + k < nsz ? RA[SA[i] + k] : 0]++] = SA[i];
		for (int i = 0; i < nsz; i++) SA[i] = tmpSA[i];
	}
	void constructSA() {
		int r;
		for (int i = 0; i < nsz; i++) RA[i] = T[i];
		for (int i = 0; i < nsz; i++) SA[i] = i;
		for (int k = 1; k < nsz; k <<= 1) {
			countingsort(k);
			countingsort(0);
			tmpSA[SA[0]] = r = 0;
			for (int i = 1; i < nsz; i++) tmpRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
			for (int i = 0; i < nsz; i++) RA[i] = tmpRA[i];
			if (RA[SA[nsz - 1]] == nsz - 1) break;
		}
	}
	void computeLCP() {
		int L = 0;
		Phi[SA[0]] = -1;
		for (int i = 1; i < nsz; i++) Phi[SA[i]] = SA[i - 1];
		for (int i = 0; i < nsz; i++) {
			if (!~Phi[i]) {PLCP[i] = 0; continue;}
			while (T[i + L] == T[Phi[i] + L] && T[i + L] != '$') L++;
			PLCP[i] = L;
			L = max(L - 1, 0);
		}
		for (int i = 0; i < nsz; i++) LCP[i] = PLCP[SA[i]];
	}
} sa;

const int maxn = 500000 + 10;
int n, q;
int cnt;
char s[maxn];
int st1[maxn];
int st2[maxn];
int len1[maxn];
int len2[maxn];

int querylow(int ix, int len) {
	int l = 0, r = ix;
	while (l < r) {
		int m = l + r >> 1;
		if (m < ix && rmq.query(m + 1, ix) < len) {
			l = m + 1;
		}
		else {
			r = m;
		}
	}
	return l;
}

int queryhigh(int ix, int len) {
	int l = ix, r = cnt - 1;
	while (l < r) {
		int m = l + r + 1 >> 1;
		if (m == ix || rmq.query(ix + 1, m) >= len) {
			l = m;
		}
		else {
			r = m - 1;
		}
	}
	return l;
}

int compare(int i, int j) {
	int u = st1[i];
	int v = st1[j];
	int ru = sa.RA[u];
	int rv = sa.RA[v];
	if (len1[i] != len1[j]) return len1[i] < len1[j];
	if (ru == rv) {
		return i < j;
	}
	if (ru > rv) {
		if (rmq.query(rv + 1, ru) == len1[i]) {
			return i < j;
		}
		else {
			return ru < rv;
		}
	}
	else if (ru < rv) {
		if (rmq.query(ru + 1, rv) == len1[i]) {
			return i < j;
		}
		else {
			return ru < rv;
		}
	}
}

vi st[maxn << 2];
void upd(int p, int i, int L, int R, int val) {
	if (i < L || i > R) return;
	st[p].pb(val);
	if (L < R) {
		upd(p << 1, i, L, L + R >> 1, val);
		upd(p << 1 | 1, i, (L + R >> 1) + 1, R, val);
	}
}
void build(int p, int L, int R) {
	sort(all(st[p]), compare);
	uni(st[p]);
	while (sz(st[p]) > 10) st[p].pop_back();
	if (L < R) {
		build(p << 1, L, L + R >> 1);
		build(p << 1 | 1, (L + R >> 1) + 1, R);
	}
}
vi merge(vi a, vi b) {
	vi res = a;
	res.insert(res.end(), all(b));
	sort(all(res), compare);
	uni(res);
	while (sz(res) > 10) res.pop_back();
	return res;
}
vi query(int p, int l, int r, int L, int R) {
	if (l > R || r < L) return vi();
	if (l <= L && r >= R) return st[p];
	return merge(query(p << 1, l, r, L, L + R >> 1), query(p << 1 | 1, l, r, (L + R >> 1) + 1, R));
}

void solve() {
	cin >> n;
	FOR(i, 0, n) {
		string t; cin >> t;
		st1[i] = cnt;
		len1[i] = sz(t);
		FOR(j, 0, sz(t)) {
			s[cnt++] = t[j];
		}
		s[cnt++] = '$';
	}
	cin >> q;
	FOR(i, 0, q) {
		string t; cin >> t;
		st2[i] = cnt;
		len2[i] = sz(t);
		FOR(j, 0, sz(t)) {
			s[cnt++] = t[j];
		}
		s[cnt++] = '$';
	}
	sa.init(s);
	rmq.n = cnt;
	FOR(i, 0, cnt) {
		rmq.a[i] = sa.LCP[i];
	}
	rmq.build();
	FOR(i, 0, n) {
		FOR(j, 0, len1[i]) {
			int u = sa.RA[st1[i] + j];
			upd(1, u, 0, cnt - 1, i);
		}
	}
	build(1, 0, cnt - 1);
	FOR(i, 0, q) {
		int u = sa.RA[st2[i]];
		int l = querylow(u, len2[i]);
		int r = queryhigh(u, len2[i]);
		vi res = query(1, l, r, 0, cnt - 1);
		if (!sz(res)) {
			cout << "-1\n";
		}
		else {
			FOR(i, 0, sz(res)) cout << res[i] + 1 << " \n"[i == sz(res) - 1];
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
