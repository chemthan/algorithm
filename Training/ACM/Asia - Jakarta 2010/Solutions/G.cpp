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
#include <iomanip>
#include <bitset>
 
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
typedef pair<ll, ll> pll;
 
const int N = 100 + 7;
const int M = 23000;
const int inf = 1e9 + 7;
const long long linf = (ll) inf * inf + 7;
const double pi = acos(-1);
const double eps = 1e-20;
const bool multipleTest = true;
 
 
 
int lt[N], invlt[N];
 
int inverse(int x, int n){
    int r = n, newr = x;
    int t = 0, newt = 1;
    while (newr > 0){
        int q = r / newr;
        int tmp = newr;
        newr = r % newr;
        r = tmp;
 
        tmp = newt;
        newt = t - q * newt;
        t = tmp;
    }
    if (t < 0) t += n;
    return t;
}
 
ll f[N][20];
 
int C(int n, int k) {
    return (ll) lt[n] * invlt[n - k] % inf * invlt[k] % inf;
}
 
 
void init() {
    lt[0] = invlt[0] = 1;
    rep(i, 1, N) {
        lt[i] = (ll) lt[i - 1] * i % inf;
        invlt[i] = inverse(lt[i], inf);
    }
 
    for(int t = 1; t < 10; ++t) {
        f[t][t] = (f[t - 1][t - 1] * 10ll + 1) % inf;
        for(int len = t + 1; len < N; ++len) {
            f[len][t] = (f[len - 1][t - 1] * 10 + C(len - 1, t - 1)) % inf;
            f[len][t] = (f[len][t] + f[len - 1][t] * 10ll) % inf;
 
        }
    }
 
    //cout << f[2][1] * 10 + 1 + f[2][2] * 10 << "\n";
    //cout << f[4][3] << "\n";
}
 
 
ll pw(ll x, ll k) {
    if (!k) return 1;
    else if (k & 1) return pw(x, k - 1) * x % inf;
    ll tmp = pw(x, k / 2);
    return tmp * tmp % inf;
}
 
 
int a[N];
int dp[2][N];
 
ll calc(int r) {
    if (a[r] == 0) return 0;
    for(int i = 0; i < N; ++i) dp[0][i] = 0;
    dp[0][0] = 1;
    ll ans = 0;
    int cur = 0;
 
    for(int i = 1; i <= 9; ++i) {
        if (a[i] == 0 || i == r) continue;
        int pre = cur;
        cur ^= 1;
        for(int j = 0; j < N; ++j) dp[cur][j] = dp[pre][j];
 
        for(int j = 0; j < N; ++j) {
            for(int t = 1; t <= a[i]; ++t) {
                if (j >= t) {
                    dp[cur][j] = (dp[cur][j] + (ll)dp[pre][j - t] * C(j, t)) % inf;
                }
            }
        }
    }
 
    for(int t = 1; t <= a[r]; ++t) {
        for(int len = t; len < N; ++len) {
            ans = (ans + f[len][t] * dp[cur][len - t] % inf * r) % inf;
        }
    }
    return ans;
}
 
void solve() {
    for(int i = 1; i <= 9; ++i) scanf("%d", a + i);
 
    ll ans = 0;
    for(int i = 1; i <= 9; ++i)
        ans = (ans + calc(i)) % inf;
 
//    for(int j = 1; j < N; ++j) ans = (ans + dp[cur][j]) % inf;
    cout << ans << "\n";
}
 
int main() {
 
    //    createTest();
    //    return 0;
 
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//    auto t1 = clock();
//#endif
 
    init();
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    for(int i = 0; i < Test; ++i) {
        solve();
    }
 
//#ifndef ONLINE_JUDGE
//    printf("\n%.9lf\n", (0.0 + clock() - t1) / CLOCKS_PER_SEC);
//#endif
}
