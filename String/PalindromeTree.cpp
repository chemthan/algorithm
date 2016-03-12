#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXC = 26;
struct PalindromeTree {
	int next[MAXN][MAXC], fail[MAXN], cnt[MAXN];
	int num[MAXN], len[MAXN], s[MAXN];
	int last, n, p;
	int newnode(int l) {
		for(int i = 0; i < MAXC; i++) next[p][i] = 0;
		cnt[p] = num[p] = 0;
		len[p] = l;
		return p++;
	}
	void init() {
		p = 0;
		newnode(0); newnode(-1);
		n = last = 0;
		s[n] = -1; fail[0] = 1;
	}
	int getfail(int x) {
		while (s[n - len[x] - 1] != s[n]) x = fail[x];
		return x;
	}
	void add(char c) {
		c -= 'a';
		s[++n] = c;
		int cur = getfail(last);
		if(next[cur][c] == 0) {
			int now = newnode(len[cur] + 2);
			fail[now] = next[getfail(fail[cur])][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
	}
	void count() {
		for (int i = p - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
	}
};

int main() {
	return 0;
}
