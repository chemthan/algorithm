#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N)
* Problem:
* 1. http://codeforces.com/problemset/problem/128/B
*/
const int MAXN = 1e5 + 5;
const int MAXC = 26;
struct state {
    int len, link, fpos;
    int nxt[MAXC];
};
struct SuffixAutomaton {
    state st[MAXN << 1];
    int nsz, last;
    int cnt[MAXN << 1];
    long long nchild[MAXN << 1];
    void init() {
        st[0].len = 0;
        st[0].link = -1;
        st[0].fpos = 0;
        memset(st[0].nxt, -1, sizeof(st[0].nxt));
        nsz = 1; last = 0;
        cnt[0] = nchild[0] = 0;
    }
    void extend(char c) {
        int cur = nsz++;
        st[cur].len = st[last].len + 1;
        st[cur].fpos = st[cur].len - 1;
        memset(st[cur].nxt, -1, sizeof(st[cur].nxt));
        cnt[cur] = 1; nchild[cur] = 0;
        int p;
        for (p = last; ~p && !~st[p].nxt[c]; p = st[p].link) st[p].nxt[c] = cur;
        if (!~p) st[cur].link = 0;
        else {
            int q = st[p].nxt[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = nsz++;
                st[clone].len = st[p].len + 1;
                memcpy(st[clone].nxt, st[q].nxt, sizeof(st[q].nxt));
                st[clone].link = st[q].link;
                st[clone].fpos = st[q].fpos;
                cnt[clone] = 0; nchild[clone] = 0;
                for (; ~p && st[p].nxt[c] == q; p = st[p].link) st[p].nxt[c] = clone;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    char cur[MAXN];
    void trace(int u, int len = 0) {
        for (int i = 0; i < MAXC; i++) {
            if (~st[u].nxt[i]) {
                cur[len] = 'a' + i;
                cur[len + 1] = 0;
                cout << cur << "\n";
                trace(st[u].nxt[i], len + 1);
                cur[len] = 0;
            }
        }
    }
    long long ndsubstr(int u) {
        if (nchild[u]) return nchild[u];
        nchild[u] = 1;
        for (int i = 0; i < MAXC; i++) {
            if (~st[u].nxt[i]) {
                nchild[u] += ndsubstr(st[u].nxt[i]);
            }
        }
        return nchild[u];
    }
    string kth(int u, int k) {
        if (!k) return "";
        int tot = 0;
        for (int i = 0; i < MAXC; i++) {
            if (~st[u].nxt[i]) {
                int v = st[u].nxt[i];
                if (tot + nchild[v] >= k) {
                    return char('a' + i) + kth(v, k - tot - 1);
                }
                tot += nchild[v];
            }
        }
        return "";
    }
    int minshift(int u, int k) {
        if (!k) return st[u].fpos;
        for (int i = 0; i < MAXC; i++) {
            if (~st[u].nxt[i]) {
                return minshift(st[u].nxt[i], k - 1);
            }
        }
    }
    void updatesize() {
        vector<int> v, vis(nsz, 0);
        queue<int> q;
        q.push(0); vis[0] = 1;
        while (q.size()) {
            int u = q.front(); q.pop();
            v.push_back(u);
            for (int i = 0; i < MAXC; i++) {
                if (~st[u].nxt[i] && !vis[st[u].nxt[i]]) {
                    q.push(st[u].nxt[i]);
                    vis[st[u].nxt[i]] = 1;
                }
            }
        }
        for (int i = v.size() - 1; i > 0; i--) {
            int u = v[i];
            cnt[st[u].link] += cnt[u];
        }
    }
    int repstr(string str) {
        int idx = 0, cur = 0;
        while (cur < str.size()) {
            idx = st[idx].nxt[str[cur] - 'a'];
            if (!~idx) return 0;
            cur++;
        }
        return cnt[idx];
    }
    int firstpostn(string str) {
        int cur = 0, vtx = 0;
        while (cur < str.size()) {
            vtx = st[vtx].nxt[str[cur] - 'a'];
            if (!~vtx) return -1;
            cur++;
        }
        return st[vtx].fpos - str.size() + 1;
    }
} sa;

string lcs(string s, string t) {
    sa.init();
    for (int i = 0; i < s.size(); i++) {
        sa.extend(s[i] - 'a');
    }
    int v = 0, l = 0, best = 0, bestpos = 0;
    for (int i = 0; i < t.size(); i++) {
        while (v && !~sa.st[v].nxt[t[i] - 'a']) {
            v = sa.st[v].link;
            l = sa.st[v].len;
        }
        if (~sa.st[v].nxt[t[i] - 'a']) {
            v = sa.st[v].nxt[t[i] - 'a'];
            l++;
        }
        if (best < l) {
            best = l;
            bestpos = i;
        }
    }
    return t.substr(bestpos - best + 1, best);
}

int main() {
    string s = "bcabc";
    sa.init();
    for (int i = 0; i < s.size(); i++) {
        sa.extend(s[i] - 'a');
    }
    sa.trace(0); cout << "\n";
    cout << sa.ndsubstr(0) << "\n"; //Total distinct substring, include empty one
    cout << sa.kth(0, 3) << "\n"; //kth smallest substring
    sa.updatesize();
    cout << sa.repstr("e") << "\n"; //The number of occurrences
    s += s;
    sa.init();
    for (int i = 0; i < s.size(); i++) {
        sa.extend(s[i] - 'a');
    }
    cout << sa.minshift(0, s.size() >> 1) - (s.size() >> 1) + 1 << "\n";
    cout << sa.firstpostn("ab") << "\n";
    cout << lcs("abcdef", "gcdeft") << "\n";
    return 0;
}
