include <iostream>
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
 
void init() {
    lt[0] = invlt[0] = 1;
    rep(i, 1, N) {
        lt[i] = (ll) lt[i - 1] * i % inf;
        invlt[i] = inverse(lt[i], inf);
    }
}
 
int C(int n, int k) {
    if (n < k) return 0;
    return (ll) lt[n] * invlt[n - k] % inf * invlt[k] % inf;
}
 
ll pw(ll x, ll k) {
    if (!k) return 1;
    else if (k & 1) return pw(x, k - 1) * x % inf;
    ll tmp = pw(x, k / 2);
    return tmp * tmp % inf;
}
 
 
 
void solve() {
 
    init();
 
    int T;
    cin >> T;
    while (T-- > 0) {
        int m, n, k;
        cin >> n >> m >> k;
        if (m == 1) {
            printf("%d\n", n);
            continue;
        }
        if (k * m + m > n) printf("%d\n", 0);
        else {
            int ans = 1ll * C(n - k * m - 1, m - 1) * n % inf * inverse(m, inf) % inf;
//            ans = (ans + C(n - k * m - 1, m)) % inf;
            printf("%d\n", ans);
        }
 
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
