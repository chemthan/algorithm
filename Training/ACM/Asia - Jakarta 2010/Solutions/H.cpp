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

const int MAXN = 100 + 10;
const int MAXC = 10;
struct Node {
	Node* parent;
	Node* child[MAXC];
	Node* bfail;
	Node* gfail;
	int key;
	char val;
	Node() {
		bfail = 0;
		key = -1;
	}
} node[MAXN];
Node* alloc = node;
Node* q[MAXN];
Node* root = alloc++;
Node* insert(Node* x, char* s, int key) {
	while (*s) {
		int c = *s - '0';
		if (!x->child[c]) {
			x->child[c] = alloc++;
			x->child[c]->val = c;
			x->child[c]->parent = x;
		}
		x = x->child[c];
		s++;
	}
	x->key = key;
	return x;
}
void pushlink(Node* root) {
	int b = 0, e = 0;
	q[e++] = root;
	while (b < e) {
		Node* x = q[b++];
		for (int i = 0; i < MAXC; i++) {
			if (x->child[i]) q[e++] = x->child[i];
		}
		if (x == root || x->parent == root) {
			x->bfail = root;
			x->gfail = 0;
		}
		else {
			x->bfail = x->parent->bfail;
			while (x->bfail != root && !x->bfail->child[x->val]) x->bfail = x->bfail->bfail;
			if (x->bfail->child[x->val]) x->bfail = x->bfail->child[x->val];
			if (x->bfail->key != -1) x->gfail = x->bfail;
			else x->gfail = x->bfail->gfail;
		}
	}
}

const int maxd = 11 + 1;
int dd;
int dig[maxd];
long long f[maxd][MAXN][2][2];

long long calc(int pos, int p, int a, int z) {
	if (pos == dd) return z;
	long long& res = f[pos][p][a][z];
	if (~res) return res;
	res = 0;
	int lo = 0, hi = 9;
	if (!a) chkmin(hi, dig[pos]);
	FOR(i, lo, hi + 1) {
		if (!i && !z) {
			res += calc(pos + 1, p, a | i < dig[pos], z);
		}
		else {
			Node* cur = node + p;
			while (cur != root && !cur->child[i]) cur = cur->bfail;
			cur = cur->child[i];
			if (!cur) {
				res += calc(pos + 1, 0, a | i < dig[pos], 1);
			}
			else {
				if (cur->key == -1 && !cur->gfail) {
					res += calc(pos + 1, cur - root, a | i < dig[pos], 1);
				}
			}
		}
	}
	return res;
}

long long calc(long long m) {
	ms(dig, 0);
	dd = 0;
	while (m) {
		dig[dd++] = m % 10;
		m /= 10;
	}
	reverse(dig, dig + dd);
	FOR(i, 0, dd) FOR(j, 0, alloc - node) FOR(k, 0, 2) FOR(l, 0, 2) f[i][j][k][l] = -1;
	return calc(0, 0, 0, 0);
}

void solve() {
	int test; cin >> test;
	while (test--) {
		ms(node, 0); alloc = node + 1;
		FOR(i, 0, MAXN) node[i].key = -1;
		int k; cin >> k;
		FOR(i, 0, k) {
			char s[20] = {};
			cin >> s;
			insert(root, s, 0);
		}
		pushlink(root);
		int n; cin >> n;
		FOR(i, 0, n) {
			long long x; cin >> x;
			long long l = 1, r = (long long) 3e9;
			while (l < r) {
				long long m = l + r >> 1;
				if (calc(m) < x) l = m + 1; else r = m;
			}
			cout << l << " \n"[i == n - 1];
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
