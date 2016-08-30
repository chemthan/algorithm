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
 
const int N = 50 + 7;
const int M = N * 10;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
//const double PI = acos(-1);
const bool multipleTest = true;
 
int n;
vii list;
int mx;
int ans = inf;
int h, w;
 
int dp[N][N * 10];
 
void DP() {
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j) dp[i][j] = inf;
 
 
    for(int i = 0; i < n; ++i) {
        if (list[i].second == mx) {
            if (i > 0 && list[i].second - list[i - 1].second <= h)
            for(int j = 0; j < list[i].first; ++j) {
                if ((list[i].first - j) <= w)
                    dp[i + 1][list[i].first] = min(dp[i + 1][list[i].first], dp[i][j]);
            }
            if (list[i].second <= h)
                dp[i + 1][list[i].first] = 0;
            ans = min(ans, dp[i + 1][list[i].first]);
            continue;
        }
 
        if (list[i].second <= h) {
            for(int j = 0; j < M; ++j)
                dp[i + 1][j] = min(dp[i + 1][j], abs(list[i].first - j) * list[i].second);
        }
        if (i == 0 || list[i].second - list[i - 1].second <= h) {
            for(int j = 0; j < M; ++j) {
                for(int t = 0; t < j; ++t) if (j - t <= w) {
                    dp[i + 1][j] = min(dp[i + 1][j],
                                       abs(list[i].first - j) * list[i].second + dp[i][t]);
                }
            }
        }
    }
 
//    for(int i = 1; i <= n; ++i) {
//        for(int j = 0; j < 20; ++j)
//            cout << dp[i][j] << " ";
//        puts("");
//    }
 
}
 
void solve() {
    cin >> n >> h >> w;
    mx = 0;
    ans = inf;
    list.clear();
    for(int i = 0; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        list.push_back(mk(u, v));
        mx = max(mx, v);
    }
 
    DP();
    for(int i = 0; i < list.size(); ++i) list[i].first = 501 - list[i].first;
    reverse(list.begin(), list.end());
    DP();
 
    if (ans < inf) cout << ans << "\n";
    else puts("-1");
 
 
}
 
 
int main() {
//    #ifndef ONLINE_JUDGE
//        freopen("in.txt", "r", stdin);
////    freopen("out.txt", "w", stdout);
//        //t1=clock();
//    #endif
 
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
