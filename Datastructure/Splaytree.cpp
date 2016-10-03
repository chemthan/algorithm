#include <bits/stdc++.h>
using namespace std;

/*
Complexity: amortized O(logn)
Problems:
1. http://codeforces.com/gym/100796/problem/J
2. https://www.codechef.com/problems/SUMBITS
3. https://www.codechef.com/problems/BRCKMT
4. https://www.codechef.com/problems/FURGRAPH
*/

struct Node {
	Node();
	Node *l, *r, *p;
	int size, key;
	int rev, lz;
};
Node* nil = new Node();
Node::Node() {
	l = r = p = nil;
	size = 1; key = rev = lz = 0;
}
void init() {
	nil->l = nil->r = nil->p = nil;
	nil->size = 0;
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

const int MAXN = 10000000 + 10;
struct SplayTree {
	Node mem[MAXN], *root;
	int cur;
	SplayTree() {
		root = nil; cur = 0;
		init();
	}
	Node* alloc(int key) {
		mem[cur].key = key;
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
			else {
				splay(x);
				return root = x;
			}
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
			if (pos == k) {
				splay(x);
				return root = x;
			}
			else if (pos < k) x = x->l;
			else {x = x->r; pos -= k;}
		}
		return nil;
	}
	Node* findpos(int pos) {
		return findpos(root, pos);
	}
	Node* join(Node* x, Node* y) {
		x->p = y->p = nil;
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
	void trace(Node* x) {
		if (x == nil) return;
		pushdown(x);
		trace(x->l);
		cout << x->key << " ";
		trace(x->r);
	}
	void trace() {
		trace(root);
		cout << "\n";
	}
} slt;

int main() {
	slt.insert(3); slt.insert(4); slt.insert(5);
	slt.reverse(1, 2);
	slt.trace();
	slt.update(1, 3, 1);
	slt.trace();
	slt.update(2, 3, 2);
	slt.trace();
	return 0;
}
