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
 
const int N = 100000 + 7;
const int M = 23000;
const int inf = 1e9 + 7;
const long long linf = (ll) inf * inf + 7;
const double pi = acos(-1);
const double eps = 1e-20;
const bool multipleTest = true;
 
 
int n, k;
 
vi win[N];
int p[N];
int a[N];
 
 
void calc(vi list) {
 
    if (list.size() == 1) {
        printf("%d\n", list[0] + 1);
        for(int i = 0; i < win[list[0]].size(); ++i) {
            printf("%d", win[list[0]][i] + 1);
            if (i + 1 < win[list[0]].size()) printf(" ");
            else printf("\n");
        }
//        puts("");
        return;
    }
 
    vi nxtList;
    for(int i = 0; i < list.size(); i += 2) {
        int winner = 0, loser = 0;
        if (p[list[i]] >= p[list[i + 1]]) {
            winner = list[i];
            loser = list[i + 1];
        } else {
            winner = list[i + 1];
            loser = list[i];
        }
        win[loser].clear();
        win[winner].push_back(loser);
        p[winner] = min(a[winner], p[winner] - p[loser] + k);
        nxtList.push_back(winner);
    }
    list.clear();
    calc(nxtList);
}
 
vi list;
 
void solve() {
    cin >> n >> k;
 
    list.clear();
    for(int i = 0, m = 1 << n; i < m; ++i) {
        scanf("%d", p + i);
        a[i] = p[i];
        list.push_back(i);
        win[i].clear();
    }
//    return;
    calc(list);
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
