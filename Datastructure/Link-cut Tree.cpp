#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
struct Node {
	Node();
	Node *ch[2], *p;
	int size, root, key;
	int dir() {return this == p->ch[1];}
	void setchild(Node* c, int d) {ch[d] = c; c->p = this;}
	void pushup() {size = ch[0]->size + ch[1]->size + 1;}
} node[MAXN], *nil = node + MAXN - 1;
Node::Node() {
	size = 1, root = 1;
	ch[0] = ch[1] = p = nil;
}
void rotate(Node* t) {
	Node* p = t->p;
	int d = t->dir();
	if (!p->root) {
		p->p->setchild(t, p->dir());
	}
	else {
		p->root = 0;
		t->root = 1;
		t->p = p->p;
	}
	p->setchild(t->ch[!d], d);
	t->setchild(p, !d);
	p->pushup(); t->pushup();
}
void splay(Node* t) {
//	t->pushup();
	while (!t->root) {
//		if (!t->p->root) t->p->p->pushup(); t->p->pushup(), t->pushup();
		if (!t->p->root) rotate(t->dir() == t->p->dir() ? t->p : t);
		rotate(t);
	}
}
Node* access(Node* x) {
	Node* y = nil;
	while (x != nil) {
		splay(x);
		x->ch[1]->root = 1;
		x->ch[1] = y;
		y->root = 0;
		x->pushup();
		y = x;
		x = x->p;
	}
	return y;
}
void cut(Node* x) {
	access(x);
	splay(x);
	x->ch[0]->root = 1;
	x->ch[0]->p = nil;
	x->ch[0] = nil;
}
void link(Node* x, Node* y) {
	access(y);
	splay(y);
	y->p = x;
	access(y);
}
Node* findroot(Node* x) {
	x = access(x);
	while (x->ch[0] != nil) x = x->ch[0];
	splay(x);
	return x;
}
Node* lca(Node* x, Node* y) {
	if (findroot(x) != findroot(y)) return nil;
	access(x);
	return access(y);
}
void init() {
	nil->size = 0;
}

int main() {
	init();
	int n = 10;
	for (int i = 1; i <= n; i++) {
		node[i].key = i;
	}
	link(node + 1, node + 2);
	link(node + 1, node + 5);
	link(node + 2, node + 3);
	link(node + 2, node + 4);
	link(node + 5, node + 6);
	cout<<lca(node + 3, node + 4)->key<<"\n";
	cout<<findroot(node + 3)->key<<"\n";
	cut(node + 3);
	cout<<findroot(node + 3)->key<<"\n";
	return 0;
}
