#include <bits/stdc++.h>
using namespace std;

#define ST SuffixTree
namespace SuffixTree {
    const int maxn = 1e5 + 5;
    const int maxc = 26 + 1;
    struct node_t {
        node_t* children[maxc];
        node_t* sufflink;
        int start, *end;
        int suffidx;
    };
    char s[maxn];
    node_t* rts;
    node_t* lnode;
    node_t* anode;
    int aedge = -1;
    int alen = 0;
    int cnt = 0;
    int eleaf = -1;
    int* erts;
    int* esplit;
    int size = -1;
    node_t* new_node(int start, int* end) {
        node_t* node = (node_t*) malloc(sizeof(node_t));
        for (int i = 0; i < maxc; i++) node->children[i] = 0;
        node->sufflink = rts; node->start = start;
        node->end = end; node->suffidx = -1;
        return node;
    }
    int edge_len(node_t* p) {
        return *(p->end) - (p->start) + 1;
    }
    int walkdown(node_t *currnode_t) {
        if (alen >= edge_len(currnode_t)) {
            aedge += edge_len(currnode_t);
            alen -= edge_len(currnode_t);
            anode = currnode_t;
            return 1;
        }
        return 0;
    }
    void extend(int pos) {
        eleaf = pos; cnt++; lnode = 0;
        while (cnt > 0) {
            if (!alen) aedge = pos;
            if (!anode->children[s[aedge]]) {
                anode->children[s[aedge]] = new_node(pos, &eleaf);
                if (lnode) {
                    lnode->sufflink = anode;
                    lnode = 0;
                }
            } else {
                node_t* next = anode->children[s[aedge]];
                if (walkdown(next)) continue;
                if (s[next->start + alen] == s[pos]) {
                    if (lnode && anode != rts) {
                        lnode->sufflink = anode;
                        lnode = 0;
                    }
                    alen++;
                    break;
                }
                esplit = (int*) malloc(sizeof(int));
                *esplit = next->start + alen - 1;
                node_t* split = new_node(next->start, esplit);
                anode->children[s[aedge]] = split;
                split->children[s[pos]] = new_node(pos, &eleaf);
                next->start += alen;
                split->children[s[next->start]] = next;
                if (lnode) lnode->sufflink = split;
                lnode = split;
            }
            cnt--;
            if (anode == rts && 0 < alen) {alen--; aedge = pos - cnt + 1;}
            else if (anode != rts) anode = anode->sufflink;
        }
    }
    void upd(node_t* p, int hlabel, int lev = 0) {
        if (!p) return;
        if (!lev) {
            cerr << "root\n";
        }
        else {
            for (int i = 0; i < lev; i++) {
                cerr << "  ";
            }
            for (int i = p->start; i <= *(p->end); i++) {
                cerr << (s[i] ? char(s[i] + 'a' - 1) : '$');
            }
            cerr << "\n";
        }
        int isleaf = 1;
        for (int i = 0; i < maxc; i++) {
            if (p->children[i]) {
                isleaf = 0;
                upd(p->children[i], hlabel + edge_len(p->children[i]), lev + 1);
            }
        }
        if (isleaf) {
            p->suffidx = size - hlabel;
        }
    }
    void clear(node_t* p) {
        if (!p) return;
        for (int i = 0; i < maxc; i++) if (p->children[i]) clear(p->children[i]);
        if (!~p->suffidx) free(p->end);
        free(p);
    }
    void build(char* t) {
        strcpy(s, t);
        size = strlen(s);
        erts = (int*) malloc(sizeof(int));
        *erts = -1;
        rts = new_node(-1, erts);
        anode = rts;
        for (int i = 0; i < size; i++) {
            if (i < size - 1) {
                s[i] = s[i] - 'a' + 1;
            }
            else {
                s[i] = 0;
            }
            extend(i);
        }
        upd(rts, 0);
    }
    void clear() {
        clear(rts);
    }
}

int main() {
    ST::build((char *) "abcabxabcd$");
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

