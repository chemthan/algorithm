#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: NMlog(M)
* f[i][j] = min(f[i - 1][k]) + c[k][j], k < j
* a[i][j] = min(k | k < j && f[i][j] = f[i - 1][k] + c[k][j]);
* Sufficient condition: a[i][j] <= a[i][j + 1]
*/

const int oo = (int) 1e9;
const int MAXN = 1010;
const int MAXM = 1010;
int f[MAXN][MAXM];

int getcost(int l, int r) {
    return 0;
}

void divide(int i, int L, int R, int optL, int optR) {
    if (L > R) return;
    int M = L + R >> 1, savek = optL;
    f[i][M] = oo;
    for (int k = optL; k <= min(M - 1, optR); k++) {
        int cur = f[i - 1][k] + getcost(k + 1, M);
        if (f[i][M] > cur) {
            f[i][M] = cur;
            savek = k;
        }
    }
    divide(i, L, M - 1, optL, savek);
    divide(i, M + 1, R, savek, optR);
}

int main() {
	return 0;
}
