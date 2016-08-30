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
 
const int N = 5000 + 7;
const int M = 20;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
//const double PI = acos(-1);
const bool multipleTest = true;
 
int sl[N];
int a[N][N];
int n, m;
 
int x[4] = {-1, 1, 0, 0};
int y[4] = {0, 0, -1, 1};
ii qu[N];
int top, bot;
ll ans = 0;
ll f[N][N];
int deg[N][N];
 
bool valid(int u, int v) {
    return u >= 0 && v >= 0 && u < n && v < m;
}
 
void BFS() {
 
    while (top < bot) {
        ii u = qu[top++];
        bool ok = true;
        for(int i = 0; i < 4; ++i) {
            int _x = u.first + x[i];
            int _y = u.second + y[i];
            if (valid(_x, _y) && a[_x][_y] < a[u.first][u.second]) {
                ok = false;
                f[_x][_y] += f[u.first][u.second];
                --deg[_x][_y];
                if (!deg[_x][_y])
                    qu[bot++] = mk(_x, _y);
 
            }
        }
        if (ok) {
            ans += f[u.first][u.second];
        }
    }
}
 
void solve() {
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            scanf("%d", &a[i][j]);
            deg[i][j] = 0;
            f[i][j] = 0;
        }
    ans = 0;
    top = bot = 0;
 
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int t = 0; t < 4; ++t) {
                int _x = i + x[t];
                int _y = j + y[t];
                if (valid(_x, _y) && a[_x][_y] > a[i][j]) {
                    deg[i][j] ++;
                }
            }
            if (!deg[i][j]) {
                qu[bot++] = mk(i, j);
                f[i][j] = 1;
            }
        }
    }
    BFS();
    cout << ans << "\n";
 
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
