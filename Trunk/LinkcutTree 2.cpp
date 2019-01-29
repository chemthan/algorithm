#include <bits/stdc++.h>
using namespace std;

struct Node {
	Node();
	Node *l, *r, *p;
	int size, root, key, cnt;
	int rev, lz;
};
Node* nil = new Node();
Node::Node() {
	l = r = p = nil;
	size = root = cnt = 1;
	key = rev = lz = 0;
}
void init() {
	nil->size = nil->cnt = 0;
}
void setchild(Node* p, Node* c, int l) {
	c->p = p; l ? p->l = c : p->r = c;
}
void updatelz(Node* x, int val) {
	if (x == nil) return;
	x->lz += val;
	x->cnt += val;
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
}
void rotate(Node* x) {
	Node* y = x->p;
	int l = x->p->l == x;
	if (!y->root) {
		setchild(y->p, x, y->p->l == y);
	}
	else {
		x->root = 1;
		y->root = 0;
		x->p = y->p;
	}
	setchild(y, l ? x->r : x->l, l);
	setchild(x, y, !l);
	pushup(y);
}
void splay(Node* x) {
	pushdown(x);
	while (!x->root) {
		pushdown(x->p->p); pushdown(x->p); pushdown(x);
		if (!x->p->root) rotate((x->p->l == x) == (x->p->p->l == x->p) ? x->p : x);
		rotate(x);
	}
	pushup(x);
}
Node* access(Node* x) {
	Node* z = nil;
	for (Node* y = x; y != nil; y = y->p) {
		splay(y);
		y->r->root = 1;
		y->r = z;
		z->root = 0;
		pushup(z = y);
	}
	splay(x);
	return z;
}
void link(Node* x, Node* y) {
	access(y); access(x);
	y->cnt += x->cnt;
	updatelz(y->l, x->cnt);
	x->p = y;
	access(x);
}
void cut(Node* x) {
	access(x);
	x->l->root = 1;
	x->l->p = nil;
	updatelz(x->l, -x->cnt);
	x->l = nil;
	pushup(x);
}
Node* findroot(Node* x) {
	access(x);
	while (x->l != nil) pushdown(x), x = x->l;
	splay(x);
	return x;
}
Node* lca(Node* x, Node* y) {
	if (findroot(x) != findroot(y)) return nil;
	access(x);
	return access(y);
}
void makeroot(Node* x) {
	access(x);
	swap(x->l, x->r);
	x->rev ^= 1;
}
int connected(Node* x, Node* y) {
    if (x == y) return 1;
    access(x); access(y);
    return x->p != nil;
}

const int MAXN = 100000 + 10;
Node node[MAXN];

int main() {
	init();
	int n = 10;
	for (int i = 1; i <= n; i++) {
		node[i].key = i;
	}
	link(node + 2, node + 1);
	link(node + 5, node + 1);
	link(node + 3, node + 2);
	link(node + 4, node + 2);
	link(node + 6, node + 5);
	cout << lca(node + 3, node + 4)->key << "\n";
	cout << findroot(node + 2)->key << "\n";
	cut(node + 3);
	cout << findroot(node + 3)->key << "\n";
	return 0;
}
