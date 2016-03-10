#include <bits/stdc++.h>
using namespace std;

struct node {
	node *l, *r, *p;
	int key, size;
	int rev, lz;
	node(int key = 0) : key(key) {
		l = r = p = 0;
		size = 1;
		rev = lz = 0;
	}
	~node() {
		if (l) delete l;
		if (r) delete r;
		if (p) delete p;
	}
} *root;
int size(node* x) {
	return x ? x->size : 0;
}
void setchild(node* p, node* c, int l) {
	c->p = p; l ? p->l = c : p->r = c;
}
void updatelz(node* x, int val) {
    x->lz += val;
    x->key += val;
}
void pushdown(node* x) {
	if (!x) return;
	node *u = x->l, *v = x->r;
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
void pushup(node*& x) {
	if (!x) return;
	x->size = size(x->l) + size(x->r) + 1;
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
	pushup(x); pushup(y);
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
	pushup(x); pushup(y);
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
		pushdown(z);
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
		pushdown(z);
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
	pushdown(z);
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
	pushup(x);
}
node* find(node* x, int pos) {
	while (1) {
		pushdown(x);
		int k = x->l ? x->l->size + 1 : 1;
		if (pos == k) return x;
		if (pos < k) x = x->l;
		else {x = x->r; pos -= k;}
	}
	return 0;
}
void split(node* x, int pos, node*& l, node*& r) {
	if (pos == 0) {
		l = 0;
		r = x;
		return;
	}
	node* y = find(x, pos);
	splay(y);
	if (r = y->r) r->p = 0;
	if (l = y) {l->r = 0; pushup(l);}
}
void split(node* t, int pos1, int pos2, node*& t1, node*& t2, node*& t3) {
	split(t, pos1 - 1, t1, t2);
	split(t2, pos2 - pos1 + 1, t2, t3);
}
void reverse(int l, int r) {
	node *x, *y, *z, *t;
	split(root, r, t, z);
	split(t, l - 1, x, y);
	if (y) {
		swap(y->l, y->r);
		y->rev ^= 1;
	}
	root = join(join(x, y), z);
}
void update(int l, int r, int val) {
	node *x, *y, *z;
	split(root, l, r, x, y, z);
	updatelz(y, val);
	root = join(join(x, y), z);
}
void trace(node* x) {
	if (!x) return;
	pushdown(x);
	trace(x->l);
	cout<<x->key<<" ";
	trace(x->r);
}
void trace() {
	trace(root);
	cout<<"\n";
}

int main() {
	insert(3); insert(4); insert(5);
	reverse(1, 2);
	trace();
	update(1, 3, 1);
	trace();
	return 0;
}
