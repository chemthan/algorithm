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
 
 
string s;
int dp[N][N];
int n, k;
 
void solve() {
    cin >> s >> k;
    n = sz(s);
    int ans = 0;
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) dp[i][j] = inf;
    for(int i = n; i >= 1; --i) {
        dp[i][i] = 0;
        if (i + 1 <= n) dp[i][i + 1] = (s[i - 1] != s[i]);
        for(int j = i + 2; j <= n; ++j) {
            dp[i][j] = dp[i + 1][j - 1];
            if (s[i - 1] != s[j - 1]) dp[i][j] ++;
        }
        for(int j = i; j <= n; ++j) if (dp[i][j] <= k) ans = max(ans, j - i + 1);
    }
    cout << ans << "\n";
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
