#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
*/
const int MAXN = 1e5 + 5;
int ptr;
struct Node {
    Node *l, *r;
    int key, size, rev;
} mem[MAXN], *nil = mem + MAXN - 1;
void init() {
    nil->l = nil->r = nil;
    nil->size = 0;
}
int rd() {
    static int seed = 0;
    seed = (seed * 1001 + 100621) % 999983;
    return seed;
}
void pushup(Node* x) {
    if (x == nil) return;
    x->size = x->l->size + 1 + x->r->size;
}
void pushdown(Node* x) {
    if (x == nil) return;
    if (x->rev) {
        Node* u = x->l;
        Node* v = x->r;
        if (u != nil) swap(u->l, u->r), u->rev ^= 1;
        if (v != nil) swap(v->l, v->r), v->rev ^= 1;
        x->rev = 0;
    }
}
Node* newNode(int key, Node* l = nil, Node* r = nil) {
    Node* x = mem + (ptr++);
    x->l = l, x->r = r, x->key = key;
    x->rev = 0;
    pushup(x);
    return x;
}
Node* join(Node* l, Node* r) {
    if (l == nil) return r;
    if (r == nil) return l;
    if (rd() % (l->size + r->size) < l->size) {
        pushdown(l);
        l->r = join(l->r, r);
        pushup(l);
        return l;
    }
    else {
        pushdown(r);
        r->l = join(l, r->l);
        pushup(r);
        return r;
    }
}
pair<Node*, Node*> split(Node* x, int pos) {
    if (x == nil || !pos) return make_pair(nil, x);
    pushdown(x);
    if (x->l->size >= pos) {
        pair<Node*, Node*> res = split(x->l, pos);
        x->l = res.second;
        pushup(x);
        return make_pair(res.first, x);
    }
    pair<Node*, Node*> res = split(x->r, pos - x->l->size - 1);
    x->r = res.first;
    pushup(x);
    return make_pair(x, res.second);
}
void split(Node* x, Node*& t1, Node*& t2, Node*& t3, int pos1, int pos2) {
    pair<Node*, Node*> res = split(x, pos2);
    t3 = res.second;
    res = split(res.first, pos1 - 1);
    t1 = res.first, t2 = res.second;
}
void reverse(Node*& x, int l, int r) {
    Node *t1, *t2, *t3;
    split(x, t1, t2, t3, l, r);
    swap(t2->l, t2->r), t2->rev ^= 1;
    x = join(join(t1, t2), t3);
}
int depth(Node* x) {
    if (x == nil) return 0;
    return 1 + max(depth(x->l), depth(x->r));
}
void trace(Node* x) {
    if (x == nil) return;
    pushdown(x);
    trace(x->l);
    cout << x->key << " ";
    trace(x->r);
}

int main() {
    init();
    Node* root = nil;
    for (int i = 1; i <= 100000; i++) {
        root = join(root, newNode(i));
    }
    Node *x, *y, *z;
    split(root, x, y, z, 3, 8);
    trace(y); cout << "\n";
    root = join(join(x, y), z);
    cout << depth(root) << "\n";
    return 0;
}
