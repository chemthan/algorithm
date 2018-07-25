#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: average O(1)
*/
template<class TK, class TV> struct HashTable {
    static const int MAXN = 10000000;
    static const int MAGIC = 7654321;
    int ptr;
    int lst[MAGIC];
    int prv[MAXN];
    TK l[MAXN];
    TV x[MAXN];
    int cnt;
    int used[MAGIC];
    
    HashTable() {
        ptr = 0;
        fill_n(lst, MAGIC, -1);
        cnt = 0;
    }
    void clear() {
        ptr = 0;
        for (int i = 0; i < cnt; i++) {
            lst[used[i]] = -1;
        }
        cnt = 0;
    }
    TV& operator [] (const TK& key) {
        int hs = (key % MAGIC + MAGIC) % MAGIC;
        if (!~lst[hs]) {
            used[cnt++] = hs;
        }
        for (int e = lst[hs]; ~e; e = prv[e]) {
            if (l[e] == key) {
                return x[e];
            }
        }
        l[ptr] = key, x[ptr] = 0;
        prv[ptr] = lst[hs], lst[hs] = ptr;
        return x[ptr++];
    }
    int count(TK key) {
        int hs = (key % MAGIC + MAGIC) % MAGIC;
        for (int e = lst[hs]; ~e; e = prv[e]) {
            if (l[e] == key) {
                return 1;
            }
        }
        return 0;
    }
    void erase(TK key) {
        int hs = (key % MAGIC + MAGIC) % MAGIC;
        int nxt = -1;
        for (int e = lst[hs]; ~e; e = prv[e]) {
            if (l[e] == key) {
                if (!~nxt) {
                    lst[hs] = prv[e];
                }
                else {
                    prv[nxt] = prv[e];
                }
                return;
            }
            nxt = e;
        }
    }
};

HashTable<int, int> hs;

int main() {
    hs[3234234] = 4;
    hs[4123123] = 5;
    cout << hs[3234234] << "\n"; //Expected 4
    cout << hs[4123123] << "\n"; //Expected 5
    cout << hs.count(3234234) << "\n"; //Expected 1
    cout << hs.count(3234235) << "\n"; //Expected 0
    return 0;
}
