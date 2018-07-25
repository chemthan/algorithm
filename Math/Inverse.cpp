#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int inv[MAXN];
void build(int p) {
    inv[1] = 1;
    for (int i = 2; i < MAXN; i++) inv[i] = (p - 1LL * (p / i) * inv[p % i] % p) % p;
}

int main() {
    build(2311);
    for (int i = 1; i < 2311; i++) {
        cout << i * inv[i] % 2311 << " ";
    }
    return 0;
}
