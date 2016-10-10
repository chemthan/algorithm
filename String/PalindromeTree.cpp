#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
* Problems:
* 1. http://codeforces.com/gym/100548/status/G
*/

struct PalindromicTree {
	static const int MAXN = 100000 + 10;
	static const int MAXC = 26;
	int next[MAXN][MAXC], link[MAXN], qlink[MAXN], dlinl[MAXN][MAXC], cnt[MAXN];
	int num[MAXN], len[MAXN], s[MAXN];
	int last, n, p;
	int newnode(int l) {
		for (int i = 0; i < MAXC; i++) next[p][i] = 0;
		qlink[p] = 0;
		for (int i = 0; i < MAXC; i++) dlink[p][i] = 0;
		cnt[p] = num[p] = 0;
		len[p] = l;
		return p++;
	}
	void init() {
		p = 0;
		newnode(0); newnode(-1);
		n = last = 0;
		s[n] = -1; link[0] = 1;
	}
	int getlink(int x) {
		while (s[n - len[x] - 1] != s[n]) {
			if (s[n - len[link[x]] - 1] == s[n]) x = link[x];
			else x = qlink[x]; //dlink[x][s[n]]
		return x;
	}
	void add(char c) {
		c -= 'a';
		s[++n] = c;
		int cur = getlink(last);
		if(next[cur][c] == 0) {
			int now = newnode(len[cur] + 2);
			link[now] = next[getlink(link[cur])][c];
			next[cur][c] = now;
			num[now] = num[link[now]] + 1;
			if (s[n - len[link[now]]] == s[n - len[link[link[now]]]]) {
				qlink[now] = qlink[link[now]];
			}
			else {
				qlink[now] = link[link[now]];
			}
			for (int i = 0; i < MAXC; i++) {
				dlink[now][i] = dlink[link[now]][i];
			}
			dlink[now][s[n - len[link[now]]]] = link[now];
		}
		last = next[cur][c];
		cnt[last]++;
	}
	void count() {
		for (int i = p - 1; i >= 0; i--) cnt[link[i]] += cnt[i];
	}
} pdt;

int main() {
	return 0;
}
