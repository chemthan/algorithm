#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
*/
struct node_t {
    node_t *l, *r;
    int h, size, key;
    node_t(int key = 0, node_t* l = 0, node_t* r = 0) : l(l), r(r), h(rand()), size(1), key(key) {}
};
int size(node_t* x) {
    return x ? x->size : 0;
}
void push(node_t* x) {
}
void pull(node_t* x) {
    x->size = size(x->l) + 1 + size(x->r);
}
node_t* join(node_t* l, node_t* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->h < r->h) {
        push(l);
        node_t* res = new node_t(l->key, l->l, join(l->r, r));
        res->h = l->h;
        pull(res);
        return res;
    }
    push(r);
    node_t* res = new node_t(r->key, join(l, r->l), r->r);
    res->h = r->h;
    pull(res);
    return res;
}
node_t* splitL(node_t* x, int pos) {
    if (!x || !pos) return 0;
    push(x);
    if (x->l->size >= pos) return splitL(x->l, pos);
    node_t* res = new node_t(x->key, x->l, splitL(x->r, pos - x->l->size - 1));
    res->h = x->h;
    pull(res);
    return res;
}
node_t* splitR(node_t* x, int pos) {
    if (!x || !pos) return 0;
    push(x);
    if (x->r->size >= pos) return splitR(x->r, pos);
    node_t* res = new node_t(x->key, splitR(x->l, pos - 1 - x->r->size), x->r);
    res->h = x->h;
    pull(res);
    return res;
}
node_t* split(node_t* x, int l, int r) {
    if (!x || l > r) return 0;
    if (l == 1 && r == size(x)) return x;
    if (r <= size(x->l)) return split(x->l, l, r);
    if (size(x->l) + 2 <= l) return split(x->r, l - size(x->l) - 1, r - size(x->l) - 1);
    node_t* res = new node_t(x->key, split(x->l, l, size(x->l)), split(x->r, 1, r - size(x->l) - 1));
    res->h = x->h;
    pull(res);
    return res;
}
int depth(node_t* x) {
    if (!x) return 0;
    push(x);
    return 1 + max(depth(x->l), depth(x->r));
}
void trace(node_t* x, int isrt = 1) {
    if (!x) return;
    push(x);
    trace(x->l, 0);
    cerr << x->key << " ";
    trace(x->r, 0);
    if (isrt) cerr << "\n";
}

const int maxn = 1e5 + 5;
node_t* node[maxn];

int main() {
    node[1] = join(node[0], new node_t(5));
    node[2] = join(new node_t(1), node[1]);
    node[3] = join(new node_t(2), node[1]);
    trace(node[1]);
    trace(node[2]);
    trace(node[3]);
    node[4] = join(node[2], new node_t(10));
    trace(node[4]);
    for (int i = 0; i < 1e6; i++) {
        node[0] = join(node[0], new node_t(rand()));
    }
    cerr << depth(node[0]) << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
