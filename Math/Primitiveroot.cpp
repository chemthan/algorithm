#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int> > prime;
vector<int> dvs;
int exp(int n, int k, int p) {
	if (!k) return 1;
	if (k & 1) return 1LL * n * exp(n, k - 1, p) % p;
	int t = exp(n, k >> 1, p);
	return 1LL * t * t % p;
}
void go(int pos, int cur) {
	if (pos == prime.size()) return;
	for (int i = 0; i <= prime[pos].second; i++) {
		if (i) dvs.push_back(cur);
		go(pos + 1, cur);
		cur *= prime[pos].first;
	}
}
int primitiveroot(int p) {
	int t = p - 1;
	for (int i = 2; 1LL * i * i <= t; i++) {
		int cnt = 0;
		while (t % i == 0) {
			t /= i;
			cnt++;
		}
		if (cnt) prime.push_back(make_pair(i, cnt));
	}
	if (t > 1) prime.push_back(make_pair(t, 1));
	go(0, 1);
	sort(dvs.begin(), dvs.end());
	dvs.pop_back();
	for (int i = 2; i < p; i++) {
		int flag = 1;
		for (int j = 0; j < dvs.size(); j++) {
			if (exp(i, dvs[j], p) == 1) {
				flag = 0;
				break;
			}
		}
		if (flag) return i;
	}
}

int main() {
	printf("%d", primitiveroot(7));
	return 0;
}
