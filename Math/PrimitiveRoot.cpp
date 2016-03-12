#include <bits/stdc++.h>
using namespace std;

vector<int> dvs;
int fmod(int n, int k, int p) {
	if (!k) return 1;
	if (k & 1) return 1LL * n * fmod(n, k - 1, p) % p;
	int t = fmod(n, k >> 1, p);
	return 1LL * t * t % p;
}
int primitiveroot(int p) {
	dvs.clear();
	for (int i = 2; i * i < p; i++) {
		if ((p - 1) % i) continue;
		dvs.push_back(i);
		if (i * i != p - 1) dvs.push_back((p - 1) / i);
	}
	for (int i = 2; i < p; i++) {
		int flag = 1;
		for (int j = 0; j < dvs.size(); j++) {
			if (fmod(i, dvs[j], p) == 1) {
				flag = 0;
				break;
			}
		}
		if (flag) return i;
	}
}

int main() {
	printf("%d", primitiveroot(1000000007));
	return 0;
}
