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
 
const int N = 40 + 7;
const int M = 5000;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-6;
const bool multipleTest = true;
 
 
double f[N];
int sl[N];
int g, n;
 
void init() {
    f[0] = 1;
    for(int i = 1; i < N; ++i) f[i] = f[i - 1] * i;
}
 
double C(int n, int k) {
    return f[n] / f[k] / f[n - k];
}
 
double dp[N];
double pw[N];
 
double calc(int d, int skip) {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int i = 1; i <= n; ++i) {
        if (i == skip) continue;
 
        for(int j = d; j >= sl[i]; --j) {
            dp[j] = 0;
            for(int t = sl[i]; t <= d; ++t)
                if (j >= t) {
                    dp[j] += dp[j - t] * C(j, t);
                }
        }
        for(int j = sl[i] - 1; j >= 0; --j) dp[j] = 0;
    }
    return dp[d];
}
 
void solve() {
    cin >> g >> n;
    int sum = 0;
    for(int i = 1; i <= n; ++i) {
        cin >> sl[i];
        sum += sl[i];
    }
 
    double tol = 0;
 
    pw[0] = 1;
    for(int i = 1; i <= g; ++i) pw[i] = pw[i - 1] * n;
 
    for(int i = 1; i <= n; ++i) {
        for(int d = sum; d <= g; ++d) {
            tol += C(d - 1, sl[i] - 1) * calc(d - sl[i], i) / pw[d];
        }
    }
 
    printf("%.6lf\n", tol * 100);
}
 
 
int main() {
 
//    freopen("in.txt", "r", stdin);
    init();
 
 
//    cout << C(5,2) << "\n";
 
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
