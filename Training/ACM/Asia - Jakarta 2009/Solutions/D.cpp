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
 
 
int x[9] = {-1, 0, 1, 1, 1, 0, -1, -1, 0};
int y[9] = {-1, -1, -1, 0, 1, 1, 1, 0, 0};
int n, m;
 
int c[20][20];
string s[20];
int dp[1 << 20];
 
bool valid(int u, int v) {
    return u >= 0 && v >= 0 && u < 10 && v < 10;
}
 
int getMask(int u, int v) {
    if (!valid(u, v)) return -1;
    int mask = 0;
    for(int i = 0; i < 9; ++i) {
        int _u = u + x[i];
        int _v = v + y[i];
        if (valid(_u, _v)) {
            if (c[_u][_v] == -1) return -1;
            if (c[_u][_v] == 0) continue;
            mask |= (1 << (c[_u][_v] - 1));
        }
    }
    return mask;
}
 
int cMask[20][20];
 
int px[N], py[N];
 
void solve() {
    memset(c, 0, sizeof(c));
    getline(cin, s[0]);
    for(int i = 0; i < 10; ++i) {
        cin >> s[i];
    }
    int k = 0;
    for(int i = 0; i < 10; ++i) for(int j = 0; j < 10; ++j) {
        if (s[i][j] == 'g') c[i][j] = -1;
        if (s[i][j] == 'e') {
            c[i][j] = k + 1;
            px[k] = i;
            py[k] = j;
            ++k;
        }
    }
 
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            cMask[i][j] = getMask(i, j);
 
//    for(int i = 0; i < 10; ++i) {
//        for(int j = 0; j < 10; ++j)
//            cout << c[i][j] << " ";
//        puts("");
//            }
 
 
    dp[0] = 0;
    rep(mask, 1, 1 << k) dp[mask] = inf;
    rep(mask, 0, 1 << k) {
        //dp[mask] = inf;
        rep(j, 0, k) if (!(mask & (1 << j))) {
            rep(u, -1, 2) rep(v, -1, 2) {
                int _u = px[j] + u;
                int _v = py[j] + v;
                int mm = cMask[_u][_v];
                if (mm == -1) continue;
 
                dp[mask | mm] = min(dp[mask | mm], dp[mask] + 1);
            }
        }
    }
 
    //cout << (1 << 9) - 1 << " " << getMask(3, 4) << "\n";
    int tMask = 0;
    for(int i = 0; i < 10; ++i) for(int j = 0; j < 10; ++j) {
        int tmp = getMask(i, j);
        if (tmp <= 0) continue;
        tMask |= tmp;
    }
    cout << __builtin_popcount(tMask) << " " << dp[tMask] << "\n";
 
}
 
 
int main() {
 
//    freopen("in.txt", "r", stdin);
 
 
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
