#include <bits/stdc++.h>
using namespace std;

//Index from 1
struct FullLinkCutTree {
    static const int maxn = 1e5 + 5;
    static const int oo = (int) 1e9;
    
    struct Edge {
        int u, v, c;
    } e[maxn];
    
    struct Node {
        struct Flag {
            int mul, add;
            Flag() : mul(1) {}
            Flag(int mul, int add) : mul(mul), add(add) {}
            int exist() {
                return add || (mul - 1);
            }
            void clear() {
                mul = 1, add = 0;
            }
            void operator += (const Flag& x) {
                mul *= x.mul;
                add = add * x.mul + x.add;
            }
        } cF, tF; //ChainFlag, TreeFlag
        
        struct Info {
            int max, min, sum, sz;
            Info() {}
            Info(int max, int min, int sum, int sz) : max(max), min(min), sum(sum), sz(sz) {}
            Info operator += (const Flag& x) {
                if (!sz) return *this;
                max = max * x.mul + x.add;
                min = min * x.mul + x.add;
                sum = sum * x.mul + x.add * sz;
                return *this;
            }
            void operator += (const Info& x) {
                max = std::max(max, x.max);
                min = std::min(min, x.min);
                sum += x.sum;
                sz += x.sz;
            }
        } cI, tI, aI; //ChainInfo, TreeInfo, AllInfo
        
        Node *s[4], *f;
        int val, inr, rev, use;
        
        void initval() {
            aI = tI = cI = Info(-oo, oo, 0, 0);
            if (!inr) aI = cI = Info(val, val, val, 1);
        }
        void initnode(int ty = 0, int v = 0) {
            inr = ty; val = v;
            initval();
            cF.clear(); tF.clear();
            rev = 0; use = 1;
        }
        int nson() {
            for (int i = 0; i < 4; i++) if (this->f->s[i] == this) return i;
            return 0;
        }
    } *nil, *root, node[maxn << 1];
    
    int ne, value[maxn];
    int tot, top, trash[maxn];

    FullLinkCutTree() {
        ne = top = 0;
        nil = node;
        newnode(1, 0, 0);
        nil->inr = 0;
    }
    void addedge(int u, int v, int c = 0) {
        e[++ne].u = u;
        e[ne].v = v;
        e[ne].c = c;
    }
    void addvalue(int u, int v) {
        value[u] = v;
    }
    void build(int n, int rt) {
        for (int i = 1; i <= n; i++) newnode(0, value[i], ++tot);
        for (int i = 1; i <= ne; i++) {
            makeroot(e[i].u);
            link(e[i].u, e[i].v);
        }
        makeroot(rt);
    }
    Node* newnode(int ty = 0, int v = 0, int id = -1) {
        if (id < 0) {
            if (top) id = trash[top--];
            else id = ++tot;
        }
        Node* p = node + id;
        p->initnode(ty,v);
        p->f = nil;
        fill(p->s, p->s + 4, nil);
        return p;
    }
    inline void updatelz(Node* p) {
        if (p == nil) return;
        if (p->rev) {
            swap(p->s[0], p->s[1]);
            p->s[0]->rev ^= 1;
            p->s[1]->rev ^= 1;
            p->rev = 0;
        }
        if (p->tF.exist()) {
            p->aI = p->tI += p->tF;
            p->aI += p->cI;
            for (int i = 0; i < 4; i++)
                if (p->s[i] != nil) {
                    p->s[i]->tF += p->tF;
                    if (i >= 2) p->s[i]->cF += p->tF;
                }
            p->tF.clear();
        }
        if (p->cF.exist()) {
            p->aI = p->cI += p->cF;
            p->aI += p->tI;
            p->val = p->val * p->cF.mul + p->cF.add;
            for (int i = 0; i < 2; i++)
                p->s[i]->cF += p->cF;
            p->cF.clear();
        }
    }
    void update(Node* p) {
        if (p == nil) return;
        for (int i = 0; i < 4; i++) updatelz(p->s[i]);
        p->initval();
        for (int i = 0; i < 2; i++) p->cI += p->s[i]->cI, p->tI += p->s[i]->tI;
        for (int i = 0; i < 4; i++) p->aI += p->s[i]->aI;
        for (int i = 2; i < 4; i++) p->tI += p->s[i]->aI;
    }
    inline void setchild(Node* u, Node* v, int r) {
        if (u != nil) u ->s[r] = v;
        if (v != nil) v ->f = u;
    }
    void rotate(Node* p, int ty = 0) {
        int k = lr(p, ty);
        Node* w = p->f;
        setchild(w->f, p, w->nson());
        setchild(w, p->s[!k + ty], k + ty);
        setchild(p, w, !k + ty);
        update(w);
    }
    int lr(Node* p, int ty = 0) {
        return p->f->s[1 + ty] == p;
    }
    int isroot(Node* p, int ty = 0) {
        if (ty) return !p->f->inr || !p->inr;
        else return p->f == nil || (p->f->s[0] != p && p->f->s[1] != p);
    }
    void splay(Node* p,int ty = 0) {
        while (!isroot(p, ty)) {
            if (!isroot(p->f, ty)) {
                if (lr(p, ty) == lr(p->f, ty)) rotate(p->f, ty);
                else rotate(p, ty);
            }
            rotate(p, ty);
        }
        update(p);
    }
    void add(Node* u, Node* v) {
        if (v == nil) return;
        updatelz(u); updatelz(v);
        for (int i = 2; i < 4; i++) {
            if (u->s[i] == nil) {
                setchild(u, v, i);
                return;
            }
        }
        Node *p = newnode(1,0), *x;
        for (x = u; x->s[2]->inr; updatelz(x->s[2]), x = x->s[2]);
        setchild(p, v, 3);
        setchild(p, x->s[2], 2);
        setchild(x, p, 2);
        splay(p, 2);
    }
    void rem(Node* p) {
        if (!p->f->inr) setchild(p->f, nil, lr(p, 2) + 2);
        else {
            setchild(p->f->f, p->f->s[3 - lr(p, 2)], lr(p->f, 2) + 2);
            trash[++top] = p->f - node;
            p->f->use = 0;
            splay(p->f->f, 2);
        }
        p->f = nil;
    }
    void clearmark(Node* p) {
        if (p == nil) return;
        clearmark(p->f);
        updatelz(p);
    }
    void splice(Node* p) {
        splay(p);
        Node* w = p->s[0];
        if (w == nil) return;
        w->f = p;
        p->s[0] = nil;
        add(p, w);
        update(p);
    }
    Node* access(Node* p) {
        Node *w = p, *r;
        clearmark(p);
        splice(w);
        for (; w->f != nil; w = r) {
            for (r = w->f; r->inr; r = r->f);
            splice(r);
            rem(w);
            setchild(r, w, 0);
            update(r);
        }
        splay(p);
        return w;
    }
    void makeroot(Node* p) {
        access(p);
        p->rev ^= 1;
    }
    void makeroot(int x) {
        root = node + x;
        makeroot(root);
    }
    Node* findroot(Node* x) {
        while(x->f != nil) x = x->f;
        return x;
    }
    int findroot(int u) {
        return findroot(node + u) - nil;
    }
    Node* cut(int x) {
        Node* u = node + x;
        access(u);
        updatelz(u->s[1]);
        for (u = u->s[1]; u != nil && u->s[0] != nil; u = u->s[0], updatelz(u));
        if (u != nil) access(u), rem(node + x), update(u);
        return u;
    }
    void link(int x, int y) {
        Node *p = cut(x), *u = node + x, *v = node + y;
        if (findroot(u) != findroot(v)) p = v;
        if (p == nil) return;
        access(p);
        add(p, u);
        update(p);
    }
    Node::Info chain(int u, int v, int mul, int add) {
        makeroot(node + u);
        access(node + v);
        splay(node + u);
        node[u].cF += Node::Flag(mul, add);
        Node::Info ans = node[u].cI;
        makeroot(root);
        return ans;
    }
    void alterchain(int u, int v, int mul, int add) {
        chain(u, v, mul, add);
    }
    void altertree(int u, int mul, int add) {
        access(node + u);
        node[u].val = node[u].val * mul + add;
        for (int i = 2; i < 4; i++) {
            node[u].s[i]->tF += Node::Flag(mul, add);
            node[u].s[i]->cF += Node::Flag(mul, add);
        }
        update(node + u);
    }
    Node::Info asktree(int u) {
        access(node + u);
        int val = node[u].val;
        Node::Info ans = Node::Info(val, val, val, 0);
        for (int i = 2; i < 4; i++) updatelz(node[u].s[i]), ans += node[u].s[i]->aI;
        return ans;
    }
    int sumchain(int u, int v) {
        return chain(u, v, 1, 0).sum;
    }
    int minchain(int u, int v) {
        return chain(u, v, 1, 0).min;
    }
    int maxchain(int u, int v) {
        return chain(u, v, 1, 0).max;
    }
    int mintree(int u) {
        return asktree(u).min;
    }
    int maxtree(int u) {
        return asktree(u).max;
    }
    int sumtree(int u) {
        return asktree(u).sum;
    }
    void trace() {
        for (int i = 1; i <= tot; i++) {
            if (!node[i].use) continue;
            cout << i <<": ";
            for (int j = 0; j < 4; j++)
                cout << node[i].s[j] - node << " ";
            cout << " f: " << node[i].f - nil
                 << " rev: " << node[i].rev << " val : "<< node[i].val <<" "
                 << " aSum: " << node[i].aI.sum << " tSum: "<< node[i].tI.sum <<" cSum: " << node[i].cI.sum << "\n";
        }
        cout<<"--------------------------\n";
    }
} flct;

int main() {
    flct.build(3, 1);
    flct.link(2, 1);
    flct.link(3, 1);
    flct.alterchain(2, 3, 1, 3);
    cout << flct.sumtree(1) << "\n"; //Expected 9
    flct.cut(2);
    cout << flct.sumtree(1) << "\n"; //Expected 6
    cout << flct.findroot(3) << "\n"; //Expected 1
    return 0;
}
