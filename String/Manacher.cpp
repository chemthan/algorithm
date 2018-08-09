#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
*/
struct Manachar {
    int n;
    vector<int> d; //Radius of odd palindromes
    vector<int> e; //Radius of even palindromes
    int build(char* s) {
        n = strlen(s), d.resize(n), e.resize(n);
        int res = 0;
        int l = 0, r = -1;
        for (int i = 0; i < n; ++i) {
            int k = (i > r) ? 1 : min(d[l + r - i], r - i) + 1;
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
            d[i] = --k;
            res = max(res, k + k + 1);
            if (r < i + k) {
                l = i - k;
                r = i + k;
            }
        }
        l = 0; r = -1;
        for (int i = 0; i < n; ++i) {
            int k = (i > r) ? 1 : min(e[l + r - i + 1], r - i + 1) + 1;
            while (i - k >= 0 && i + k - 1 < n && s[i - k] == s[i + k - 1]) k++;
            e[i] = --k;
            res = max(res, k + k);
            if (r < i + k - 1) {
                l = i - k;
                r = i + k - 1;
            }
        }
        return res;
    }
} mnc;

int main() {
    cout << mnc.build((char*) "aaadefede") << "\n";
    for (int i = 0; i < mnc.n; i++) {
        cout << mnc.d[i] << " \n"[i == mnc.n - 1];
    }
    for (int i = 0; i < mnc.n; i++) {
        cout << mnc.e[i] << " \n"[i == mnc.n - 1];
    }
    return 0;
}
