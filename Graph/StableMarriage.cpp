#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 5;
int n, rate[MAXN][MAXN], husband[MAXN];
queue<int> womanlist[MAXN];
queue<int> freemans;
int prefer(int woman, int newman, int herhusband) {
	return rate[woman][newman] < rate[woman][herhusband];
}
void doit() {
	memset(husband, -1, sizeof(husband));
	for (int man = 0; man < n; man++) {
		freemans.push(man);
	}
	while (freemans.size()) {
		int man = freemans.front();
		int woman = womanlist[man].front();
		womanlist[man].pop();
		if (!~husband[woman]) {
			husband[woman] = man;
			freemans.pop();
		}
		else {
			int herhusband = husband[woman];
			if (prefer(woman, man, herhusband)) {
				husband[woman] = man;
				freemans.pop();
				freemans.push(herhusband);
			}
		}
	}
	for (int woman = 0; woman < n; woman++) {
		printf("(%d %d) ", husband[woman], woman);
	}
}

int main() {
	scanf("%d", &n);
	for (int man = 0; man < n; man++) {
		for (int i = 0; i < n; i++) {
			int woman; scanf("%d", &woman); woman--;
			womanlist[man].push(woman);
		}
	}
	for (int woman = 0; woman < n; woman++) {
		for (int i = 0; i < n; i++) {
			int man; scanf("%d", &man); man--;
			rate[woman][man] = i;
		}
	}
	doit();
	return 0;
}
