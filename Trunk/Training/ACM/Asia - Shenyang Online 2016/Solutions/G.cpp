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
#include <cfloat>
#include <iomanip>
#include <stack>
 
 
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
#define pii pair<int, int>
 
 
typedef complex<ld> cplex;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
 
const int N = 1000000 + 7;
const int M = 100 + 3;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-6;
const bool multipleTest = false;
 
 
ll dp[20][2][2];
ll sum[20];
 
void preCalc() {
 
    dp[0][0][0] = 1;
    dp[0][1][0] = 0;
 
    for(int i = 0; i < 10; ++i) {
        dp[1][i % 2][1]++;
    }
    sum[0] = 1;
    sum[1] = 5;
 
    for(int j = 2; j <= 19; ++j) {
        rep(pre, 0, 2) {
            rep(cur, 0, 2) {
                if (cur != pre) {
                    dp[j][cur][1] += 5 * dp[j - 1][pre][1 ^ pre];
                } else {
                    dp[j][cur][0] += 5 * dp[j - 1][pre][1];
                    dp[j][cur][1] += 5 * dp[j - 1][pre][0];
                }
            }
        }
        for(int t = 1; t < 10; ++t) {
            if (t & 1) sum[j] += dp[j - 1][1][1];
            else {
                sum[j] += dp[j - 1][0][0];
                sum[j] += dp[j - 1][1][0];
            }
        }
        sum[j] += sum[j - 1];
    }
}
 
int a[20];
int k = 0;
 
ll calc(ll x) {
    if (!x) return 1;
    k = 0;
    while(x > 0) {
        a[k ++] = x % 10;
        x /= 10;
    }
 
    if (k == 1) {
        return a[0] / 2 + 1;
    }
 
    ll ans = 0;
    reverse(a, a + k);
    ans = sum[k - 1];
    //cout << k << " " << ans << "\n";
 
    int state = 0, pre = 0;
 
    bool ok = true;
 
    for(int i = 0; i < k; ++i) {
        if (i == 0) {
            for(int j = 1; j < a[i]; ++j) {
                if (j & 1) ans += dp[k - i - 1][1][1];
                else {
                    ans += dp[k - i - 1][1][0];
                    ans += dp[k - i - 1][0][0];
                }
 
            }
        } else {
            if (!ok) continue;
 
            for(int j = 0; j < a[i]; ++j) {
                if (j & 1) {
                    int curLen = 0;
                    if (pre != (j & 1)) {
                        curLen = 1;
                        if (pre == state) continue;
                    }
                    else curLen = state ^ 1;
                    if (i == k - 1) {
                        if (curLen != 1) ++ans;
                    } else {
                        ans += dp[k - i - 1][1][curLen];
                        if (!curLen) ans += dp[k - i - 1][0][1];
                    }
                } else {
//                    cout << "fuck " << j << " " << ans << "\n";
                    int curLen = 0;
                    if (pre != (j & 1)) {
                        curLen = 1;
                        if (pre == state) continue;
                    }
                    else curLen = state ^ 1;
                    //cout << curLen << "\n";
                    if (i == k - 1) {
                        if (curLen != 0) ++ans;
                    } else {
                        ans += dp[k - i - 1][0][1 ^ curLen];
                        if (curLen & 1) ans += dp[k - i - 1][1][0];
                    }
//                    cout << "fuck " << j << " " << ans << "\n";
                }
            }
        }
        if (i == 0) {
            state = 1;
            pre = a[i] & 1;
        } else {
            if ((a[i] & 1) == pre) state ^= 1;
            else {
                if (pre == state) ok = false;
                state = 1;
                pre = a[i] & 1;
            }
        }
    }
    //cout << ans << "\n";
    if (ok && pre != state) ++ans;
    return ans;
}
 
bool check(ll x) {
    if (!x) return true;
    k = 0;
    while (x > 0) {
        a[k ++] = x % 10;
        x /=10;
    }
    int len = 1;
    for(int i = k - 2; i >= 0; --i) {
        if (a[i] % 2 != a[i + 1] % 2) {
            if (len == (a[i + 1] & 1)) return false;
            len = 1;
        } else {
            len ^= 1;
        }
    }
    return len != (a[0] & 1);
}
 
ll cnt(ll x) {
    ll ans = 0;
    for(int d = 0; d <= x; ++d) {
        if (check(d)) ++ans;
        //cout << d << " " << check(d) << "\n";
    }
    return ans;
}
 
 
 
void solve() {
    int T;
    preCalc();
//    cout << cnt(13) << "\n";
//    return;
//    for(int x = 0; x < 10000; ++x) if (cnt(x) != calc(x)) {
//        cout << x << " " << cnt(x) << " " << calc(x) << "\n";
//        return;
//    }
//    return ;
 
 
 
    cin >> T;
    for(int t = 1; t <= T; ++t) {
        ll a, b;
        cin >> a >> b;
        printf("Case #%d: ", t);
        cout << calc(b) - calc(a - 1) << "\n";
    }
 
}
 
void createTest() {
    freopen("in.txt", "w", stdout);
    int tol = 0;
    while (tol < 2000000000) {
        int n = (rand() % 100) + 1;
        tol += n;
        for(int i = 0; i < n; ++i) {
            char c = (rand() % 26) + 'a';
            printf("%c", c);
        }
        puts("");
    }
 
}
 
 
 
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    clock_t t1 = clock();
#endif
//        createTest();
//        return 0;
    //    freopen("out.txt", "w", stdout);
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    for(int i = 0; i < Test; ++i) {
        //        printf("Case #%d: ", i + 1);
        solve();
    }
//    
//#ifndef ONLINE_JUDGE
//    cout << "\n";
//    cout << std::setprecision(5);
//    cout << ((double)clock() - t1) / CLOCKS_PER_SEC << "\n";
//#endif
}
