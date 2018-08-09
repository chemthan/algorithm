#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <queue>
#include <cmath>
#include <map>
#include <complex>
#include <cstring>
 
using namespace std;
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define repd(i, a, b) for(int i = (a); i > (b); i--)
#define forIt(it, a) for(__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define forRev(it, a) for(__typeof((a).rbegin()) it = (a).rbegin(); it != (a).rend(); it++)
#define ft(a) __typeof((a).begin())
#define ll long long
#define ld long double
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define bitcount(n) __builtin_popcountll(n)
 
 
typedef complex<ld> cplex;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
 
const int N = 1000000 + 7;
const int M = 1000000;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
//const double PI = acos(-1);
const bool multipleTest = true;
 
 
struct node{
    int val;
    int lz;
};
 
node tree[4][N * 4];
 
 
int key[4][N];
void init() {
    for(int i = 0; i < N; ++i) {
        int pw = 1;
        for(int t = 0; t < 4; ++t) {
            key[t][i] = pw;
            key[t][i] = (key[t][i] + key[t][i - 1]) % inf;
            pw = (ll) pw * i % inf;
        }
    }
}
 
 
void update(int num, int i, int l, int r, int u, int v, int val);
 
inline void downNode(int num, int i, int l, int r) {
 
    if (tree[num][i].lz) {
        int nxt = i << 1, g = (l + r) >> 1;
        update(num, nxt, l, g, l, g, tree[num][i].lz);
        update(num, nxt + 1, g + 1, r, g + 1, r, tree[num][i].lz);
        tree[num][i].lz = 0;
    }
}
 
inline void upNode(int num, int i) {
    int lef = i << 1; int rig = lef + 1;
    tree[num][i].val = (tree[num][lef].val + tree[num][rig].val) % inf;
}
 
inline void update(int num, int i, int l, int r, int u, int v, int val) {
 
    if (l == u && r == v) {
        int kk = key[num][r];
        if (l) kk -= key[num][l - 1];
        kk = (kk % inf);
        if (kk < 0) kk += inf;
 
        tree[num][i].val = (tree[num][i].val + (ll) val * kk) % inf;
        tree[num][i].lz = (tree[num][i].lz + val) % inf;
        return;
    }
 
    int g = (l + r) >> 1, nxt = i << 1;
 
    downNode(num, i, l, r);
 
    if (u <= g)
        update(num, nxt, l, g, u, min(g, v), val);
 
    if (g < v)
        update(num, nxt + 1, g + 1, r, max(u, g + 1), v, val);
 
    upNode(num, i);
}
 
 
int get(int num, int i, int l, int r, int u, int v) {
    if (u <= l && r <= v) return tree[num][i].val % inf;
    if (u > r || v < l) return 0;
    downNode(num, i, l, r);
    int g = (l + r) >> 1, nxt = i << 1;
    int ans = get(num, nxt, l, g, u, v);
    ans = (ans + get(num, nxt + 1, g + 1, r, u, v)) % inf;
    upNode(num, i);
    return ans % inf;
}
 
int get(int l, int r) {
    int ans = 0;
    for(int i = 0; i < 4; ++i) {
        ans = (ans + get(i, 1, 0, M, l, r)) % inf;
    }
    return ans;
}
 
 
void buildTree(int i, int l, int r) {
    if (l == r) {
        int pw = 1;
        for(int t = 0; t < 4; ++t) {
            tree[t][i].val = 0;
            tree[t][i].lz = 0;
            pw = (ll) pw * l % inf;
        }
        return;
    }
    int g = (l + r) >> 1, nxt = i << 1;
    buildTree(nxt, l, g);
    buildTree(nxt + 1, g + 1, r);
    for(int t = 0; t < 4; ++t) {
        tree[t][i].val = 0;
        tree[t][i].lz = 0;
    }
}
 
ll x[4];
 
 
void solve() {
    buildTree(1, 0, M);
    int Q;
    cin >> Q;
    char s[5];
    puts("");
    while (Q-- > 0) {
        scanf("%s", s);
        int x1, x2;
        scanf("%d%d", &x1, &x2);
 
        for(int i = 3; i >= 0; --i) scanf("%lld", x + i);
        //cout << "fuck";
        if (s[0] == 'p') {
            // update
        } else {
            int E = get(x1, x2);
            printf("%d\n", E);
            x1 = (ll) x1 * E % M;
            x2 = (ll) x2 * E % M;
            int tmp = max(x1, x2);
            x1 = min(x1, x2);
            x2 = tmp;
        }
        //        cout << x1 << " " << x2 << "\n";
        //        update(0, 1, 0, M, x1, x2, d);
        //        update(1, 1, 0, M, x1, x2, c);
        //        update(2, 1, 0, M, x1, x2, b);
        //        update(3, 1, 0, M, x1, x2, a);
        for(int t = 0; t < 4; ++t) {
            x[t] %= inf;
            if (x[t] < 0) x[t] += inf;
            update(t, 1, 0, M, x1, x2, x[t]);
        }
    }
}
 
 
int main() {
 
//        freopen("in.txt", "r", stdin);
 
    init();
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    for(int i = 0; i < Test; ++i) {
        printf("Case #%d:", i + 1);
        solve();
    }
 
    //#ifndef ONLINE_JUDGE
    //    cout<<"\n" << diff / CLOCKS_PER_SEC<<endl;
    //#endif
}
