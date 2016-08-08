#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000000 + 10;
int ptr;
struct Node {
	Node *l, *r;
	int key, size;
} mem[MAXN], *nil = mem + (ptr++);
void init() {
	nil->l = nil->r = nil;
	nil->size = 0;
}
int rd() {
	static int seed = 0;
	seed = (seed * 1001 + 100621) % 999983;
	return seed;
}
void pushdown(Node* x) {
	if (x == nil) return;
}
void pushup(Node* x) {
	if (x == nil) return;
	x->size = x->l->size + 1 + x->r->size;
}
Node* newNode(int key, Node* l = nil, Node* r = nil) {
	Node* x = mem + (ptr++);
	x->l = l, x->r = r, x->key = key;
	pushup(x);
	return x;
}
Node* join(Node* l, Node* r) {
	if (l == nil) return r;
	if (r == nil) return l;
	if (rd() % (l->size + r->size) < l->size) {
		pushdown(l);
		return newNode(l->key, l->l, join(l->r, r));
	}
	pushdown(r);
	return newNode(r->key, join(l, r->l), r->r);
}
Node* splitL(Node* x, int pos) {
	if (x == nil || !pos) return nil;
	pushdown(x);
	if (x->l->size >= pos) return splitL(x->l, pos);
	return newNode(x->key, x->l, splitL(x->r, pos - x->l->size - 1));
}
Node* splitR(Node* x, int pos) {
	if (x == nil || !pos) return nil;
	pushdown(x);
	if (x->r->size >= pos) return splitR(x->r, pos);
	return newNode(x->key, splitR(x->l, pos - 1 - x->r->size), x->r);
}
Node* split(Node* x, int pos1, int pos2) {
	x = splitL(x, pos2);
	return splitR(x, pos2 - pos1 + 1);
}
int depth(Node* x) {
	if (x == nil) return 0;
	pushdown(x);
	return 1 + max(depth(x->l), depth(x->r));
}
void trace(Node* x) {
	if (x == nil) return;
	pushdown(x);
	trace(x->l);
	cout << x->key << " ";
	trace(x->r);
}

const int maxn = 100000 + 10;
Node* node[maxn];

int main() {
	init();
	node[0] = nil;
	node[1] = join(node[0], newNode(5));
	node[2] = join(newNode(1), node[1]);
	node[3] = join(newNode(2), node[1]);
	trace(node[1]); cout << "\n";
	trace(node[2]); cout << "\n";
	trace(node[3]); cout << "\n";
	node[4] = join(node[2], newNode(10));
	trace(node[4]); cout << "\n";
	return 0;
}
