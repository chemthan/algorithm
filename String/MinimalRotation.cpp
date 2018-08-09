#include <bits/stdc++.h>
using namespace std;

/*
* Find minimal rotation
* Complexity: O(N)
* Problems:
* 1. http://www.spoj.com/problems/MINMOVE/
*/

int min_rotation(string s) {
    int n = (int) s.size();
    s += s;
    
    int a = 0;
    for (int b = 0; b < n; b++) {
        for (int i = 0; i < n; i++) {
            if (a + i == b || s[a + i] < s[b + i]) {
                b += max(0, i - 1);
                break;
            }
            if (s[a + i] > s[b + i]) {
                a = b;
                break;
            }
        }
    }
    return a;
}

int main() {
    cout << min_rotation("adbcadbcadbcaa") << "\n";
    return 0;
}
