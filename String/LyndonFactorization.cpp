#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
*/

vector<string> factorize(string s) {
    vector<string> res;
    int n = s.size(), i = 0;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while (i <= k) {
            res.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return res;
}

int main() {
    //abcdefasdf abcdefasdf abcdea
    vector<string> res = factorize("abcdefasdfabcdefasdfabcdea");
    for (int i = 0; i < (int) res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }
    return 0;
}
