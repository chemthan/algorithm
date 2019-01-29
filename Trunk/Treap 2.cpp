#include <bits/stdc++.h>
using namespace std;

const int oo = (int) 1e9;
struct node {
	int key, prio, size;
	node *l, *r;
	int rev, lz;
	node() {}
	node(int key, int prio, node* l, node* r) : key(key), prio(prio), l(l), r(r) {
		size = 1;
		if (l) size += l->size;
		if (r) size += r->size;
		rev = lz = 0;
	}
} *root;
int randprio() {
	static int seed = 0;
	seed = (seed * 1001 + 100621) % 999983;
	return seed;
}
int size(node*& t) {
	return t ? t->size : 0;
}
int prio(node*& t) {
	return t ? t->prio : -1;
}
void updatelz(node* t, int val) {
	if (!t) return;
	t->lz += val;
	t->key += val;
}
void pushdown(node* t) {
	if (!t) return;
	node *x = t->l, *y = t->r;
	if (t->rev) {
		if (x) {swap(x->l, x->r); x->rev ^= 1;}
		if (y) {swap(y->l, y->r); y->rev ^= 1;}
		t->rev = 0;
	}
	if (t->lz) {
		if (x) updatelz(x, t->lz);
		if (y) updatelz(y, t->lz);
		t->lz = 0;
	}
}
void pushup(node*& t) {
	if (!t) return;
	t->size = size(t->l) + size(t->r) + 1;
}
void lrotate(node*& t) {
	node* l = t->l;
	t->l = l->r; l->r = t;
	t = l; pushup(t->r); pushup(t);
}
void rrotate(node*& t) {
	node* r = t->r;
	t->r = r->l; r->l = t;
	t = r; pushup(t->l); pushup(t);
}
void balance(node*& t) {
	if (prio(t->l) > t->prio) lrotate(t);
	else if (prio(t->r) > t->prio) rrotate(t);
}
void insert(node*& t, int key, int prio, int pos) {
	if (!t) {
		t = new node(key, prio, 0, 0);
		return;
	}
	pushdown(t);
	t->size++;
	if (pos > size(t)) insert(t->r, key, prio, pos);
	else if (pos <= size(t->l) + 1) insert(t->l, key, prio, pos);
	else insert(t->r, key, prio, pos - size(t->l) - 1);
	balance(t);
	pushup(t);
}
node* find(node*& t, int pos) {
	pushdown(t);
	if (pos == size(t->l) + 1) return t;
	if (pos <= size(t->l)) return find(t->l, pos);
	return find(t->r, pos - size(t->l) - 1);
}
node* join(node* l, node* r) {
	pushdown(l); pushdown(r);
	if (!l) return r;
	if (!r) return l;
	node* res;
	if (l->prio < r->prio) {
		node* t = join(l, r->l);
		res = new node(r->key, r->prio, t, r->r);
		delete r;
	}
	else {
		node* t = join(l->r, r);
		res = new node(l->key, l->prio, l->l, t);
		delete l;
	}
	pushup(res);
	return res;
}
void erase(node*& t, int pos) {
	pushdown(t);
	if (pos == size(t->l) + 1) {
		if (!t->l && !t->r) {
			delete t;
			t = 0;
		}
		else t = join(t->l, t->r);
		return;
	}
	t->size--;
	if (pos <= size(t->l)) erase(t->l, pos);
	else erase(t->r, pos - size(t->l) - 1);
}
void split(node* t, int pos, node*& l, node*& r) {
	insert(t, -1, oo, pos);
	l = t->l; r = t->r;
	delete t;
}
void split(node* t, int pos1, int pos2, node*& t1, node*& t2, node*& t3) {
	split(t, pos1, t1, t2);
	split(t2, pos2 - pos1 + 2, t2, t3);
}
void reverse(int l, int r) {
	node *x, *y, *z;
	split(root, l, r, x, y, z);
	if (y) {
		y->rev ^= 1;
		swap(y->l, y->r);
	}
	root = join(join(x, y), z);
}
void update(int l, int r, int val) {
	node *x, *y, *z;
	split(root, l, r, x, y, z);
	updatelz(y, val);
	root = join(join(x, y), z);
}
void trace(node* t) {
	if (!t) return;
	pushdown(t);
	trace(t->l);
	cout << t->key << " ";
	trace(t->r);
}
void trace() {
	trace(root);
	cout << "\n";
}

int main() {
	for (int i = 1; i < 10; i++) {
		insert(root, i, randprio(), i);
	}
	cout << size(root->l) << " " << size(root->r) << "\n";
	trace();
	reverse(1, 4);
	trace();
	return 0;
}
