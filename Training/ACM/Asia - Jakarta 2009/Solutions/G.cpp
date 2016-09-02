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
 
const int N = 100 + 7;
const int M = 5000;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-6;
const bool multipleTest = false;
 
const int mod[2] = {inf, 100000000 + 7};
const int gen[2] = {(rand() % 92473247) + 1, (rand() % 92473247) + 1};
 
ll f[2][N];
 
char mapping[60];
 
void init() {
    f[0][0] = f[1][0] = 1;
    for(int i = 1; i < N; ++i) {
        for(int t = 0; t < 2; ++t)
            f[t][i] = (ll)f[t][i - 1] * gen[t] % mod[t];
    }
    for(int i = 0; i < 26; ++i) {
        mapping[i] = 'A' + i;
        mapping[i + 26] = 'a' + i;
    }
}
 
ii val[N];
 
ii getNext(ii cur, ii nxt, int len) {
    int fir = (cur.first * f[0][len] + nxt.first) % mod[0];
    if (fir < 0) fir += mod[0];
    int sec = (cur.second * f[1][len] + nxt.second) % mod[1];
    if (sec < 0) sec += mod[1];
    return mk(fir, sec);
}
 
string s[N];
int n, m;
 
ii handle(vii list) {
    sort(list.begin(), list.end());
    ii ans = mk(0, 0);
    for(int i = 1; i < list.size(); ++i) {
        ans = getNext(ans, mk(list[i].first - list[0].first, list[i].second - list[0].second), 1);
    }
    return ans;
}
 
ii gt[600][8];
int check[N][N];
 
bool valid(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}
 
 
int x[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int y[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
 
vii list;
 
int k = 0;
 
void dfs(int i, int j) {
    list.push_back(mk(i, j));
    check[i][j] = k;
    for(int t = 0; t < 8; ++t) {
        int u = i + x[t];
        int v = j + y[t];
        if (valid(u, v) && check[u][v] == 0 && s[u][v] == '1') {
            dfs(u, v);
        }
    }
 
}
 
int stack[N];
int color[N * N];
int tolAns = 0;
set<ii> all;
 
void solve() {
    int cs = 0;
    while (cin >> n >> m) {
        if (!n) break;
        for(int i = 0; i < n; ++i) cin >> s[i];
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) check[i][j] = 0;
 
        k = 0;
        tolAns = 0;
 
        for(int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (s[i][j] == '1' && !check[i][j]) {
                    ++k;
                    list.clear();
                    dfs(i, j);
                    int cur = 0;
                    int _n = n, _m = m;
                    for(; cur < 4; ++cur) {
                        gt[k][cur] = handle(list);
                        for(int i = 0; i < list.size(); ++i) {
                            ii tmp = mk(list[i].second, _n - 1 - list[i].first);
                            list[i] = tmp;
                        }
                        swap(_n, _m);
                    }
 
                    for(int i = 0; i < list.size(); ++i) {
                        list[i] = mk(list[i].first, m - 1 - list[i].second);
                    }
 
                    for(; cur < 8; ++cur) {
                        gt[k][cur] = handle(list);
                        for(int i = 0; i < list.size(); ++i) {
                            ii tmp = mk(list[i].second, _n - 1 - list[i].first);
                            list[i] = tmp;
                        }
                        swap(_n, _m);
                    }
                    all.clear();
                    for(int t = 0; t < 8; ++t) {
                        all.insert(gt[k][t]);
                    }
 
                    int found = -1;
                    for(int t = 0; t < tolAns && found == -1; ++t) {
                        int cnt = 0;
                        for(int u = 0; u < 8; ++u) if (!all.count(gt[stack[t]][u])) break;
                        else ++cnt;
                        if (cnt == 8) {
                            found = t;
                            break;
                        }
 
                    }
                    if (found == -1) {
                        stack[tolAns++] = k;
                        found = tolAns - 1;
                    }
                    color[k] = found;
                }
            }
        }
        if (cs > 0) puts("");
        ++cs;
        cout << tolAns << "\n";
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if (s[i][j] == '0') printf("0");
                else printf("%c", mapping[color[check[i][j]]]);
                //else printf("%d", check[i][j]);
            }
            puts("");
        }
//        puts("");
    }
 
}
 
 
int main() {
 
//    freopen("in.txt", "r", stdin);
 
 
    init();
 
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    //cout << p[5] << "\n";
    for(int i = 0; i < Test; ++i) {
//        printf("Test Case #%d:\n", i + 1);
        //        if (i > 0) puts("");
        solve();
        //        puts("");
    }
 
 
    //#ifndef ONLINE_JUDGE
    //    cout<<"\n" << diff / CLOCKS_PER_SEC<<endl;
    //#endif
}
