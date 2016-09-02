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
 
const int N = 4000000 + 7;
const int M = 5000;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-6;
const bool multipleTest = true;
 
 
int n;
double p[N];
double f[N];
void init() {
    p[0] = 1;
    for(int i = 1; i <= 60; ++i) p[i] = p[i - 1] * i;
}
 
int sl[N];
 
void solve() {
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%lf", f + i);
    int Q;
    cin >> Q;
    while (Q-- > 0) {
        double ans = 1;
        int k; scanf("%d", &k);
        for(int i = 1; i <= n; ++i) sl[i] = 0;
 
        for(int i = 0; i < k; ++i) {
            int u; scanf("%d", &u);
            sl[u] ++;
            ans = ans * (i + 1) * f[u];
        }
        //cout << ans << "\n";
        for(int i = 1; i <= n; ++i) if (sl[i] > 1)
            ans /= p[sl[i]];
        int  b;
        char s[100], a[20];
        sprintf( s, "%.5le", ans );
        sscanf( s, "%[^e]e%d", a, &b );
        printf( "%s x 10^%d\n", a, b );
    }
}
 
 
int main() {
 
//    freopen("in.txt", "r", stdin);
 
 
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
    init();
    //cout << p[5] << "\n";
    for(int i = 0; i < Test; ++i) {
        printf("Test Case #%d:\n", i + 1);
        //        if (i > 0) puts("");
        solve();
        //        puts("");
    }
 
 
    //#ifndef ONLINE_JUDGE
    //    cout<<"\n" << diff / CLOCKS_PER_SEC<<endl;
    //#endif
}
