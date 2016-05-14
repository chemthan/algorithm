#include <bits/stdc++.h>
using namespace std;

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
Node* alloc() {
	static int cur = 0;
	return mem + (cur++);
}
Node* build(int L, int R) {
	Node* node = alloc();
	node->L = L; node->R = R;
	if (L == R) return node;
	node->l = build(L, (L + R) >> 1);
	node->r = build(((L + R) >> 1) + 1, R);
	return node;
}
Node* update(Node* node, int i, int val) {
	if (node->L > i || node->R < i) return node;
	Node* x = alloc();
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

Node* root[MAXN];

int main() {
	int n = 10;
	root[0] = build(0, n - 1);
	root[1] = update(root[0], 2, 4);
	root[2] = update(root[1], 3, 1);
	cout<<query(root[2], 0, 3)<<"\n";
	return 0;
}
