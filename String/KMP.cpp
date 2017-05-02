#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
*/
struct KMP {
    string s;
    int n;
    vector<int> link;
    void build(char* str) {
        s = str, n = (int) s.size();
        link.resize(n);
        int cur = link[0] = -1;
        for (int i = 1; i < n; i++) {
            while (cur >= 0 && s[i] != s[cur + 1]) cur = link[cur];
            if (s[i] == s[cur + 1]) cur++;
            link[i] = cur;
        }
    }
    vector<int> query(char* t) {
        vector<int> res;
        int k = strlen(t);
        int cur = -1;
        for (int i = 0; i < k; i++) {
            while (cur >= 0 && t[i] != s[cur + 1]) cur = link[cur];
            if (t[i] == s[cur + 1]) cur++;
            if (cur == n - 1) {
                res.push_back(i - n + 1);
                cur = link[cur];
            }
        }
        return res;
    }
} kmp;

int main() {
    kmp.build((char*) "123123");
    vector<int> res = kmp.query((char*) "412312312312312312341231231231234");
    for (int i = 0; i < res.size(); i++) cout << res[i] << " \n"[i == res.size() - 1]; //Expected 1 4 7 10 13 20 23 26
    return 0;
}
