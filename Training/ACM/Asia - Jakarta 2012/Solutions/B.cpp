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
 
const int N = 200000 + 7;
const int M = 20;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
//const double PI = acos(-1);
const bool multipleTest = true;
 
 
int n;
vii adj[N];
 
int ans = 0;
 
 
void dfs(int u, int r, int pre) {
    int tol = 0, mx = 0;
 
    for(int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j].first;
        int c = adj[u][j].second;
        if (v != r) {
            dfs(v, u, c);
            tol += c;
            mx = max(mx, c);
        }
    }
    if (2 * mx > tol + pre) ans += mx - pre;
    else if (tol >= pre) ans += (tol - pre + 1) / 2;
 
}
 
void solve() {
    cin >> n;
    for(int i = 1; i <= n; ++i) adj[i].clear();
    for(int i = 1; i < n; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[u].push_back(mk(v, c));
        adj[v].push_back(mk(u, c));
    }
 
    ans = 0;
 
    dfs(1, -1, 0);
 
    cout << ans << "\n";
 
 
}
 
 
int main() {
 
 
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
