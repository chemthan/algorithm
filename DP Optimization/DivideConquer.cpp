#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: NMlog(M)
* f[i][j] = min(f[i - 1][k]) + c[k][j], k < j
* a[i][j] = min(k | k < j && f[i][j] = f[i - 1][k] + c[k][j]);
* Sufficient condition: a[i][j] <= a[i][j + 1]
* Problem:
* 1. http://codeforces.com/contest/674/problem/C
* 2. https://online.acmicpc.org/problems/branch
*/

const int oo = (int) 1e9;
const int MAXN = 1e3 + 5;
const int MAXM = 1e3 + 5;
int n;
int f[MAXN][MAXM];
int c[MAXN][MAXM];

void divide(int i, int L, int R, int optL, int optR) {
    if (L > R) return;
    int M = L + R >> 1, ptr = optL;
    f[i][M] = oo;
    for (int k = optL; k <= min(M - 1, optR); k++) {
        int cur = f[i - 1][k] + c[k][M];
        if (f[i][M] > cur) {
            f[i][M] = cur;
            ptr = k;
        }
    }
    divide(i, L, M - 1, optL, ptr);
    divide(i, M + 1, R, ptr, optR);
}

int main() {
    return 0;
}
