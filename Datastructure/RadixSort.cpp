#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(W * (2 ^ H + N))
*/
template<class T> struct RadixSort {
    static const int MAXN = 1e5 + 5;
    static const int W = 4;
    static const int H = (sizeof(T) * 8 + W - 1) / W;
    static const int MSK = (1 << H) - 1;
    T tmp[MAXN];
    int cnt[1 << H];
    int p[1 << H];
    
    void sort(T st[], T ed[]) {
        int n = ed - st;
        for (int step = 0; step < W; step++) {
            for (int i = 0; i < n; i++) {
                cnt[st[i] >> step * H & MSK]++;
                tmp[i] = st[i];
            }
            p[0] = 0;
            for (int i = 1; i < (1 << H); i++) {
                p[i] = p[i - 1] + cnt[i - 1];
                cnt[i - 1] = 0;
            }
            cnt[(1 << H) - 1] = 0;
            for (int i = 0; i < n; i++) {
                st[p[tmp[i] >> step * H & MSK]++] = tmp[i];
            }
        }
    }
    
};
RadixSort<int> radix;

const int maxn = 1e5 + 5;
int n;
int a[maxn];

int main() {
    srand(time(NULL));
    n = 100000;
    for (int i = 0; i < n; i++) a[i] = rand();
    radix.sort(a, a + n);
    for (int i = 0; i < n - 1; i++) {
        assert(a[i] <= a[i + 1]);
    }
    cout << "Correct!\n";
    return 0;
}
