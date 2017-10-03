#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: amortized O(logn)
* Problems:
* 1. http://codeforces.com/gym/100796/problem/J
* 2. https://www.codechef.com/problems/SUMBITS
* 3. https://www.codechef.com/problems/BRCKMT
* 4. https://www.codechef.com/problems/FURGRAPH
*/
const int MAXN = 1e5 + 5;
int ptr;
struct Node {
    Node *l, *r, *p;
    int size, key;
    int rev, lz;
    Node();
    void clear();
} mem[MAXN], *nil = mem + MAXN - 1;
Node::Node() {
    clear();
}
void Node::clear() {
    l = r = p = nil;
    size = 1, key = rev = lz = 0;
}
inline Node* newNode(int key) {
    mem[ptr].clear();
    mem[ptr].key = key;
    return mem + (ptr++);
}
inline void init() {
    ptr = 1;
    nil->l = nil->r = nil->p = nil;
    nil->size = 0;
}
inline void normalize(Node*& x) {if (!x) x = nil;}
inline int isrt(Node* x) {
    normalize(x);
    return x->p == nil || (x->p->l != x && x->p->r != x);
}
inline void setchild(Node* p, Node* c, int l) {
    normalize(p), normalize(c);
    c->p = p; l ? p->l = c : p->r = c;
}
inline void updatelz(Node* x, int val) {
    normalize(x);
    if (x == nil) return;
    x->lz += val;
    x->key += val;
}
inline void pushdown(Node* x) {
    normalize(x);
    if (x == nil) return;
    Node *u = x->l, *v = x->r;
    if (x->rev) {
        if (u != nil) {swap(u->l, u->r); u->rev ^= 1;}
        if (v != nil) {swap(v->l, v->r); v->rev ^= 1;}
        x->rev = 0;
    }
    if (x->lz) {
        if (u != nil) updatelz(u, x->lz);
        if (v != nil) updatelz(v, x->lz);
        x->lz = 0;
    }
}
inline void pushup(Node* x) {
    normalize(x);
    if (x == nil) return;
    x->size = x->l->size + x->r->size + 1;
}
inline void rotate(Node* x) {
    normalize(x);
    Node* y = x->p;
    int l = x->p->l == x;
    if (!isrt(y)) {
        setchild(y->p, x, y->p->l == y);
    }
    else {
        x->p = y->p;
    }
    setchild(y, l ? x->r : x->l, l);
    setchild(x, y, !l);
    pushup(y);
}
inline void splay(Node* x) {
    normalize(x);
    pushdown(x);
    while (!isrt(x)) {
        pushdown(x->p->p); pushdown(x->p); pushdown(x);
        if (!isrt(x->p)) rotate((x->p->l == x) == (x->p->p->l == x->p) ? x->p : x);
        rotate(x);
    }
    pushup(x);
}
inline void insert(Node*& x, int key) {
    normalize(x);
    Node* p = nil;
    while (x != nil) {
        pushdown(x);
        p = x;
        if (x->key < key) x = x->r;
        else x = x->l;
    }
    x = newNode(key);
    x->p = p;
    if (p != nil) {
        if (p->key < x->key) p->r = x;
        else p->l = x;
    }
    splay(x);
}
inline Node* findkey(Node*& x, int key) {
    normalize(x);
    Node* p = nil;
    while (x != nil) {
        p = x;
        pushdown(x);
        if (x->key < key) x = x->r;
        else if (key < x->key) x = x->l;
        else {
            splay(x);
            return x;
        }
    }
    x = p, splay(x);
    return nil;
}
inline Node* findpos(Node*& x, int pos) {
    normalize(x);
    Node* p = nil;
    while (x != nil) {
        p = x;
        pushdown(x);
        int k = x->l ? x->l->size + 1 : 1;
        if (pos == k) {
            splay(x);
            return x;
        }
        else if (pos < k) x = x->l;
        else {x = x->r; pos -= k;}
    }
    x = p, splay(x);
    return nil;
}
inline Node* join(Node* x, Node* y) {
    normalize(x), normalize(y);
    x->p = y->p = nil;
    if (x == nil) return y;
    if (y == nil) return x;
    pushdown(y);
    while (1) {
        pushdown(x);
        if (x->r == nil) break;
        x = x->r;
    }
    splay(x);
    setchild(x, y, 0);
    pushup(x);
    return x;
}
inline void erase(Node*& x, int key) {
    normalize(x);
    Node* y = findkey(x, key);
    y->l->p = y->r->p = nil;
    x = join(y->l, y->r);
}
inline void split(Node* x, int pos, Node*& l, Node*& r) {
    normalize(x);
    if (!pos) {l = nil; r = x; return;}
    Node* y = findpos(x, pos);
    if ((r = y->r) != nil) r->p = nil;
    if ((l = y) != nil) {l->r = nil; pushup(l);}
}
inline void split(Node* x, int l, int r, Node*& y, Node*& z, Node*& t) {
    normalize(x);
    split(x, l - 1, y, z);
    split(z, r - l + 1, z, t);
}
inline void reverse(Node*& rt, int l, int r) {
    normalize(rt);
    Node *x, *y, *z, *t;
    split(rt, r, t, z);
    split(t, l - 1, x, y);
    if (y) {
        swap(y->l, y->r);
        y->rev ^= 1;
    }
    rt = join(join(x, y), z);
}
inline void upd(Node*& rt, int l, int r, int val) {
    normalize(rt);
    Node *x, *y, *z;
    split(rt, l, r, x, y, z);
    updatelz(y, val);
    rt = join(join(x, y), z);
}
void trace(Node* x) {
    normalize(x);
    if (x == nil) return;
    pushdown(x);
    trace(x->l);
    cout << x->key << " ";
    trace(x->r);
}

int main() {
    init();
    Node* rt;
    insert(rt, 3);
    insert(rt, 4);
    insert(rt, 5);
    reverse(rt, 1, 2);
    trace(rt); cout << "\n";
    upd(rt, 1, 3, 1);
    trace(rt); cout << "\n";
    upd(rt, 2, 3, 2);
    trace(rt); cout << "\n";
    erase(rt, 5);
    trace(rt); cout << "\n";
    return 0;
}
