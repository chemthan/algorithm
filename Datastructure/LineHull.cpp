#include <bits/stdc++.h>
using namespace std;

/*
 * Complexity: O(N, logN)
 * Problems:
 * 1. http://codeforces.com/contest/631/problem/E
 * 2. http://codeforces.com/contest/660/problem/F
 * 3. http://codeforces.com/gym/100739/problem/K
 * 4. http://codeforces.com/contest/455/problem/E
 * 5. https://www.codechef.com/problems/CYCLRACE
 */
#define double long double
typedef long long num_t;
const num_t oo = (num_t) 1e18;
struct LineHull {
    struct Line {
        num_t a, b;
        Line(num_t a, num_t b) : a(a), b(b) {}
    };
    double intersect(Line ln1, Line ln2) {
        return (double) (ln2.b - ln1.b) / (ln1.a - ln2.a);
    }
    int bad(Line ln1, Line ln2, Line ln3) {
        return (double) (ln1.a - ln2.a) * (ln2.b - ln3.b) >= (double) (ln2.a - ln3.a) * (ln1.b - ln2.b);
        //return intersect(ln1, ln2) >= intersect(ln2, ln3);
        //return (double) (ln1.a - ln2.a) * (ln2.b - ln3.b) <= (double) (ln2.a - ln3.a) * (ln1.b - ln2.b); //for adding in ascending order
        //return intersect(ln1, ln2) <= intersect(ln2, ln3); //for adding in ascending order
    }
    vector<Line> hull;
    vector<double> pos;
    LineHull() {
        pos.push_back(-oo);
        pos.push_back(+oo);
    }
    void add(num_t a, num_t b) {
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
    num_t query(num_t x) {
        if (!hull.size()) return +oo;
        int k = lower_bound(pos.begin(), pos.end(), x) - pos.begin() - 1;
        //int k = lower_bound(pos.begin(), pos.end(), -x) - pos.begin() - 1; //for adding in ascending order
        return hull[k].a * x + hull[k].b;
    }
} lh;
#undef double

int main() {
    return 0;
}
