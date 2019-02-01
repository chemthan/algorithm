#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(logN)
 */

template<typename num_t>
struct node_t {
    node_t *p, *l, *r;
    int size;
    num_t key;
    node_t(int key) : p(0), l(0), r(0), key(key), size(1) {}
};

template<typename num_t>
int size(node_t<num_t>* x) {
    return x ? x->size : 0;
}
template<typename num_t>
int isrt(node_t<num_t>* x) {
    return !(x->p) || (x->p->l != x && x->p->r != x);
}
template<typename num_t>
int left(node_t<num_t>* x) {
    return x->p->l == x;
}
template<typename num_t>
void setchild(node_t<num_t>* x, node_t<num_t>* p, int l) {
    (l ? p->l : p->r) = x;
    if (x) x->p = p;
}
template<typename num_t>
void push(node_t<num_t>* x) {
}
template<typename num_t>
void pull(node_t<num_t>* x) {
    x->size = size(x->l) + 1 + size(x->r);
}
template<typename num_t>
void rotate(node_t<num_t>* x) {
    node_t<num_t> *p = x->p, *g = p->p;
    int l = left(x);
    setchild(l ? x->r : x->l, p, l);
    if (!isrt(p)) setchild(x, g, left(p));
    else x->p = g;
    setchild(p, x, !l);
    pull(p);
}
template<typename num_t>
node_t<num_t>* splay(node_t<num_t>* x) {
    push(x);
    while (!isrt(x)) {
        node_t<num_t> *p = x->p, *g = p->p;
        if (g) push(g);
        push(p), push(x);
        if (!isrt(p)) rotate(left(x) != left(p) ? x : p);
        rotate(x);
    }
    pull(x);
    return x;
}
template<typename num_t>
node_t<num_t>* join(node_t<num_t>* x, node_t<num_t>* y) {
    if (!x) return y;
    while (x->r) push(x), x = x->r;
    push(x);
    setchild(y, x, 0);
    return splay(x);
}
template<typename num_t>
void split(node_t<num_t>* t, node_t<num_t>*& x, node_t<num_t>*& y, int pos) {
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
template<typename num_t>
void split(node_t<num_t>* t, node_t<num_t>*& x, node_t<num_t>*& y, node_t<num_t>*& z, int l, int r) {
    split(t, x, y, l - 1), split(y, y, z, r - l);
}
template<typename num_t>
void trace(node_t<num_t>* x, int isrt = 1) {
    if (!x) return;
    push(x);
    trace(x->l, 0);
    cerr << x->key << " ";
    trace(x->r, 0);
    if (isrt) cerr << "\n";
}

int main() {
    node_t<int>* rt = 0;
    for (int i = 0; i < 10; i++) {
        rt = join(rt, new node_t<int>(i));
    }
    trace(rt);
    for (int i = 0; i < 1e6; i++) {
        rt = join(rt, new node_t<int>(i));
    }
    cerr << size(rt) << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
