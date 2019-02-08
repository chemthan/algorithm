#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(logN) per query
 * Space: O((N + Q)logN)
 */
template<typename num_t>
struct node_t {
    node_t *l, *r;
    int h, size;
    num_t key;
    node_t(num_t key = 0, node_t* l = 0, node_t* r = 0, int h = rand()) : key(key), l(l), r(r), h(h) {
        size = (l ? l->size : 0) + 1 + (r ? r->size : 0);
    }
};
template<typename num_t>
int size(node_t<num_t>* x) {
    return x ? x->size : 0;
}
template<typename num_t>
node_t<num_t>* join(node_t<num_t>* l, node_t<num_t>* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->h < r->h) {
        return new node_t<num_t>(l->key, l->l, join(l->r, r), l->h);
    }
    return new node_t<num_t>(r->key, join(l, r->l), r->r, r->h);
}
template<typename num_t>
node_t<num_t>* split(node_t<num_t>* x, int l, int r) {
    if (!x || r < l) return 0;
    if (l == 0 && r == size(x) - 1) return x;
    if (r <= size(x->l) - 1) return split(x->l, l, r);
    if (size(x->l) + 1 <= l) return split(x->r, l - size(x->l) - 1, r - size(x->l) - 1);
    return new node_t<num_t>(x->key, split(x->l, l, size(x->l) - 1), split(x->r, 0, r - size(x->l) - 1), x->h);
}
template<typename num_t>
int depth(node_t<num_t>* x) {
    if (!x) return 0;
    return 1 + max(depth(x->l), depth(x->r));
}
template<typename num_t>
void trace(node_t<num_t>* x, int isrt = 1) {
    if (!x) return;
    trace(x->l, 0);
    cerr << x->key << " ";
    trace(x->r, 0);
    if (isrt) cerr << "\n";
}

const int maxn = 1e5 + 5;
node_t<int>* p[maxn];

int main() {
    p[1] = join(p[0], new node_t<int>(5));
    p[2] = join(new node_t<int>(1), p[1]);
    p[3] = join(new node_t<int>(2), p[1]);
    trace(p[1]);
    trace(p[2]);
    trace(p[3]);
    p[4] = join(p[2], new node_t<int>(10));
    trace(p[4]);
    for (int i = 0; i < 1e6; i++) {
        p[0] = join(p[0], new node_t<int>(rand()));
    }
    cerr << depth(p[0]) << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
