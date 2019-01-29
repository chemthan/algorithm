#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000000 + 10;
int cur = 0;
struct Node {
	int key, prio, size;
	Node *l, *r;
	Node() {
		key = prio = size = 0;
		l = r = 0;
	}
} mem[MAXN], *nil = mem + MAXN - 1;
void pushup(Node* a) {
	a->size = a->l->size + a->r->size + 1;
}
void init() {
	nil->prio = ~0U >> 1;
}
int randprio() {
	static int seed = 0;
	seed = (seed * 1001 + 100621) % 999983;
	return seed;
}
Node* alloc(int key, Node* l = nil, Node* r = nil, int prio = randprio()) {
	Node* res = mem + (cur++);
	res->prio = prio;
	res->key = key;
	res->l = l;
	res->r = r;
	pushup(res);
	return res;
}
int findpos(Node* root, int key) {
	if (root == nil) return 0;
	if (root->key > key) return findpos(root->l, key);
	if (root->key < key) return root->l->size + 1 + findpos(root->r, key);
	if (root->key = key) return root->l->size + 1;
}
void trace(Node* root) {
	if (root == nil) return;
	trace(root->l);
	cout << root->key << " ";
	trace(root->r);
}

struct PersistentTreap {
	Node* root;
	PersistentTreap() {
		root = nil;
	}
	Node* splitL(Node* a, int size) {
		if (a == nil || !size) return nil;
		if (a->l->size >= size) return splitL(a->l, size);
		if (a->l->size + 1 >= size) return alloc(a->key, a->l, nil, a->prio);
		return alloc(a->key, a->l, splitL(a->r, size - a->l->size - 1), a->prio);
	}
	Node* splitR(Node* a, int size) {
		if (a == nil || !size) return nil;
		if (a->r->size >= size) return splitR(a->r, size);
		if (a->r->size + 1 >= size) return alloc(a->key, nil, a->r, a->prio);
		return alloc(a->key, splitR(a->l, size - a->r->size - 1), a->r, a->prio);
	}
	Node* splitLkey(Node* a, int key) {
		if (a == nil) return nil;
		if (a->key >= key) return splitLkey(a->l, key);
		return alloc(a->key, a->l, splitLkey(a->r, key), a->prio);
	}
	Node* splitRkey(Node* a, int key) {
		if (a == nil) return nil;
		if (a->key <= key) return splitRkey(a->r, key);
		return alloc(a->key, splitRkey(a->l, key), a->r, a->prio);
	}
	Node* merge(Node* a, Node* b) {
		if (a == nil) return b;
		if (b == nil) return a;
		if (a->prio > b->prio) return alloc(a->key, a->l, merge(a->r, b), a->prio);
		return root = alloc(b->key, merge(a, b->l), b->r, b->prio);
	}
	Node* insert(int key, int p) {
		int l = root->size;
		return root = merge(merge(splitL(root, p), alloc(key, nil, nil)), splitR(root, l - p));
	}
	Node* insert(int key) {
		return root = merge(merge(splitLkey(root, key), alloc(key, nil, nil)), splitRkey(root, key));
	}
	Node* remove(int x, int y) {
		return root = merge(splitL(root, x - 1), splitR(root, root->size - y));
	}
};

const int maxn = 100000 + 10;
PersistentTreap ptreap;
Node* node[maxn];

int main() {
	srand(time(NULL));
	init();
	int n = 10;
	for (int i = 0; i < n; i++) {
		node[i] = ptreap.insert(rand());
	}
	for (int i = 0; i < n; i++) {
		trace(node[i]);
		cout << "\n";
	}
	return 0;
}
