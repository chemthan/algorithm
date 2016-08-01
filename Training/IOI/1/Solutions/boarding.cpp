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

struct Node {
	Node();
	Node *l, *r, *p;
	int size, key, val;
	int rev, lz;
};
Node* nil = new Node();
Node::Node() {
	l = r = p = nil;
	size = 1; key = rev = lz = 0;
}
void init() {
	nil->l = nil->r = nil->p = nil;
	nil->size = 0; nil->val = -INF;
}
int isrt(Node* x) {
	return x->p == nil || (x->p->l != x && x->p->r != x);
}
void setchild(Node* p, Node* c, int l) {
	c->p = p; l ? p->l = c : p->r = c;
}
void updatelz(Node* x, int val) {
	if (x == nil) return;
	x->lz += val;
	x->key += val;
	x->val += val;
}
void pushdown(Node* x) {
	if (x == nil) return;
	Node *u = x->l, *v = x->r;
	if (x->rev) {
		if (u != nil) {swap(u->l, u->r); u->rev ^= 1;}
		if (v != nil) {swap(v->l, v->r); v->rev ^= 1;}
		x->rev = 0;
	}
	if (x->lz) {
		if (u != nil) updatelz(u, x->lz);
		if (v != nil) updatelz(v, x->lz);
		x->lz = 0;
	}
}
void pushup(Node* x) {
	x->size = x->l->size + x->r->size + 1;
	x->val = x->key;
	x->val = max(x->val, x->l->val);
	x->val = max(x->val, x->r->val);
}
void rotate(Node* x) {
	Node* y = x->p;
	int l = x->p->l == x;
	if (!isrt(y)) {
		setchild(y->p, x, y->p->l == y);
	}
	else {
		x->p = y->p;
	}
	setchild(y, l ? x->r : x->l, l);
	setchild(x, y, !l);
	pushup(y);
}
void splay(Node* x) {
	pushdown(x);
	while (!isrt(x)) {
		pushdown(x->p->p); pushdown(x->p); pushdown(x);
		if (!isrt(x->p)) rotate((x->p->l == x) == (x->p->p->l == x->p) ? x->p : x);
		rotate(x);
	}
	pushup(x);
}

const int MAXN = 400010;
struct SplayTree {
	Node mem[MAXN], *root;
	int cur;
	SplayTree() {
		root = nil; cur = 0;
		init();
	}
	Node* alloc(int key) {
		mem[cur].key = key;
		mem[cur].val = key;
		return mem + (cur++);
	}
	Node* insert(Node* x, int key) {
		Node* p = nil;
		while (x != nil) {
			pushdown(x);
			p = x;
			if (x->key < key) x = x->r;
			else x = x->l;
		}
		x = alloc(key);
		x->p = p;
		if (p == nil) {
			root = x;
		}
		else if (p->key < x->key) p->r = x;
		else p->l = x;
		splay(x);
		return root = x;
	}
	Node* insert(int key) {
		return insert(root, key);
	}
	Node* findkey(Node* x, int key) {
		while (x != nil) {
			pushdown(x);
			if (x->key < key) x = x->r;
			else if (key < x->key) x = x->l;
			else return x;
		}
		return nil;
	}
	Node* findkey(int key) {
		return findkey(root, key);
	}
	Node* findpos(Node* x, int pos) {
		while (1) {
			pushdown(x);
			int k = x->l ? x->l->size + 1 : 1;
			if (pos == k) return x;
			else if (pos < k) x = x->l;
			else {x = x->r; pos -= k;}
		}
		return nil;
	}
	Node* findpos(int pos) {
		return findpos(root, pos);
	}
	Node* join(Node* x, Node* y) {
		if (x == nil) return root = y;
		if (y == nil) return root = x;
		pushdown(y);
		while (1) {
			pushdown(x);
			if (x->r == nil) break;
			x = x->r;
		}
		splay(x);
		setchild(x, y, 0);
		pushup(x);
		return root = x;
	}
	void split(Node* x, int pos, Node*& l, Node*& r) {
		if (!pos) {l = nil; r = x; return;}
		Node* y = findpos(x, pos);
		splay(y);
		if ((r = y->r) != nil) r->p = nil;
		if ((l = y) != nil) {l->r = nil; pushup(l);}
	}
	void split(Node* t, int pos1, int pos2, Node*& t1, Node*& t2, Node*& t3) {
		split(t, pos1 - 1, t1, t2);
		split(t2, pos2 - pos1 + 1, t2, t3);
	}
	void reverse(int l, int r) {
		Node *x, *y, *z, *t;
		split(root, r, t, z);
		split(t, l - 1, x, y);
		if (y) {
			swap(y->l, y->r);
			y->rev ^= 1;
		}
		join(join(x, y), z);
	}
	void update(int l, int r, int val) {
		Node *x, *y, *z;
		split(root, l, r, x, y, z);
		updatelz(y, val);
		join(join(x, y), z);
	}
	void update(int k, int val) {
		Node *x, *y, *z;
		split(root, 2, k + 1, x, y, z);
		x->key = val;
		updatelz(y, 1);
		join(join(y, x), z);
	}
	int query(int l, int r) {
		Node *x, *y, *z;
		split(root, l, r, x, y, z);
		int res = y->val;
		join(join(x, y), z);
		return res;
	}
	void trace(Node* x) {
		if (x == nil) return;
		pushdown(x);
		trace(x->l);
		cout<<x->key<<" ";
		trace(x->r);
	}
	void trace() {
		trace(root);
		cout<<"\n";
	}
} slt;

const int maxn = 200010;
int n;
int s[maxn];
int t[maxn];

void solve() {
	if (fopen("boarding.in", "r")) {
		freopen("boarding.in", "r", stdin);
		freopen("boarding.out", "w", stdout);
	}
	cin >> n;
	FOR(i, 0, n) cin >> s[i] >> t[i];
	FOR(i, 0, n << 1) {
		if (i != n - 1) {
			slt.join(slt.root, slt.alloc(-INF));
		}
		else {
			slt.join(slt.root, slt.alloc(0));
		}
	}
	int ans = 0;
	FORd(i, n, 0) {
		int tmp = slt.query(1, s[i] + n - 1);
		chkmax(ans, tmp + s[i] + t[i]);
		slt.update(s[i] + n - 2, tmp + t[i] + 1);
	}
	cout << ans << "\n";
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
