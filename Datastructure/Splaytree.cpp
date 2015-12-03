#include <bits/stdc++.h>
using namespace std;

struct node {
	node *l, *r, *p;
	int key, size, rev;
	node(int key = 0) : l(0), r(0), p(0), key(key), size(1), rev(0) {}
	~node() {
		if (l) delete l;
		if (r) delete r;
		if (p) delete p;
	}
} *root;

void setchild(node* p, node* c, int l) {
	c->p = p; l ? p->l = c : p->r = c;
}

void push(node* x) {
	if (!x || !x->rev) return;
	x->rev = 0; swap(x->l, x->r);
	x->l->rev ^= 1;
	x->r->rev ^= 1;
}

void update(node* x) {
	if (!x) return;
	x->size = 1;
	if (x->l) x->size += x->l->size;
	if (x->r) x->size += x->r->size;
}

void lrotate(node* x) {
	node* y = x->r;
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
	update(x); update(y);
}

void rrotate(node* x) {
	node* y = x->l;
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
	update(x); update(y);
}

void splay(node* x) {
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

void replace(node* u, node* v) {
	if (!u->p) root = v;
	else if (u == u->p->l) u->p->l = v;
	else u->p->r = v;
	if (v) v->p = u->p;
}

node* minsubtree(node* u) {
	while (u->l) u = u->l;
	return u;
}

node* maxsubtree(node* u) {
	while (u->r) u = u->r;
	return u;
}

void insert(int key) {
	node* z = root;
	node* p = 0;
	while (z) {
		p = z;
		if (z->key < key) z = z->r;
		else z = z->l;
	}
	z = new node(key);
	z->p = p;
	if (!p) root = z;
	else if (p->key < z->key) p->r = z;
	else p->l = z;
	splay(z);
}

node* find(int key) {
	node* z = root;
	while (z) {
		if (z->key < key) z = z->r;
		else if (key < z->key) z = z->l;
		else return z;
	}
	return 0;
}

void erase(int key) {
	node* z = find(key);
	if (!z) return;
	splay(z);
	if (!z->l) replace(z, z->r);
	else if (!z->r) replace(z, z->l);
	else {
		node* y = minsubtree(z->r);
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

node* join(node* x, node* y) {
	if (!x) return y;
	if (!y) return x;
	push(y);
	while (1) {
		push(x);
		if (!x->r) break;
		x = x->r;
	}
	splay(x);
	setchild(x, y, 0);
	update(x);
	return x;
}

void split(int i, node*& x, node*& y) {
	if (!i) {
		x = 0;
		y = root;
		return;
	}
	node* z = find(i);
	splay(z);
	y = z->r; y->p = 0;
	x = z; x->r = 0;
	update(x);
}

int main() {
	insert(3); insert(4); insert(5);
	cout<<root->key<<"\n";
	node *x, *y;
	split(4, x, y);
	cout<<x->key<<" "<<y->key<<"\n";
	//Result:
	//5
	//4 5
	return 0;
}
