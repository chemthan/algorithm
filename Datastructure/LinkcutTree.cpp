#include <bits/stdc++.h>
using namespace std;

struct node_t {
    node_t *p, *l, *r;
    int size, rev;
    int s, w;
    node_t() : p(0), l(0), r(0), size(1), rev(0), s(0), w(1) {}
};

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
    node_t* u = x->l;
    node_t* v = x->r;
    if (x->rev) {
        if (u) swap(u->l, u->r), u->rev ^= 1;
        if (v) swap(v->l, v->r), v->rev ^= 1;
        x->rev = 0;
    }
}

int size(node_t* x) {
    return x ? x->size : 0;
}

int sum(node_t* x) {
    return x ? x->s : 0;
}

void pull(node_t* x) {
    x->size = size(x->l) + 1 + size(x->r);
    x->s = sum(x->l) + x->w + sum(x->r);
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

node_t* access(node_t* x) {
    node_t* z = 0;
    for (node_t* y = x; y; y = y->p) {
        splay(y);
        y->w += sum(y->r);
        y->r = z;
        y->w -= sum(y->r);
        pull(z = y);
    }
    splay(x);
    return z;
}

void link(node_t* x, node_t* p) {
    access(x), access(p);
    x->p = p;
    p->w += sum(x);
}

void cut(node_t* x) {
    access(x);
    x->l->p = 0, x->l = 0;
    pull(x);
}

void makeroot(node_t* x) {
    access(x);
    x->rev ^= 1;
    swap(x->l, x->r);
}

node_t* findroot(node_t* x) {
    access(x);
    while (x->l) push(x), x = x->l;
    push(x);
    return splay(x);
}

node_t* lca(node_t* x, node_t* y) {
    if (findroot(x) != findroot(y)) return 0;
    access(x);
    return access(y);
}

int connect(node_t* x, node_t* y) {
    if (x == y) return 1;
    access(x), access(y);
    return x->p != 0;
}

int treequery(node_t* x) {
    access(x);
    return x->w;
}

const int maxn = 1e5 + 5;
node_t pool[maxn];

void makeroot(int u) {
    makeroot(pool + u);
}

void link(int u, int v) {
    link(pool + u, pool + v);
}

void cut(int u) {
    cut(pool + u);
}

int findroot(int u) {
    return findroot(pool + u) - pool;
}

int lca(int u, int v) {
    node_t* a = lca(pool + u, pool + v);
    if (!a) return -1;
    return a - pool;
}

int connect(int u, int v) {
    return connect(pool + u, pool + v);
}

int treequery(int u) {
    return treequery(pool + u);
}

int main() {
    link(0, 1);
    link(2, 1);
    link(3, 2);
    link(4, 2);
    link(5, 3);
    cout << treequery(2) << "\n";
    makeroot(2);
    cout << treequery(2) << "\n";
    return 0;
}
