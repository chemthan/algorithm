#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
*/
struct node_t {
    node_t *l, *r;
    int h, size;
    int key, rev, lz;
    node_t(int key) : l(0), r(0), h(rand()), size(1), key(key) {}
};

int size(node_t* x) {
    return x ? x->size : 0;
}
void push(node_t* x) {
    node_t* u = x->l;
    node_t* v = x->r;
    if (x->rev) {
        if (u) swap(u->l, u->r), u->rev ^= 1;
        if (v) swap(v->l, v->r), v->rev ^= 1;
        x->rev = 0;
    }
    if (x->lz) {
        if (u) u->key += x->lz, u->lz += x->lz;
        if (v) v->key += x->lz, v->lz += x->lz;
        x->lz = 0;
    }
}
void pull(node_t* x) {
    x->size = size(x->l) + 1 + size(x->r);
}
node_t* join(node_t* x, node_t* y) {
    if (!x) return y;
    if (!y) return x;
    if (x->h < y->h) {
        push(x);
        x->r = join(x->r, y);
        pull(x);
        return x;
    }
    push(y);
    y->l = join(x, y->l);
    pull(y);
    return y;
}
void split(node_t* x, node_t*& l, node_t*& r, int pos) {
    if (!x) {
        l = r = 0;
        return;
    }
    push(x);
    if (size(x->l) + 1 <= pos) {
        split(x->r, x->r, r, pos - size(x->l) - 1);
        pull(l = x);
    }
    else {
        split(x->l, l, x->l, pos);
        pull(r = x);
    }
}
void split(node_t* t, node_t*& x, node_t*& y, node_t*& z, int l, int r) {
    split(t, x, y, l);
    split(y, y, z, r - l + 1);
}
void reverse(node_t*& x, int l, int r) {
    node_t *y, *z;
    split(x, x, y, z, l, r);
    y->rev ^= 1;
    swap(y->l, y->r);
    x = join(x, join(y, z));
}
void upd(node_t*& x, int l, int r, int val) {
    node_t *y, *z;
    split(x, x, y, z, l, r);
    y->lz += val;
    y->key += val;
    x = join(x, join(y, z));
}
int depth(node_t* x) {
    if (!x) return 0;
    push(x);
    return 1 + max(depth(x->l), depth(x->r));
}
void trace(node_t* x) {
    if (!x) return;
    push(x);
    trace(x->l);
    cout << x->key << " ";
    trace(x->r);
}
int main() {
    srand(time(NULL));
    node_t* rt = 0;
    for (int i = 0; i < 100000; i++) {
        rt = join(rt, new node_t(i));
    }
    node_t *x, *y, *z;
    split(rt, x, y, z, 3, 8);
    trace(y); cout << "\n";
    rt = join(join(x, y), z);
    cout << depth(rt) << "\n";
    return 0;
}
