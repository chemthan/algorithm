#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;
const int maxc = 26;

struct Node {
	Node* parent;
	Node* child[maxc];
	Node* bfail;
	Node* gfail;
	int key;
	char val;
	Node () {
		bfail = 0;
		key = -1;
	}
} node[maxn];

Node* alloc = node;
Node* q[maxn];
Node* root = alloc++;

Node* insert(Node* x, char* s, int key) {
	while (*s) {
		int c = *s - 'a';
		if (!x->child[c]) {
			x->child[c] = alloc++;
			x->child[c]->val = c;
			x->child[c]->parent = x;
		}
		x = x->child[c];
		s++;
	}
	x->key = key;
	return x;
}

void pushlink(Node* root) {
	int b = 0, e = 0;
	q[e++] = root;
	while (b < e) {
		Node* x = q[b++];
		for (int i = 0; i < maxc; i++) {
			if (x->child[i]) q[e++] = x->child[i];
		}
		if (x == root || x->parent == root) {
			x->bfail = root;
			x->gfail = 0;
		} else {
			x->bfail = x->parent->bfail;
			while (x->bfail != root && !x->bfail->child[x->val]) x->bfail = x->bfail->bfail;
			if (x->bfail->child[x->val]) x->bfail = x->bfail->child[x->val];
			if (x->bfail->key != -1) x->gfail = x->bfail;
			else x->gfail = x->bfail->gfail;
		}
	}
}

void search(char* s) {
	Node* cur = root;
	while (*s) {
		while (!cur->child[*s - 'a']) cur = cur->bfail;
		cur = cur->child[*s - 'a'];
		Node* tmp = cur;
		if (tmp->key == -1) tmp = tmp->gfail;
		while (tmp) {
			printf("%d ", tmp->key);
			tmp = tmp->gfail;
		}
		s++;
	}
}

int main() {
	insert(root, "abab", 0);
	insert(root, "aba", 1);
	insert(root, "aabab", 2);
	insert(root, "ababb", 3);
	insert(root, "bab", 4);
	pushlink(root);
	search("aabab");
	return 0;
}
