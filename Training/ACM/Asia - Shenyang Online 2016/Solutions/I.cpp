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
 
const int N = 300 + 7;
const int M = 100 + 3;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-6;
const bool multipleTest = false;
 
 
 
ll L[N][N];
ll dp[N];
int a[N], key[N];
 
void solve() {
    int T;
    cin >> T;
    while (T-- > 0) {
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) scanf("%d", a + i);
        for(int i = 0; i < n; ++i) scanf("%d", key + i);
 
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) L[i][j] = -linf;
 
        for(int i = n - 1; i >= 0; --i) {
            if (i + 1 < n && __gcd(a[i], a[i + 1]) > 1) L[i][i + 1] = key[i] + key[i + 1];
            for(int j = i + 3; j < n; j += 2) {
                if (__gcd(a[i], a[j]) > 1) {
                    L[i][j] = L[i + 1][j - 1] + key[i] + key[j];
                    for(int k = i + 1; k + 1 < j; k += 2) {
                        L[i][j] = max(L[i][j], L[i + 1][k - 1] + L[k][j - 1] + key[i] + key[j]);
                    }
                }
 
                for(int k = i + 2; k < j; k += 2)
                    L[i][j] = max(L[i][j], L[i][k - 1] + L[k][j]);
            }
        }
 
        for(int i = 0; i < n; ++i) {
            dp[i] = 0;
            if (i > 0) dp[i] = dp[i - 1];
 
            for(int j = i - 1; j >= 0; j -= 2) {
                ll pre = 0;
                if (j > 0) pre = max(pre, dp[j - 1]);
                dp[i] = max(dp[i], pre + L[j][i]);
            }
        }
        cout << dp[n - 1] << "\n";
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
