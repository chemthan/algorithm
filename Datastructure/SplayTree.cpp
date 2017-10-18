#include <bits/stdc++.h>
using namespace std;

struct node_t {
    node_t *p, *l, *r;
    int key, size;
    node_t(int key) : p(0), l(0), r(0), key(key), size(1) {}
};

int size(node_t* x) {
    return x ? x->size : 0;
}

int isrt(node_t* x) {
    return !(x->p) || (x->p->l != x && x->p->r != x);
}

int left(node_t* x) {
    return x->p->l == x;
}

void setchild(node_t* x, node_t* p, int l) {
    (l ? p->l : p->r) = x;
    if (x) x->p = p;
}

void push(node_t* x) {
}

void pull(node_t* x) {
    x->size = size(x->l) + 1 + size(x->r);
}

void rotate(node_t* x) {
    node_t *p = x->p, *g = p->p;
    int l = left(x);
    setchild(l ? x->r : x->l, p, l);
    if (!isrt(p)) setchild(x, g, left(p));
    else x->p = g;
    setchild(p, x, !l);
    pull(p);
}

node_t* splay(node_t* x) {
    push(x);
    while (!isrt(x)) {
        node_t *p = x->p, *g = p->p;
        if (g) push(g);
        push(p), push(x);
        if (!isrt(p)) rotate(left(x) != left(p) ? x : p);
        rotate(x);
    }
    pull(x);
    return x;
}

node_t* join(node_t* x, node_t* y) {
    if (!x) return y;
    while (x->r) push(x), x = x->r;
    push(x);
    setchild(y, x, 0);
    return splay(x);
}

void split(node_t* t, node_t*& x, node_t*& y, int pos) {
    if (pos < 0) {
    	x = 0, y = t;
        return;
    }
    if (pos == size(t) - 1) {
        x = t, y = 0;
        return;
    }
    while (size(t->l) != pos) {
        push(t);
        if (size(t->l) > pos) {
            t = t->l;
        }
        else {
            pos -= size(t->l) + 1;
            t = t->r;
        }
    }
    splay(t);
    x = t;
    y = x->r;
    x->r = y->p = 0;
    pull(x);
}

void split(node_t* t, node_t*& x, node_t*& y, node_t*& z, int l, int r) {
    split(t, x, y, l - 1), split(y, y, z, r - l);
}

void trace(node_t* x) {
    if (!x) return;
    push(x);
    trace(x->l);
    cout << x->key << " ";
    trace(x->r);
}

int main() {
    node_t* rt = 0;
    for (int i = 0; i < 10; i++) {
        rt = join(rt, new node_t(i));
    }
    trace(rt); cout << "\n";
    return 0;
}
