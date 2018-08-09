#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(N)
 * Problems:
 * 1. http://codeforces.com/problemset/problem/434/C
 * 2. https://www.codechef.com/problems/MSDBIN
 */
const int maxn = 1e5 + 5;
const int maxc = 26;
struct node_t {
    node_t* p;
    node_t* c[maxc];
    node_t *bf, *gf;
    int key;
    char val;
    node_t();
    void clear();
} pool[maxn], *ptr = pool;
node_t::node_t() {
    clear();
}
void node_t::clear() {
    p = 0;
    for (int i = 0; i < maxc; i++) c[i] = 0;
    bf = gf = 0, key = -1, val = 0;
}
void clear() {
    node_t* st = pool;
    while (st != ptr) {
        st->clear();
        st++;
    }
    ptr = pool;
}
node_t* insert(node_t* x, char* s, int key) {
    while (*s) {
        int k = *s - 'a';
        if (!x->c[k]) {
            x->c[k] = ptr++;
            x->c[k]->p = x;
            x->c[k]->val = k;
        }
        x = x->c[k];
        s++;
    }
    x->key = key;
    return x;
}
void pushlink(node_t* rt) {
    static node_t* q[maxn];
    int b = 0, e = 0;
    q[e++] = rt;
    while (b < e) {
        node_t* x = q[b++];
        for (int i = 0; i < maxc; i++) {
            if (x->c[i]) q[e++] = x->c[i];
        }
        if (x == rt || x->p == rt) {
            x->bf = rt;
            x->gf = 0;
        }
        else {
            x->bf = x->p->bf;
            while (x->bf != rt && !x->bf->c[x->val]) x->bf = x->bf->bf;
            if (x->bf->c[x->val]) x->bf = x->bf->c[x->val];
            if (x->bf->key != -1) x->gf = x->bf;
            else x->gf = x->bf->gf;
            //x->info += x->bf->info;
        }
    }
}
void search(node_t* rt, char* s) {
    node_t* cur = rt;
    while (*s) {
        if (cur == rt && !cur->c[*s - 'a']) {
            s++;
            continue;
        }
        while (cur != rt && !cur->c[*s - 'a']) cur = cur->bf;
        cur = cur->c[*s - 'a'];
        if (!cur) {
            cur = rt;
            continue;
        }
        node_t* tmp = cur;
        if (tmp->key == -1) tmp = tmp->gf;
        while (tmp) {
            cout << tmp->key << " ";
            tmp = tmp->gf;
        }
        s++;
    }
    cout << "\n";
}

int main() {
    node_t* rt = ptr++;
    insert(rt, (char*) "abab", 0);
    insert(rt, (char*) "aba", 1);
    insert(rt, (char*) "aabab", 2);
    insert(rt, (char*) "ababb", 3);
    insert(rt, (char*) "bab", 4);
    pushlink(rt);
    search(rt, (char*) "aabab");
    return 0;
}
