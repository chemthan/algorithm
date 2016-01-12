#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXC = 256;

struct Node {
	Node *children[MAXC];
	Node *sufflink;
	int start, *end;
	int suffidx;
};

char S[MAXN];
Node* root = NULL;
Node* lnode = NULL;
Node* anode = NULL;
int aedge = -1;
int alen = 0;
int cnt = 0;
int eleaf = -1;
int* eroot = NULL;
int* esplit = NULL;
int size = -1;

Node* newnode(int start, int* end) {
	Node* node = (Node*) malloc(sizeof(Node));
	for (int i = 0; i < MAXC; i++) node->children[i] = NULL;
	node->sufflink = root; node->start = start;
	node->end = end; node->suffidx = -1;
	return node;
}
int edgelen(Node* n) {
	return *(n->end) - (n->start) + 1;
}
int walkdown(Node *currNode) {
	if (alen >= edgelen(currNode)) {
		aedge += edgelen(currNode);
		alen -= edgelen(currNode);
		anode = currNode;
		return 1;
	}
	return 0;
}
void extend(int pos) {
	eleaf = pos; cnt++; lnode = NULL;
	while (cnt > 0) {
		if (alen == 0) aedge = pos;
		if (anode->children[S[aedge]] == NULL) {
			anode->children[S[aedge]] = newnode(pos, &eleaf);
			if (lnode != NULL) {
				lnode->sufflink = anode;
				lnode = NULL;
			}
		} else {
			Node* next = anode->children[S[aedge]];
			if (walkdown(next)) continue;
			if (S[next->start + alen] == S[pos]) {
				if(lnode != NULL && anode != root) {
					lnode->sufflink = anode;
					lnode = NULL;
				}
				alen++;
				break;
			}
			esplit = (int*) malloc(sizeof(int));
			*esplit = next->start + alen - 1;
			Node* split = newnode(next->start, esplit);
			anode->children[S[aedge]] = split;
			split->children[S[pos]] = newnode(pos, &eleaf);
			next->start += alen;
			split->children[S[next->start]] = next;
			if (lnode != NULL) lnode->sufflink = split;
			lnode = split;
		}
		cnt--;
		if (anode == root && alen > 0) {alen--; aedge = pos - cnt + 1;}
		else if (anode != root) anode = anode->sufflink;
	}
}
void print(int i, int j) {
	for (int k = i; k <= j; k++) printf("%c", S[k]);
}
void dfs(Node* n, int hlabel) {
	if (n == NULL) return;
	if (~n->start) print(n->start, *(n->end));
	int leaf = 1;
	for (int i = 0; i < MAXC; i++) {
		if (n->children[i] != NULL) {
			if (leaf == 1 && ~n->start) printf(" [%d]\n", n->suffidx);
			leaf = 0;
			dfs(n->children[i], hlabel + edgelen(n->children[i]));
		}
	}
	if (leaf == 1) {
		n->suffidx = size - hlabel;
		printf(" [%d]\n", n->suffidx);
	}
}
void clear(Node* n) {
	if (n == NULL) return;
	for (int i = 0; i < MAXC; i++) if (n->children[i] != NULL) clear(n->children[i]);
	if (!~n->suffidx) free(n->end);
	free(n);
}
void build() {
	size = strlen(S);
	eroot = (int*) malloc(sizeof(int));
	*eroot = - 1;
	root = newnode(-1, eroot);
	anode = root;
	for (int i = 0; i < size; i++) extend(i);
	int hlabel = 0; dfs(root, hlabel);
	clear(root);
}

int main() {
	strcpy(S, "abcabxabcd$");
	build();
	return 0;
}
