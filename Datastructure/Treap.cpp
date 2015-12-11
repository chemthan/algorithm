#include <bits/stdc++.h>
using namespace std;

const int INF = (int) 1e9;

struct node {
	int key, prio, size;
	node *l, *r;
	node() {}
	node(int _key, int _prio, node* _l, node* _r) {
		key = _key; prio = _prio;
		size = 1; l = _l; r = _r;
		if (l) size += l->size;
		if (r) size += r->size;
	}
};

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

void update(node*& t) {
	t->size = size(t->l) + size(t->r) + 1;
}

void lrotate(node*& t) {
	node* l = t->l;
	t->l = l->r; l->r = t;
	t = l; update(t->r); update(t);
}

void rrotate(node* &t) {
	node* r = t->r;
	t->r = r->l; r->l = t;
	t = r; update(t->l); update(t);
}

void balance(node* &t) {
	if (prio(t->l) > t->prio) lrotate(t);
	else if (prio(t->r) > t->prio) rrotate(t);
}

void insert(node*& t, int key, int prio, int pos) {
	if (!t) {
		t = new node(key, prio, 0, 0);
		return;
	}
	t->size++;
	if (pos > size(t)) insert(t->r, key, prio, pos);
	else if (pos <= size(t->l) + 1) insert(t->l, key, prio, pos);
	else insert(t->r, key, prio, pos - size(t->l) - 1);
	balance(t);
}

node* find(node*& t, int pos) {
	if (pos == size(t->l) + 1) return t;
	if (pos <= size(t->l)) return find(t->l, pos);
	return find(t->r, pos - size(t->l) - 1);
}

node* join(node* l, node* r) {
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
	return res;
}

void erase(node*& t, int pos) {
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

void split(node* t, node* &l, node*& r, int pos) {
	insert(t, -1, INF, pos);
	l = t->l; r = t->r;
	delete t;
}

void split(node* t, node*& t1, node*& t2, node*& t3, int pos1, int pos2) {
	split(t, t1, t2, pos1);
	split(t2, t2, t3, pos2 - pos1 + 2);
}

node* root;

int main() {
	for (int i = 1; i < 100000; i++) {
		insert(root, i, randprio(), i);
	}
	cout<<size(root->l)<<" "<<size(root->r);
	return 0;
}
