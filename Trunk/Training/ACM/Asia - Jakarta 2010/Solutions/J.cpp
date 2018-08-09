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
const int M = 12;
const int inf = 1e9 + 7;
const long long linf = (ll) inf * inf + 7;
const double pi = acos(-1);
const double eps = 1e-20;
const bool multipleTest = true;
 
 
char s[M][N][N];
int dp[M][N][N];
int cost[M][N][N];
int L, H, W;
int n, m;
 
iii q[100007];
int top, bot;
 
int x[4] = {0, 0, -1, 1};
int y[4] = {-1, 1, 0, 0};
 
bool valid(iii u) {
    return (u.first.first >= 0 && u.first.first < L
        && u.first.second >= 0 && u.first.second < H
            && u.second >= 0 && u.second < W
            && s[u.first.first][u.first.se][u.second] != 'X');
 
}
 
char get(iii u) {
    return s[u.fi.fi][u.fi.se][u.se];
}
 
vii list;
 
int F[N * N];
 
void solve() {
    cin >> L >> H >> W >> n >> m;
    for(int i = 0; i < L; ++i) {
        for(int j = 0; j < H; ++j) {
            scanf("%s", s[i][j]);
        }
    }
 
    for(int i = 0; i < L; ++i) {
        for(int u = 0; u < H; ++u) {
            for(int v = 0; v < W; ++v) {
                cost[i][u][v] = 0;
                dp[i][u][v] = inf;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        int r, u, v, c;
        scanf("%d%d%d%d", &r, &u, &v, &c);
        --r; --u; --v;
        cost[r][u][v] = c;
    }
 
    iii r;
    for(int i = 0; i < H; ++i)
        for(int j = 0; j < W; ++j) {
            if (s[0][i][j] == 'S') {
                r = mk(mk(0, i), j);
            }
        }
 
 
 
    dp[r.first.first][r.first.second][r.second] = 0;
 
    top = bot = 0;
    q[bot ++] = r;
    while (top < bot) {
        iii u = q[top++];
 
        for(int i = 0; i < 4; ++i) {
            int x1 = u.first.second + x[i];
            int y1 = u.second + y[i];
            iii nxt = mk(mk(u.first.first, x1), y1);
            if (valid(nxt) && dp[nxt.first.first][nxt.first.se][nxt.se] == inf) {
                dp[nxt.fi.fi][nxt.fi.se][nxt.se] = dp[u.fi.fi][u.fi.se][u.se] + 1;
                q[bot++] = nxt;
            }
        }
 
        for(int t = -1; t < 2; ++t) {
            if (t == -1 && get(u) != 'D') continue;
            if (t == 1 && get(u) != 'U') continue;
            int z1 = u.fi.fi + t;
            iii nxt = mk(mk(z1, u.fi.se), u.se);
            if (valid(nxt) && dp[nxt.first.first][nxt.first.se][nxt.se] == inf) {
                dp[nxt.fi.fi][nxt.fi.se][nxt.se] = dp[u.fi.fi][u.fi.se][u.se] + 1;
                q[bot++] = nxt;
            }
        }
    }
 
 
    list.clear();
    for(int z = 0; z < L; ++z) {
        for (int u = 0; u < H; ++u) {
            for(int v = 0; v < W; ++v) {
                //printf("%d ", dp[z][u][v]);
                if (cost[z][u][v] != 0 && dp[z][u][v] < inf) {
                    list.push_back(mk(cost[z][u][v], dp[z][u][v] * 3));
                    //cout << cost[z][u][v] << " " << dp[z][u][v] * 3 << "\n";
                }
            }
            //puts("");
        }
    }
 
    for(int i = 0; i <= m; ++i) F[i] = -inf;
    F[0] = 0;
 
    for(int i = 0; i < list.size(); ++i) {
        for(int j = m; j >= list[i].second; --j)
            F[j] = max(F[j], F[j - list[i].second] + list[i].first);
    }
 
    int ans = 0;
 
    for(int i = m; i >= 0; --i) ans = max(ans, F[i]);
    cout << ans << "\n";
 
 
 
}
 
int main() {
 
    //    createTest();
    //    return 0;
 
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//    auto t1 = clock();
//#endif
 
//    init();
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
