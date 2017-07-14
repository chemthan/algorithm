#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
* Problems:
* 1. http://codeforces.com/problemset/problem/434/C
* 2. https://www.codechef.com/problems/MSDBIN
*/
const int MAXN = 1e5 + 5;
const int MAXC = 26;
struct Node {
    Node* p;
    Node* c[MAXC];
    Node *bf, *gf;
    int key;
    char val;
    Node();
    void clear();
} mem[MAXN], *ptr = mem;
Node::Node() {
    clear();
}
void Node::clear() {
    p = 0;
    for (int i = 0; i < MAXC; i++) c[i] = 0;
    bf = gf = 0, key = -1, val = 0;
}
void clear() {
    Node* st = mem;
    while (st != ptr) {
        st->clear();
        st++;
    }
    ptr = mem;
}
Node* insert(Node* x, char* s, int key) {
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
void pushlink(Node* rt) {
    static Node* q[MAXN];
    int b = 0, e = 0;
    q[e++] = rt;
    while (b < e) {
        Node* x = q[b++];
        for (int i = 0; i < MAXC; i++) {
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
void search(Node* rt, char* s) {
    Node* cur = rt;
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
        Node* tmp = cur;
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
    Node* rt = ptr++;
    insert(rt, (char*) "abab", 0);
    insert(rt, (char*) "aba", 1);
    insert(rt, (char*) "aabab", 2);
    insert(rt, (char*) "ababb", 3);
    insert(rt, (char*) "bab", 4);
    pushlink(rt);
    search(rt, (char*) "aabab");
    return 0;
}
