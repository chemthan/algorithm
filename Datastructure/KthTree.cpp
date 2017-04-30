#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
*/
template<class TE, class TS> struct KthTree {
    static const int MAXN = 1e5 + 5;
    static const int LOGN = 20;
    int tr[LOGN + 1][MAXN];
    TS sm[LOGN + 1][MAXN];
    void insert(int x, TE t) {
        for (int i = 0; i < LOGN; i++) {
            tr[i][x]++;
            sm[i][x] += t;
            x >>= 1;
        }
    }
    void erase(int x, TE t) {
        for (int i = 0; i < LOGN; i++) {
            tr[i][x]--;
            sm[i][x] -= t;
            x >>= 1;
        }
    }
    TE kthelm(int k) {
        TE res = 0;
        int a = 0, b = LOGN;
        while (b--) {
            a <<= 1;
            k -= tr[b][a] < k ? tr[b][a++] : 0;
            res = sm[b][a] / tr[b][a];
        }
        return res;
    }
    TS kthsum(int k) {
        TS res = 0;
        int a = 0, b = LOGN;
        while (b--) {
            a <<= 1;
            if (tr[b][a] < k) {
                res += sm[b][a];
            }
            k -= tr[b][a] < k ? tr[b][a++] : 0;
            if (!b) res += sm[b][a] / tr[b][a] * k;
        }
        return res;
    }
};
KthTree<int, long long> ktree;

int main() {
    ktree.insert(0, 0), ktree.insert(1, 1), ktree.insert(1, 1);
    ktree.insert(1, 1), ktree.insert(1, 1), ktree.insert(1, 1);
    ktree.insert(2, 2);
    cout << ktree.kthsum(7) << "\n"; //Expected 7
    ktree.erase(2, 2);
    cout << ktree.kthsum(6) << "\n"; //Expected 5
    return 0;
}
