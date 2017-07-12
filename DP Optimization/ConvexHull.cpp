#include <bits/stdc++.h>
using namespace std;

/*
* f[i] = min(ff[i][j] = f[j] + c[j][i]), j < i
* Sufficient condition: there exist g, h such that:
* 1. g is increasing
* 2. ff[i][j] <= ff[i][k] <=> h[j][k] <= g[i], i > j > k
*/

typedef double T;
const int MAXN = 1e5 + 5;
int n;
int f[MAXN];
int dq[MAXN];

int C(int j, int i) {return 0;} //Need to modify
int ff(int i, int j) {return f[j] + C(j, i);} //Need to modify
T gg(int i) {return 0.0;} //Need to modify
T hh(int j, int k) {return 0.0;} //Need to modify
int worse1(int i, int j, int k) {return hh(j, k) <= gg(i);}
int worse2(int i, int j, int k) {return hh(i, j) <= hh(j, k);}

void doit() {
    int qh = 0, qe = 0;
    dq[qe++] = 0;
    f[0] = 0; //Need to modify
    for (int i = 1; i < n; i++) {
        while (qe - qh > 1 && worse1(i, dq[qh + 1], dq[qh])) qh++;
        f[i] = ff(i, dq[qh]);
        while (qe - qh > 1 && worse2(i, dq[qe - 1], dq[qe - 2])) qe--;
        dq[qe++] = i;
    }
}

int main() {
    return 0;
}
