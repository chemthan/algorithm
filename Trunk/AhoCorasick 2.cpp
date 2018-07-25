#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;
const int MAXC = 26;
int key[MAXN], next[MAXN], ptrlist, nil;
struct List {
	int head, tail;
	void init() {
		head = tail = nil;
	}
	void add(int k) {
		++ptrlist;
		key[ptrlist] = k;
		next[ptrlist] = nil;
		if (head == nil) {
			head = tail = ptrlist;
			return;
		}
		next[tail] = ptrlist;
		tail = ptrlist;
	}
	void join(List& other) {
		if (other.head == nil) return;
		if (head == nil) {
			head = other.head;
			tail = other.tail;
			return;
		}
		next[tail] = other.head;
		tail = other.tail;
	}
};
int go[MAXN][MAXC], fail[MAXN], ptrtrie, que[MAXN], qsize;
List out[MAXN];
void init() {
	nil = ptrlist = -1;
	ptrtrie = 0;
	memset(go[0], 0, sizeof(go[0]));
	out[0].init();
}
void add(char s[], int len, int key) {
	int v = 0;
	for (int i = 0; i < len; i++) {
		int c = s[i] - 'a';
		if (go[v][c] < 1) {
			++ptrtrie;
			memset(go[ptrtrie], -1, sizeof(go[ptrtrie]));
			out[ptrtrie].init();
			go[v][c] = ptrtrie;
		}
		v = go[v][c];
	}
	out[v].add(key);
}
void build() {
	qsize = 0;
	for (int c = 0; c < MAXC; c++) if (go[0][c]) {
			fail[go[0][c]] = 0;
			que[qsize++] = go[0][c];
		}
	for (int i = 0; i < qsize; i++) {
		int r = que[i];
		for (int c = 0; c < MAXC; c++) {
			int u = go[r][c];
			if (u < 0) go[r][c] = go[fail[r]][c];
			else {
				que[qsize++] = u;
				fail[u] = go[fail[r]][c];
				out[u].join(out[fail[u]]);
			}
		}
	}
}
void search(char s[], int len) {
	int v = 0;
	for (int i = 0; i < len; i++) {
		int c = s[i] - 'a';
		while (go[v][c] < 0) v = fail[v];
		v = go[v][c];
		int x = out[v].head;
		while (x != nil) {
			cout << key[x] << " ";
			x = next[x];
		}
	}
}

int main() {
	init();
	add("abab", 4, 0);
	add("aba", 3, 1);
	add("aabab", 5, 2);
	add("ababb", 5, 3);
	add("bab", 3, 4);
	build();
	search("aabab", 5); cout << "\n";
	return 0;
}
