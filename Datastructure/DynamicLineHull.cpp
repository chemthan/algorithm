#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
* Problems:
* 1. http://codeforces.com/contest/631/problem/E
* 2. http://codeforces.com/contest/660/problem/F
* 3. http://codeforces.com/gym/100739/problem/K
* 4. http://codeforces.com/contest/455/problem/E
* 5. https://www.codechef.com/problems/CYCLRACE
*/
typedef long long T;
const T oo = (T) 1e18;
struct DynamicLineHull {
    struct Line {
        T a, b;
        Line(T a = 0, T b = 0) : a(a), b(b) {}
        int operator < (const Line& rhs) const {
            return make_pair(-a, b) < make_pair(-rhs.a, rhs.b);
        }
        int operator == (const Line& rhs) const {
            return make_pair(a, b) == make_pair(rhs.a, rhs.b);
        }
        int operator != (const Line& rhs) const {
            return make_pair(a, b) != make_pair(rhs.a, rhs.b);
        }
        T query(T x) {
            return a * x + b;
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
} dlh;

int main() {
    return 0;
}
