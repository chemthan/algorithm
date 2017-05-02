#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(NlogN)
*/
struct SuffixArray {
    static const int MAXN = 1e5 + 5;
    static const char SEP = '$';
    char T[MAXN];
    int n;
    int RA[MAXN], tmpRA[MAXN];
    int SA[MAXN], tmpSA[MAXN];
    int c[MAXN];
    int Phi[MAXN], PLCP[MAXN];
    int LCP[MAXN];
    void build(char* str) {
        strcpy(T, str);
        n = strlen(T);
        for (int i = 0; i < n; i++) {
            RA[i] = tmpRA[i] = 0;
            SA[i] = tmpSA[i] = 0;
            Phi[i] = PLCP[i] = LCP[i] = 0;
        }
        constructSA();
        computeLCP();
    }
    void countingsort(int k) {
        int sum = 0, maxi = max(300, n);
        memset(c, 0, sizeof(c));
        for (int i = 0; i < n; i++) c[i + k < n ? RA[i + k] : 0]++;
        for (int i = 0; i < maxi; i++) {
            int t = c[i]; c[i] = sum; sum += t;
        }
        for (int i = 0; i < n; i++) tmpSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
        for (int i = 0; i < n; i++) SA[i] = tmpSA[i];
    }
    void constructSA() {
        int r;
        for (int i = 0; i < n; i++) RA[i] = T[i];
        for (int i = 0; i < n; i++) SA[i] = i;
        for (int k = 1; k < n; k <<= 1) {
            countingsort(k);
            countingsort(0);
            tmpSA[SA[0]] = r = 0;
            for (int i = 1; i < n; i++) tmpRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
            for (int i = 0; i < n; i++) RA[i] = tmpRA[i];
            if (RA[SA[n - 1]] == n - 1) break;
        }
    }
    void computeLCP() {
        int L = 0;
        Phi[SA[0]] = -1;
        for (int i = 1; i < n; i++) Phi[SA[i]] = SA[i - 1];
        for (int i = 0; i < n; i++) {
            if (!~Phi[i]) {PLCP[i] = 0; continue;}
            while (T[i + L] == T[Phi[i] + L] && T[i + L] != SEP) L++;
            PLCP[i] = L;
            L = max(L - 1, 0);
        }
        for (int i = 0; i < n; i++) LCP[i] = PLCP[SA[i]];
    }
} sa;

int main() {
    sa.build((char*) "stringsrandom$");
    for (int i = 0; i < sa.n; i++) cout << sa.SA[i] << " \n"[i == sa.n - 1];
    for (int i = 0; i < sa.n; i++) cout << sa.RA[i] << " \n"[i == sa.n - 1];
    for (int i = 0; i < sa.n; i++) cout << sa.LCP[i] << " \n"[i == sa.n - 1];
    return 0;
}
