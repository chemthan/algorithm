#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int t[MAXN];
int npr;
int pr[MAXN / 10];
void build() {
    memset(t, 0, sizeof(t));
    npr = 0;
    for (int i = 2; i < MAXN; i++) {
        if (!t[i]) {
            pr[++npr] = i;
            t[i] = npr;
        }
        for(int j = 1; j <= t[i] && (long long) i * pr[j] < MAXN; j++) t[i * pr[j]] = j;
    }
}

int main() {
    build();
    for (int i = 1; i <= 100; i++) {
        cout << pr[i] << " \n"[i == 100];
    }
    return 0;
}
