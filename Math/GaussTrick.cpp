#include <bits/stdc++.h>
using namespace std;

inline void add(int x, vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] & -v[i] & x) x ^= v[i];
    }
    if (!x) return;
    for (int i = 0; i < v.size(); i++) {
        if (x & -x & v[i]) v[i] ^= x;
    }
    v.push_back(x);
}

int main() {
    vector<int> v;
    add(1, v);
    add(2, v);
    add(3, v);
    add(4, v);
    cout << v.size() << "\n";
    return 0;
}
