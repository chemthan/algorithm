#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N^2)
* f[i][j] = min(f[i][k] + f[k][j] + c[i][j], i < k < j)
* a[i][j] = min(k | i < k < j && f[i][j] = f[i][k] + f[k][j] + c[i][j])
* Sufficient condition: a[i][j - 1] <= a[i][j] <= a[i + 1][j] or
* c[x][z] + c[y][t] <= c[x][t] + c[y][z] (quadrangle inequality) and c[y][z] <= c[x][t] (monotonicity), x <= y <= z <= t
*/

const int oo = (int) 1e9;
const int MAXN = 1e3 + 5;
int n;
int f[MAXN][MAXN];
int c[MAXN][MAXN];
int a[MAXN][MAXN];

void knuth() {
    for (int i = 0; i < n; i++) {
        f[i][i] = 0;
        a[i][i] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            f[i][j] = oo;
            for (int k = a[i][j - 1]; k <= a[i + 1][j]; k++) {
                if (f[i][j] > f[i][k] + f[k][j] + c[i][j]) {
                    f[i][j] = f[i][k] + f[k][j] + c[i][j];
                    a[i][j] = k;
                }
            }
        }
    }
}

int main() {
    return 0;
}
