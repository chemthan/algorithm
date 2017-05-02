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
    Node* parent;
    Node* child[MAXC];
    Node* bfail;
    Node* gfail;
    int key;
    char val;
    Node() {
        parent = 0;
        for (int i = 0; i < MAXC; i++) {
            child[i] = 0;
        }
        bfail = 0;
        gfail = 0;
        key = -1;
        val = 0;
    }
} mem[MAXN], *ptr = mem;
void init() {
    Node* st = mem;
    while (st != ptr) {
        st->parent = 0;
        for (int i = 0; i < MAXC; i++) {
            st->child[i] = 0;
        }
        st->bfail = 0;
        st->gfail = 0;
        st->key = -1;
        st->val = 0;
        st++;
    }
    ptr = mem;
}
Node* insert(Node* x, char* s, int key) {
    while (*s) {
        int c = *s - 'a';
        if (!x->child[c]) {
            x->child[c] = ptr++;
            x->child[c]->parent = x;
            x->child[c]->val = c;
        }
        x = x->child[c];
        s++;
    }
    x->key = key;
    return x;
}
void pushlink(Node* root) {
    static Node* q[MAXN];
    int b = 0, e = 0;
    q[e++] = root;
    while (b < e) {
        Node* x = q[b++];
        for (int i = 0; i < MAXC; i++) {
            if (x->child[i]) q[e++] = x->child[i];
        }
        if (x == root || x->parent == root) {
            x->bfail = root;
            x->gfail = 0;
        }
        else {
            x->bfail = x->parent->bfail;
            while (x->bfail != root && !x->bfail->child[x->val]) x->bfail = x->bfail->bfail;
            if (x->bfail->child[x->val]) x->bfail = x->bfail->child[x->val];
            if (x->bfail->key != -1) x->gfail = x->bfail;
            else x->gfail = x->bfail->gfail;
            //x->info += x->bfail->info;
        }
    }
}
void search(Node* root, char* s) {
    Node* cur = root;
    while (*s) {
        if (cur == root && !cur->child[*s - 'a']) {
            s++;
            continue;
        }
        while (cur != root && !cur->child[*s - 'a']) cur = cur->bfail;
        cur = cur->child[*s - 'a'];
        if (!cur) {
            cur = root;
            continue;
        }
        Node* tmp = cur;
        if (tmp->key == -1) tmp = tmp->gfail;
        while (tmp) {
            cout << tmp->key << " ";
            tmp = tmp->gfail;
        }
        s++;
    }
    cout << "\n";
}

int main() {
    Node* root = ptr++;
    insert(root, (char*) "abab", 0);
    insert(root, (char*) "aba", 1);
    insert(root, (char*) "aabab", 2);
    insert(root, (char*) "ababb", 3);
    insert(root, (char*) "bab", 4);
    pushlink(root);
    search(root, (char*) "aabab");
    return 0;
}
