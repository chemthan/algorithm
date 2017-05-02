#include <bits/stdc++.h>
using namespace std;

/*
* Problems:
* 1. http://codeforces.com/contest/631/problem/E
* 2. http://codeforces.com/contest/660/problem/F
* 3. http://codeforces.com/gym/100739/problem/K
* 4. http://codeforces.com/contest/455/problem/E
* 5. https://www.codechef.com/problems/CYCLRACE
* 6. http://vn.spoj.com/problems/VOMARIO/Problems
*/
typedef long long T;
const T oo = (T) 1e18;

//O(N, QlogN)
//Adding lines in descending/ascending order by a
struct ConvexhullTrick {
    struct Line {
        T a, b;
        Line(T a, T b) : a(a), b(b) {}
    };
    long double intersect(Line ln1, Line ln2) {
        return (long double) (ln2.b - ln1.b) / (ln1.a - ln2.a);
    }
    int bad(Line ln1, Line ln2, Line ln3) {
        return (long double) (ln1.a - ln2.a) * (ln2.b - ln3.b) >= (long double) (ln2.a - ln3.a) * (ln1.b - ln2.b);
        //return intersect(ln1, ln2) >= intersect(ln2, ln3);
        //return (long double) (ln1.a - ln2.a) * (ln2.b - ln3.b) <= (long double) (ln2.a - ln3.a) * (ln1.b - ln2.b); //for adding in ascending order
        //return intersect(ln1, ln2) <= intersect(ln2, ln3); //for adding in ascending order
    }
    vector<Line> hull;
    vector<long double> pos;
    ConvexhullTrick() {
        pos.push_back(-oo);
        pos.push_back(+oo);
    }
    void add(T a, T b) {
        Line ln(a, b);
        pos.pop_back();
        while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull[hull.size() - 1], ln)) {
            hull.pop_back();
            pos.pop_back();
        }
        hull.push_back(ln);
        if (hull.size() >= 2) pos.push_back(intersect(hull[hull.size() - 2], hull[hull.size() - 1]));
        //if (hull.size() >= 2) pos.push_back(-intersect(hull[hull.size() - 2], hull[hull.size() - 1])); //for adding in ascending order
        pos.push_back(+oo);
    }
    T query(T x) {
        if (!hull.size()) return oo;
        int k = lower_bound(pos.begin(), pos.end(), x) - pos.begin() - 1;
        //int k = lower_bound(pos.begin(), pos.end(), -x) - pos.begin() - 1; //for adding in ascending order
        return hull[k].a * x + hull[k].b;
    }
};

//O(NlogN, QlogN)
//Adding lines in arbitrary order
struct DynamicConvexhullTrick {
    struct Line {
        T a, b;
        Line(T a = 0, T b = 0) : a(a), b(b) {}
        bool operator < (const Line& rhs) const {
            return make_pair(-a, b) < make_pair(-rhs.a, rhs.b);
        }
        bool operator == (const Line& rhs) const {
            return make_pair(a, b) == make_pair(rhs.a, rhs.b);
        }
        bool operator != (const Line& rhs) const {
            return make_pair(a, b) != make_pair(rhs.a, rhs.b);
        }
    };
    long double intersect(Line ln1, Line ln2) {
        return (long double) (ln2.b - ln1.b) / (ln1.a - ln2.a);
    }
    int bad(Line ln1, Line ln2, Line ln3) {
        return (long double) (ln1.a - ln2.a) * (ln2.b - ln3.b) >= (long double) (ln2.a - ln3.a) * (ln1.b - ln2.b);
        //return intersect(ln1, ln2) >= intersect(ln2, ln3);
    }
    set<Line> hull;
    set<pair<long double, Line> > pos;
    void add(T a, T b) {
        Line ln(a, b);
        if (hull.find(ln) != hull.end()) return;
        hull.insert(ln);
        set<Line>::iterator it = hull.find(ln);
        if (it == hull.begin()) {
            pos.insert(make_pair(-oo, ln));
            if (++it != hull.end()) pos.erase(make_pair(-oo, *it));
            it--;
        }
        else {
            Line prv = *(--it); it++;
            if (prv.a == ln.a) {
                hull.erase(ln);
                return;
            }
            if (*it != *hull.rbegin()) {
                Line nxt = *(++it); it--;
                if (bad(prv, ln, nxt)) {
                    hull.erase(ln);
                    return;
                }
                pos.erase(make_pair(intersect(prv, nxt), nxt));
            }
        }
        Line u, v;
        if (it != hull.begin()) {
            v = *(--it);
            while (it != hull.begin()) {
                u = *(--it);
                if (bad(u, v, ln)) {
                    pos.erase(make_pair(intersect(u, v), v));
                    hull.erase(v); it = hull.find(v = u);
                }
                else {
                    it++;
                    break;
                }
            }
            pos.insert(make_pair(intersect(v, ln), ln));
            it++;
        }
        if (*it != *hull.rbegin()) {
            u = *(++it);
            while (*it != *hull.rbegin()) {
                v = *(++it);
                if (ln.a == u.a || bad(ln, u, v)) {
                    pos.erase(make_pair(intersect(u, v), v));
                    hull.erase(u); it = hull.find(u = v);
                }
                else {
                    it--;
                    break;
                }
            }
            pos.insert(make_pair(intersect(ln, u), u));
            it--;
        }
    }
    T query(T x) {
        if (!pos.size()) return oo;
        set<pair<long double, Line> >::iterator it = pos.upper_bound(make_pair(x, Line(-oo, -oo)));
        it--;
        return it->second.a * x + it->second.b;
    }
};

//O(logN) for updating, O(logN^2) for query
const int MAXN = 1e5 + 5;
ConvexhullTrick st[MAXN << 2];
void update(int node, int i, int L, int R, T a, T b) {
    if (i < L || i > R) return;
    st[node].add(a, b);
    if (L == R) return;
    update(node << 1, i, L, L + R >> 1, a, b);
    update(node << 1 | 1, i, (L + R >> 1) + 1, R, a, b);
}
T query(int node, int l, int r, int L, int R, T x) {
    if (l > R || r < L) return oo;
    if (l <= L && r >= R) return st[node].query(x);
    return min(query(node << 1, l, r, L, L + R >> 1, x), query(node << 1 | 1, l, r, (L + R >> 1) + 1, R, x));
}

//O(logN) for updating, query
struct LineSegmentTree {
    static const int MAXN = 1e5 + 5;
    struct Line {
        T a, b;
        Line() {a = 0; b = oo;}
        Line(T a, T b) : a(a), b(b) {}
        T query(T x) {
            return a * x + b;
        }
    };
    Line st[MAXN << 2];
    void update(int node, int l, int r, int L, int R, Line ln) {
        int M = L + R >> 1;
        if (l > R || r < L) return;
        if (l <= L && r >= R) {
            if (ln.query(L) >= st[node].query(L) && ln.query(R) >= st[node].query(R)) {
                return;
            }
            if (ln.query(L) <= st[node].query(L) && ln.query(R) <= st[node].query(R)) {
                st[node] = ln;
                return;
            }
            if (ln.query(L) >= st[node].query(L) && ln.query(M) >= st[node].query(M)) {
                update(node << 1 | 1, l, r, M + 1, R, ln);
                return;
            }
            if (ln.query(L) <= st[node].query(L) && ln.query(M) <= st[node].query(M)) {
                update(node << 1 | 1, l, r, M + 1, R, st[node]);
                st[node] = ln;
                return;
            }
            if (ln.query(M + 1) >= st[node].query(M + 1) && ln.query(R) >= st[node].query(R)) {
                update(node << 1, l, r, L, M, ln);
                return;
            }
            if (ln.query(M + 1) <= st[node].query(M + 1) && ln.query(R) <= st[node].query(R)) {
                update(node << 1, l, r, L, M, st[node]);
                st[node] = ln;
                return;
            }
        }
        else if (L < R) {
            update(node << 1, l, r, L, L + R >> 1, ln);
            update(node << 1 | 1, l, r, (L + R >> 1) + 1, R, ln);
        }
    }
    void update(int node, int l, int r, int L, int R, T a, T b) {
        update(node, l, r, L, R, Line(a, b));
    }
    T query(int node, int i, int L, int R) {
        if (i < L || i > R) return oo;
        T res = oo;
        res = min(res, st[node].query(i));
        if (L < R) {
            res = min(res, query(node << 1, i, L, L + R >> 1));
            res = min(res, query((node << 1) + 1, i, (L + R >> 1) + 1, R));
        }
        return res;
    }
};

int main() {
    srand(time(NULL));
    for (int test = 0; test < 1000; test++) {
        ConvexhullTrick cht;
        DynamicConvexhullTrick dcht;
        vector<pair<long double, long double> > v1, v2;
        for (int i = 0; i < 1000; i++) {
            v1.push_back(make_pair(rand() * rand(), rand() * rand()));
            dcht.add(v1.back().first, v1.back().second);
        }
        sort(v1.begin(), v1.end());
        //reverse(v1.begin(), v1.end());
        for (int i = 0; i < v1.size(); i++) {
            if (!i || v1[i].first != v1[i - 1].first) v2.push_back(v1[i]);
        }
        v1 = v2;
        for (int i = v1.size() - 1; i >= 0; i--) {
            cht.add(v1[i].first, v1[i].second);
        }
        T x = rand();
        if (cht.query(x) != dcht.query(x)) {
            cout << "Wrong!\n";
            return 0;
        }
    }
    cout << "Correct!\n";
    return 0;
}
