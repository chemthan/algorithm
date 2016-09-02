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
char name[N][50];
int low[N], high[N];
 
void solve() {
    cin >> n;
    for(int i = 0; i < n; ++i) {
        scanf("%s %d %d", name[i], &low[i], &high[i]);
    }
    int Q;
    cin >> Q;
    while (Q-- > 0) {
        int u ;
        scanf("%d", &u);
        int cnt = 0, index = -1;
        for(int i = 0; i < n; ++i) {
            if (low[i] <= u && u <= high[i]) {
                index = i;
                ++cnt;
                if (cnt == 2) break;
            }
        }
        if (cnt == 1) printf("%s\n", name[index]);
        else puts("UNDETERMINED");
    }
 
}
 
 
int main() {
 
//        freopen("in.txt", "r", stdin);
 
 
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    for(int i = 0; i < Test; ++i) {
//        printf("Case #%d:", i + 1);
        if (i > 0) puts("");
        solve();
//        puts("");
    }
 
    //#ifndef ONLINE_JUDGE
    //    cout<<"\n" << diff / CLOCKS_PER_SEC<<endl;
    //#endif
}
