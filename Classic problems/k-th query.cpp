#include <bits/stdc++.h>
using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define FORd(i, a, b) for(int i = (a) - 1; i >= (b); i--)
#define sz(a) int((a).size())
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
ll gcd(ll a, ll b) {ll r; while (b != 0) {r = a % b; a = b; b = r;} return a;}
ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
const int mod = 1000000007;
const int INF = (int) 1e9;
const ll LINF = (ll) 1e18;

//http://www.spoj.com/problems/MKTHNUM/en/
//Persistent segment tree
struct node
{
	int cnt;
	node *left, *right;
	node() {cnt = 0; left = right = NULL;}
	node(int cnt, node* left, node* right): cnt(cnt), left(left), right(right) {}
	node* insert(int l, int r, int w);
};

node* null = new node(0, NULL, NULL);

node* node::insert(int l, int r, int w)
{
	if (l <= w && w <= r)
	{
		if (l == r) return new node(this->cnt + 1, null, null);
		int m = (l + r) >> 1;
		return new node(this->cnt + 1, this->left->insert(l, m, w), this->right->insert(m + 1, r, w));
	}
	return this;
}

int query(node* a, node* b, int l, int r, int k)
{
	if (l == r) return l;
	int m = (l + r) >> 1;
	int cnt = a->left->cnt - b->left->cnt;
	if (cnt >= k) return query(a->left, b->left, l, m, k);
	return query(a->right, b->right, m + 1, r, k - cnt);
}

const int maxn = 100010;
int n, m;
int a[maxn], rm[maxn];
node* root[maxn];
map<int, int> mp;

void solve() {
	scanf("%d%d", &n, &m);
	FOR(i, 0, n) {
		scanf("%d", &a[i]);
		mp[a[i]];
	}
	int cnt = 0;
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
	{
		mp[it->first] = cnt;
		rm[cnt] = it->first;
		cnt++;
	}
	null->left = null->right = null;
	FOR(i, 0, n) root[i] = (i == 0 ? null : root[i - 1])->insert(0, cnt - 1, mp[a[i]]);
	while (m--) {
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k); u--; v--;
		int ans = query(root[v], (u == 0 ? null : root[u - 1]), 0, cnt - 1, k);
		printf("%d\n", rm[ans]);
	}
}

int main() {
	//ios_base::sync_with_stdio(0); cin.tie(NULL);
#ifdef _LOCAL_
	freopen("in.txt", "r", stdin); //freopen("out.txt", "w", stdout);
#endif
	solve();
#ifdef _LOCAL_
	//printf("\nTime elapsed: %dms", 1000 * clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
