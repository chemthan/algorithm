#include <bits/stdc++.h>
using namespace std;

//O(n)
//Problem:
//http://codeforces.com/problemset/problem/128/B
struct state {
	int len, link;
	map<char, int> nxt;
};
const int MAXN = 100010;
const int MAXC = 26;
state st[MAXN << 1];
int nsz, last;
void init() {
	last = st[0].len = 0;
	st[0].link = -1;
	nsz = 1;
}
void extend(char c) {
	int cur = nsz++;
	st[cur].len = st[last].len + 1;
	int p;
	for (p = last; ~p && !st[p].nxt.count(c); p = st[p].link) st[p].nxt[c] = cur;
	if (!~p) st[cur].link = 0;
	else {
		int q = st[p].nxt[c];
		if (st[p].len + 1 == st[q].len) st[cur].link = q;
		else {
			int clone = nsz++;
			st[clone].len = st[p].len + 1;
			st[clone].nxt = st[q].nxt;
			st[clone].link = st[q].link;
			for (; ~p && st[p].nxt[c] == q; p = st[p].link) st[p].nxt[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}

char cur[MAXN];
void trace(int u, int len = 0) {
	for (int i = 0; i < MAXC; i++) {
		if (st[u].nxt['a' + i]) {
			cur[len] = 'a' + i;
			cout<<cur<<"\n";
			trace(st[u].nxt['a' + i], len + 1);
			cur[len] = 0;
		}
	}
}

int nchild[MAXN << 1];
int dfs(int u) {
	if (nchild[u]) return nchild[u];
	nchild[u] = 1;
	for (int i = 0; i < MAXC; i++) {
		if (st[u].nxt['a' + i]) {
			nchild[u] += dfs(st[u].nxt['a' + i]);
		}
	}
	return nchild[u];
}

string kth(int u, int k) {
	if (!k--) return "";
	int tot = 0;
	for (int i = 0; i < MAXC; i++) {
		if (st[u].nxt['a' + i]) {
			int v = st[u].nxt['a' + i];
			if (tot + nchild[v] >= k) {
				return char('a' + i) + kth(v, k - tot);
			}
			tot += nchild[v];
		}
	}
	return "";
}

int main() {
	string s = "abcbc";
	init();
	for (int i = 0; i < s.size(); i++) {
		extend(s[i]);
	}
	trace(0);
	cout<<dfs(0)<<"\n"; //Total distinct substring, include empty string
	cout<<kth(0, 10)<<"\n";
	state nxt = st[st[0].nxt['b']];
	cout<<nxt.len<<"\n";
	return 0;
}
