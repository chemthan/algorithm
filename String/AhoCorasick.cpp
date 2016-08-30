#include <bits/stdc++.h>
using namespace std;

/*Problem
1. http://codeforces.com/problemset/problem/434/C
2. https://www.codechef.com/problems/MSDBIN
*/
const int MAXN = 100000 + 10;
const int MAXC = 26;
struct Node {
	Node* parent;
	Node* child[MAXC];
	Node* bfail;
	Node* gfail;
	int key;
	char val;
	Node() {
		bfail = 0;
		key = -1;
	}
} node[MAXN];
Node* alloc = node;
Node* q[MAXN];
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
		for (int i = 0; i < MAXC; i++) {
			if (x->child[i]) q[e++] = x->child[i];
		}
		if (x == root || x->parent == root) {
			x->bfail = root;
			x->gfail = 0;
		}
		else {
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
		while (cur != root && !cur->child[*s - 'a']) cur = cur->bfail;
		cur = cur->child[*s - 'a'];
		if (!cur) {
			cur = root;
			continue;
		}
		Node* tmp = cur;
		if (tmp->key == -1) tmp = tmp->gfail;
		while (tmp) {
			cout << tmp->key << " ";
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
	search("aabab"); cout << "\n";
	return 0;
}
