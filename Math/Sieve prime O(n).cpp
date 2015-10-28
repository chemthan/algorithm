#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;
int t[maxn];
int nprime;
int prime[maxn / 10];
void build() {
	memset(t, 0, sizeof(t));
	nprime = 0;
	for (int i = 2; i < maxn; i++) {
		if (!t[i]) {
			prime[++nprime] = i;
			t[i] = nprime;
		}
		for(int j = 1; j <= t[i] && 1LL * i * prime[j] < maxn; j++) t[i * prime[j]] = j;
	}
}

int main() {
	build();
	for (int i = 1; i <= 100; i++) printf("%d\n", prime[i]);
	return 0;
}
