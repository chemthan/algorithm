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
 
const int N = 100000 + 7;
const int M = 1000000;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
 
const bool multipleTest = true;
 
 
int n;
int ans = 0 ;
bool check[N];
int m;
 
 
vi list;
 
void handle(vi list) {
    if (list.size() <= 1) return;
    vi cur;
    for(int i = 0; i < list.size(); i += 2) {
        cur.push_back(list[i] | list[i + 1]);
        if ((list[i] ^ list[i + 1]) == 1) {
            ans ++;
        }
    }
    handle(cur);
}
 
void solve() {
    cin >> n >> m;
    int t = 1 << n;
    for(int i = 1; i <= t; ++i) check[i] = 1;
    for(int i = 0; i < m; ++i) {
        int u; scanf("%d", &u);
        check[u] = 0;
    }
    list.clear();
    for(int i = 1; i <= t; ++i)
        list.push_back(check[i]);
    ans = 0;
    handle(list);
    cout << ans << "\n";
 
}
 
 
int main() {
 
//        freopen("in.txt", "r", stdin);
 
 
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    for(int i = 0; i < Test; ++i) {
//        printf("Case #%d:", i + 1);
//        if (i > 0) puts("");
        solve();
//        puts("");
    }
 
    //#ifndef ONLINE_JUDGE
    //    cout<<"\n" << diff / CLOCKS_PER_SEC<<endl;
    //#endif
}
