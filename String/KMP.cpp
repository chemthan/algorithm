#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
*/
struct KMP {
    string s;
    int nsz;
    vector<int> link;
    void init(char* str) {
        s = str, nsz = (int) s.size();
        link.resize(nsz);
        int cur = link[0] = -1;
        for (int i = 1; i < nsz; i++) {
            while (cur >= 0 && s[i] != s[cur + 1]) cur = link[cur];
            if (s[i] == s[cur + 1]) cur++;
            link[i] = cur;
        }
    }
    vector<int> search(char* t) {
        vector<int> res;
        int k = strlen(t);
        int cur = -1;
        for (int i = 0; i < k; i++) {
            while (cur >= 0 && t[i] != s[cur + 1]) cur = link[cur];
            if (t[i] == s[cur + 1]) cur++;
            if (cur == nsz - 1) {
                res.push_back(i - nsz + 1);
                cur = link[cur];
            }
        }
        return res;
    }
} kmp;

int main() {
    kmp.init((char*) "123123");
    vector<int> res = kmp.search((char*) "412312312312312312341231231231234");
    for (int i = 0; i < res.size(); i++) cout<<res[i] << " "; cout << "\n"; //Expected 1 4 7 10 13 20 23 26
    return 0;
}
