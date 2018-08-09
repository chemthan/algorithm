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
const int M = 3;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
 
const bool multipleTest = true;
 
 
 
int key[N];
int r[N];
int n;
 
int dist(int u, int v) {
    int ans = 0;
    for(int i = 0; i < 4; ++i) {
        int x = u % 10, y = v % 10;
        u /= 10; v /= 10;
        if (x > y) swap(x, y);
        ans += min(y - x, x + 10 - y);
    }
    return ans;
}
 
int get(int i) {
    return r[i] < 0 ? i : r[i] = get(r[i]);
}
 
void uni(int u, int v) {
    u = get(u); v = get(v);
    if (r[u] > r[v]) swap(u, v);
    r[u] += r[v];
    r[v] = u;
}
 
viii edge;
 
void solve() {
    cin >> n;
    int mn = inf;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", key + i);
        mn = min(mn, dist(0, key[i]));
        r[i] = -1;
    }
    edge.clear();
    for(int i = 1; i <= n; ++i) for(int j = i + 1; j <= n; ++j) {
        edge.push_back(mk(mk(dist(key[i], key[j]), i), j));
    }
 
    sort(edge.begin(), edge.end());
    int ans = 0;
    for(int i = 0; i < edge.size(); ++i) {
        int c = edge[i].first.first;
        int u = edge[i].first.second;
        int v = edge[i].second;
        u = get(u); v = get(v);
        if (u != v) {
            ans += c;
            uni(u, v);
        }
    }
    //cout << mn << "\n";
    cout << ans + mn << "\n";
}
 
 
int main() {
 
//        freopen("in.txt", "r", stdin);
 
 
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    for(int i = 0; i < Test; ++i) {
        //printf("Case #%d: ", i + 1);
//        if (i > 0) puts("");
        solve();
//        puts("");
    }
 
    //#ifndef ONLINE_JUDGE
    //    cout<<"\n" << diff / CLOCKS_PER_SEC<<endl;
    //#endif
}
