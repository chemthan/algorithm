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
 
const int N = 100 + 7;
const int M = N * 10;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
//const double PI = acos(-1);
const bool multipleTest = true;
 
int n, m;
int a[N];
ll dp[N][N];
ll f[N];
 
void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) scanf("%d", a + i);
    sort(a + 1, a + n + 1);
 
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= m; ++j) dp[i][j] = linf;
        f[i] = linf;
    }
 
    dp[0][0] = 0;
    f[0] = 0;
 
    for(int i = 1; i <= n; ++i) {
        dp[i][1] = a[i] - a[1];
        for(int j = 2; j <= m; ++j) {
//            for(int t = 0; t < i; ++t)
//                dp[i][j] = min(dp[i][j], dp[t][j - 1] + a[i] - a[t + 1]);
            dp[i][j] = min(dp[i][j], f[j - 1] + a[i]);
        }
        for(int j = 1; j <= m; ++j)
            f[j] = min(f[j], dp[i][j] - a[i + 1]);
    }
    cout << dp[n][m] << "\n";
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
