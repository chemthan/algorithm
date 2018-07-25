#include <bits/stdc++.h>
using namespace std;

struct Node {
	Node *l, *r, *p;
	int key, size;
	int rev, lz;
	Node(int key = 0) : key(key) {
		l = r = p = 0;
		size = 1;
		rev = lz = 0;
	}
	~Node() {
		if (l) delete l;
		if (r) delete r;
	}
} *root;
int size(Node* x) {
	return x ? x->size : 0;
}
void setchild(Node* p, Node* c, int l) {
	c->p = p; l ? p->l = c : p->r = c;
}
void updatelz(Node* x, int val) {
	if (!x) return;
	x->lz += val;
	x->key += val;
}
void pushdown(Node* x) {
	if (!x) return;
	Node *u = x->l, *v = x->r;
	if (x->rev) {
		if (u) {swap(u->l, u->r); u->rev ^= 1;}
		if (v) {swap(v->l, v->r); v->rev ^= 1;}
		x->rev = 0;
	}
	if (x->lz) {
		if (u) updatelz(u, x->lz);
		if (v) updatelz(v, x->lz);
		x->lz = 0;
	}
}
void pushup(Node*& x) {
	if (!x) return;
	x->size = size(x->l) + size(x->r) + 1;
}
void lrotate(Node* x) {
	Node* y = x->r;
	if (y) {
		x->r = y->l;
		if (y->l) y->l->p = x;
		y->p = x->p;
	}
	if (!x->p) root = y;
	else if (x == x->p->l) x->p->l = y;
	else x->p->r = y;
	if (y) y->l = x;
	x->p = y;
	pushup(x); pushup(y);
}
void rrotate(Node* x) {
	Node* y = x->l;
	if (y) {
		x->l = y->r;
		if (y->r) y->r->p = x;
		y->p = x->p;
	}
	if (!x->p) root = y;
	else if (x == x->p->l) x->p->l = y;
	else x->p->r = y;
	if (y) y->r = x;
	x->p = y;
	pushup(x); pushup(y);
}
void splay(Node* x) {
	while (x->p) {
		if (!x->p->p) {
			if (x->p->l == x) rrotate(x->p);
			else lrotate(x->p);
		}
		else if (x->p->l == x && x->p->p->l == x->p) {
			rrotate(x->p->p);
			rrotate(x->p);
		}
		else if (x->p->r == x && x->p->p->r == x->p) {
			lrotate(x->p->p);
			lrotate(x->p);
		}
		else if (x->p->l == x && x->p->p->r == x->p) {
			rrotate(x->p);
			lrotate(x->p);
		}
		else {
			lrotate(x->p);
			rrotate(x->p);
		}
	}
}
void replace(Node* u, Node* v) {
	if (!u->p) root = v;
	else if (u == u->p->l) u->p->l = v;
	else u->p->r = v;
	if (v) v->p = u->p;
}
Node* minsubtree(Node* u) {
	while (u->l) u = u->l;
	return u;
}
Node* maxsubtree(Node* u) {
	while (u->r) u = u->r;
	return u;
}
void insert(int key) {
	Node* z = root;
	Node* p = 0;
	while (z) {
		pushdown(z);
		p = z;
		if (z->key < key) z = z->r;
		else z = z->l;
	}
	z = new Node(key);
	z->p = p;
	if (!p) root = z;
	else if (p->key < z->key) p->r = z;
	else p->l = z;
	splay(z);
}
Node* find(int key) {
	Node* z = root;
	while (z) {
		pushdown(z);
		if (z->key < key) z = z->r;
		else if (key < z->key) z = z->l;
		else return z;
	}
	return 0;
}
void erase(int key) {
	Node* z = find(key);
	if (!z) return;
	splay(z);
	pushdown(z);
	if (!z->l) replace(z, z->r);
	else if (!z->r) replace(z, z->l);
	else {
		Node* y = minsubtree(z->r);
		if (y->p != z) {
			replace(y, y->r);
			y->r = z->r;
			y->r->p = y;
		}
		replace(z, y);
		y->l = z->l;
		y->l->p = y;
	}
	delete z;
}
Node* join(Node* x, Node* y) {
	if (!x) return y;
	if (!y) return x;
	pushdown(y);
	while (1) {
		pushdown(x);
		if (!x->r) break;
		x = x->r;
	}
	splay(x);
	setchild(x, y, 0);
	pushup(x);
	return x;
}
void split(int i, Node*& x, Node*& y) {
	if (!i) {
		x = 0;
		y = root;
		return;
	}
	Node* z = find(i);
	splay(z);
	y = z->r; y->p = 0;
	x = z; x->r = 0;
	pushup(x);
}
Node* find(Node* x, int pos) {
	while (1) {
		pushdown(x);
		int k = x->l ? x->l->size + 1 : 1;
		if (pos == k) return x;
		if (pos < k) x = x->l;
		else {x = x->r; pos -= k;}
	}
	return 0;
}
void split(Node* x, int pos, Node*& l, Node*& r) {
	if (pos == 0) {
		l = 0;
		r = x;
		return;
	}
	Node* y = find(x, pos);
	splay(y);
	if (r = y->r) r->p = 0;
	if (l = y) {l->r = 0; pushup(l);}
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
	root = join(join(x, y), z);
}
void update(int l, int r, int val) {
	Node *x, *y, *z;
	split(root, l, r, x, y, z);
	updatelz(y, val);
	root = join(join(x, y), z);
}
void trace(Node* x) {
	if (!x) return;
	pushdown(x);
	trace(x->l);
	cout << x->key << " ";
	trace(x->r);
}
void trace() {
	trace(root);
	cout << "\n";
}

int main() {
	insert(3); insert(4); insert(5);
	reverse(1, 2);
	trace();
	update(1, 3, 1);
	trace();
	return 0;
}
