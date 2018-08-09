#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
*/
struct ZFuntion {
    int n;
    vector<int> f; //the length of the longest substr begins at i
    void build(char* s) {
        n = strlen(s), f.resize(n);
        int l = 0, r = 0;
        f[0] = n;
        for (int i = 1; i < n; i++) {
            if (i > r) {
                l = r = i;
                while (r < n && s[r] == s[r - l]) r++;
                f[i] = r - l, r--;
            }
            else {
                int k = i - l;
                if (f[k] < r - i + 1) f[i] = f[k];
                else {
                    l = i;
                    while (r < n && s[r] == s[r - l]) r++;
                    f[i] = r - l, r--;
                }
            }
        }
    }
} zf;

int main() {
    zf.build((char*) "stringsrandom");
    for (int i = 0; i < zf.n; i++) {
        cout << zf.f[i] << " \n"[i == zf.n - 1];
    }
    return 0;
}
