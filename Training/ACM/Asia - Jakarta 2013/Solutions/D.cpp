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
 
const int N = 1000 + 7;
const int M = N * 10;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
//const double PI = acos(-1);
const bool multipleTest = true;
 
 
int r[N];
int get(int u) {
    return r[u] < 0 ? u : r[u] = get(r[u]);
}
 
void uni(int u, int v) {
    u = get(u); v = get(v);
    if (r[u] > r[v]) swap(u, v);
    r[u] += r[v];
    r[v] = u;
}
 
viii edge;
int n, m, k;
int p[N];
 
void solve() {
    cin >> n >> m >> k;
    for(int i = 0; i < k; ++i) scanf("%d", p + i);
    for(int i = 1; i <= n; ++i) r[i] = -1;
    for(int i = 1; i < k; ++i) uni(p[0], p[i]);
 
    edge.clear();
    for(int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        edge.push_back(mk(mk(c, u), v));
    }
    int ans = 0;
    sort(edge.begin(), edge.end());
    for(int i = 0; i < m; ++i) {
        int u = edge[i].first.second;
        int v = edge[i].second;
        int c = edge[i].first.first;
        if (get(u) != get(v)) {
            uni(u, v);
            ans += c;
        }
    }
    cout << ans << "\n";
}
 
 
int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
        //t1=clock();
    #endif
 
//    init();
 
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    for(int i = 0; i < Test; ++i) {
        printf("Case #%d: ", i + 1);
        solve();
    }
 
    //#ifndef ONLINE_JUDGE
    //    cout<<"\n" << diff / CLOCKS_PER_SEC<<endl;
    //#endif
}
