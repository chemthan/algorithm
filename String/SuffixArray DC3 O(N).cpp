#include <bits/stdc++.h>
using namespace std;

/*
 * SuffixArray DC3 Algorithm
 * Complexity: O(N)
 */
unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
#define tget(i) ((t[(i) / 8] & mask[(i) % 8]) ? 1 : 0)
#define tset(i, b) t[(i) / 8] = (b) ? (mask[(i) % 8] | t[(i) / 8]) : ((~mask[(i) % 8]) & t[(i) / 8])
#define chr(i) (cs == sizeof(int) ? ((int*) s)[i] : ((unsigned char*) s)[i])
#define isLMS(i) (i > 0 && tget(i) && !tget(i - 1))
void getBuckets(unsigned char* s, int* bkt, int n, int K, int cs, int end) {
    for (int i = 0; i <= K; i++) {
        bkt[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        bkt[chr(i)]++;
    }
    int sum = 0;
    for (int i = 0; i <= K; i++) {
        sum += bkt[i];
        bkt[i] = end ? sum : sum - bkt[i];
    }
}
void induceSAl(unsigned char* t, int* SA, unsigned char* s, int* bkt, int n, int K, int cs, int end) {
    getBuckets(s, bkt, n, K, cs, end);
    for (int i = 0; i < n; i++) {
        int j = SA[i] - 1;
        if (j >= 0 && !tget(j)) {
            SA[bkt[chr(j)]++] = j;
        }
    }
}
void induceSAs(unsigned char* t, int* SA, unsigned char* s, int* bkt, int n, int K, int cs, int end) {
    getBuckets(s, bkt, n, K, cs, end);
    for (int i = n - 1; i >= 0; i--) {
        int j = SA[i] - 1;
        if (j >= 0 && tget(j)) {
            SA[--bkt[chr(j)]] = j;
        }
    }
}
void buildSA(unsigned char* s, int* SA, int n, int K, int cs) {
    unsigned char* t = (unsigned char*) malloc(n / 8 + 1);
    tset(n - 2, 0);
    tset(n - 1, 1);
    for (int i = n - 3; i >= 0; i--) {
        tset(i, (chr(i) < chr(i + 1) || (chr(i) == chr(i + 1) && tget(i + 1) == 1)) ? 1 : 0);
    }
    int* bkt = (int*) malloc(sizeof(int) * (K + 1));
    getBuckets(s, bkt, n, K, cs, true);
    for (int i = 0; i < n; i++) {
        SA[i] = -1;
    }
    for (int i = 1; i < n; i++) if (isLMS(i)) {
        SA[--bkt[chr(i)]] = i;
    }
    induceSAl(t, SA, s, bkt, n, K, cs, 0);
    induceSAs(t, SA, s, bkt, n, K, cs, 1);
    free(bkt);
    int n1 = 0;
    for (int i = 0; i < n; i++) if (isLMS(SA[i])) {
        SA[n1++] = SA[i];
    }
    for (int i = n1; i < n; i++) {
        SA[i] = -1;
    }
    int name = 0, prev = -1;
    for (int i = 0; i < n1; i++) {
        int pos = SA[i];
        int diff = 0;
        for (int d = 0; d < n; d++)
            if (prev == -1 || chr(pos + d) != chr(prev + d) || tget(pos + d) != tget(prev + d)) {
                diff = 1;
                break;
            }
            else if (d > 0 && (isLMS(pos + d) || isLMS(prev + d))) {
                break;
            }
        if (diff) {
            name++;
            prev = pos;
        }
        pos = (pos % 2 == 0) ? pos / 2 : (pos - 1) / 2;
        SA[n1 + pos] = name - 1;
    }
    for (int i = n - 1, j = n - 1; i >= n1; i--) if (SA[i] >= 0) {
        SA[j--] = SA[i];
    }
    int *SA1 = SA, *s1 = SA + n - n1;
    if (name < n1) {
        buildSA((unsigned char*) s1, SA1, n1, name - 1, sizeof(int));
    }
    else {
        for (int i = 0; i < n1; i++) {
            SA1[s1[i]] = i;
        }
    }
    bkt = (int*) malloc(sizeof(int) * (K + 1));
    getBuckets(s, bkt, n, K, cs, 1);
    for (int i = 1, j = 0; i < n; i++) if (isLMS(i)) {
        s1[j++] = i;
    }
    for (int i = 0; i < n1; i++) {
        SA1[i] = s1[SA1[i]];
    }
    for (int i = n1; i < n; i++) {
        SA[i] = -1;
    }
    for (int i = n1 - 1; i >= 0; i--) {
        int j = SA[i];
        SA[i] = -1;
        SA[--bkt[chr(j)]] = j;
    }
    induceSAl(t, SA, s, bkt, n, K, cs, 0);
    induceSAs(t, SA, s, bkt, n, K, cs, 1);
    free(bkt);
    free(t);
}
struct SuffixArray {
    static const int maxn = 1e5 + 5;
    static const int maxc = 256;
    static const unsigned char sep = '$';
    int sa[maxn], ra[maxn];
    int phi[maxn], pclp[maxn];
    int lcp[maxn];
    int n;
    unsigned char s[maxn];

    void build(char* t) {
        n = strlen(t);
        for (int i = 0; i < n; i++) {
            s[i] = t[i];
            ra[i] = sa[i] = 0;
            phi[i] = pclp[i] = lcp[i] = 0;
        }
        s[n] = 0;
        buildSA(s, sa, n + 1, maxc, 1);
        for (int i = 0; i < n; i++) {
            sa[i] = sa[i + 1];
            ra[sa[i]] = i;
        }
        buildLCP();
    }
    void buildLCP() {
        int L = 0;
        phi[sa[0]] = -1;
        for (int i = 1; i < n; i++) phi[sa[i]] = sa[i - 1];
        for (int i = 0; i < n; i++) {
            if (!~phi[i]) {pclp[i] = 0; continue;}
            while (s[i + L] == s[phi[i] + L] && s[i + L] != sep) L++;
            pclp[i] = L;
            L = max(L - 1, 0);
        }
        for (int i = 0; i < n; i++) lcp[i] = pclp[sa[i]];
    }
} sa;

int main() {
    sa.build((char*) "randomstring");
    for (int i = 0; i < sa.n; i++) cout << sa.sa[i] << " \n"[i == sa.n - 1];
    for (int i = 0; i < sa.n; i++) cout << sa.ra[i] << " \n"[i == sa.n - 1];
    for (int i = 0; i < sa.n; i++) cout << sa.lcp[i] << " \n"[i == sa.n - 1];
    /*
    Expected:
    1 3 11 9 5 2 10 4 0 8 6 7
    8 0 5 1 7 4 10 11 9 3 6 2
    0 0 0 0 0 0 1 0 0 1 0 0
     */
    return 0;
}
