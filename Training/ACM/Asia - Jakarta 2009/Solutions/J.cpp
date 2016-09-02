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
const int M = 5000;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
const bool multipleTest = true;
 
 
int cnt[M];
 
void printTime(int u) {
    int h = u / 60, m = u % 60;
    if (h < 10) cout << "0" << h;
    else cout << h;
    cout << ":";
    if (m < 10) cout << "0" << m;
    else cout << m;
}
 
void solve() {
    memset(cnt, 0, sizeof(cnt));
    int q;
    cin >> q;
    while (q-- > 0) {
        int u, v;
        scanf("%d:%d", &u, &v);
        u = u * 60 + v;
        cnt[u] ++;
 
        scanf("%d:%d", &u, &v);
        u = u * 60 + v;
        cnt[u + 1] --;
    }
    for(int i = 1; i < M; ++i) cnt[i] += cnt[i - 1];
    int mx = 0;
    for(int i = 0; i < M; ++i) mx = max(mx, cnt[i]);
    int fir = 0;
    for(fir = 0; cnt[fir] < mx; ++fir);
    printTime(fir);
    for(; cnt[fir + 1] == mx; ++fir);
    printf(" ");
    printTime(fir);
    puts("");
 
}
 
 
int main() {
 
        //freopen("in.txt", "r", stdin);
 
 
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
