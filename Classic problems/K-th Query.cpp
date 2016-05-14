#include <bits/stdc++.h>
using namespace std;

//http://www.spoj.com/problems/MKTHNUM/en/
//Persistent Segment Tree
const int MAXN = 2000010;
struct Node {
	Node *l, *r;
	int L, R, cnt;
	Node();
} mem[MAXN], *nil = mem + MAXN - 1;
Node::Node() {
	l = r = nil;
	L = R = -1;
	cnt = 0;
}
Node* Alloc() {
	static int cur = 0;
	return mem + (cur++);
}
Node* build(int L, int R) {
	Node* node = Alloc();
	node->L = L; node->R = R;
	if (L == R) return node;
	node->l = build(L, (L + R) >> 1);
	node->r = build(((L + R) >> 1) + 1, R);
	return node;
}
Node* update(Node* node, int i, int val) {
	if (node->L > i || node->R < i) return node;
	Node* x = Alloc();
	x->L = node->L; x->R = node->R;
	x->l = node->l; x->r = node->r;
	if (node->L == node->R) {
		x->cnt = node->cnt + val;
		return x;
	}
	x->l = update(x->l, i, val);
	x->r = update(x->r, i, val);
	x->cnt = x->l->cnt + x->r->cnt;
	return x;
}
int query(Node* node, int L, int R) {
	if (node->L > R || node->R < L) return 0;
	if (node->L >= L && node->R <= R) return node->cnt;
	return query(node->l, L, R) + query(node->r, L, R);
}

int n, m;
int a[MAXN];
map<int, int> dc;
int rb[MAXN];
Node* root[MAXN];

int query(Node* x, Node* y, int w) {
	int tot = x->l->cnt - y->l->cnt;
	if (x->L == x->R) {
		return rb[x->L];
	}
	if (w <= tot) {
		return query(x->l, y->l, w);
	}
	else {
		return query(x->r, y->r, w - tot);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m;
	for (int i = 0; i < n; i++) cin>>a[i], dc[a[i]];
	int cnt = 0;
	for (map<int, int>::iterator it = dc.begin(); it != dc.end(); it++) {
		it->second = cnt;
		rb[cnt++] = it->first;
	}
	for (int i = 0; i < n; i++) a[i] = dc[a[i]];
	root[0] = build(0, n - 1);
	for (int i = 0; i < n; i++) {
		root[i + 1] = update(root[i], a[i], 1);
	}
	while (m--) {
		int u, v, w; cin>>u>>v>>w;
		cout<<query(root[v], root[u - 1], w)<<"\n";
	}
	return 0;
}
