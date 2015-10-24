#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;
int inv[maxn];
void build(int p) {
	inv[1] = 1;
	for (int i = 2; i < p; i++)
		inv[i] = (p - (p / i) * inv[p % i] % p) % p;
}

int main() {
	build(2311);
	for (int i = 1; i < 2311; i++) {
		cout<<i * inv[i] % 2311<<" ";
	}
	return 0;
}

