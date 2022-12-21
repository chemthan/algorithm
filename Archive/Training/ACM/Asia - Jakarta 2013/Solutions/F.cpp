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
const int M = N * 10;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
//const double PI = acos(-1);
const bool multipleTest = true;
 
const int mod[2] = {inf, 100000000 + 7};
const int gen[2] = {(rand() % 92473247) + 1, (rand() % 92473247) + 1};
 
ll f[2][N];
 
void init() {
    f[0][0] = f[1][0] = 1;
    for(int i = 1; i < N; ++i) {
        for(int t = 0; t < 2; ++t)
            f[t][i] = (ll)f[t][i - 1] * gen[t] % mod[t];
    }
}
 
ii val[N];
 
ii getNext(ii cur, ii nxt, int len) {
    int fir = (cur.first * f[0][len] + nxt.first) % mod[0];
    int sec = (cur.second * f[1][len] + nxt.second) % mod[1];
    return mk(fir, sec);
}
 
ii getVal(int u, int v) {
    ++u; ++v;
    ll fir = (val[v].first - val[u - 1].first * f[0][v - u + 1]) % mod[0];
    if (fir < 0) fir += mod[0];
    ll sec = (val[v].second - val[u - 1].second * f[1][v - u + 1]) % mod[1];
    if (sec < 0) sec += mod[1];
    return mk(fir, sec);
}
 
void solve() {
    string s;
    cin >> s;
 
    int n = sz(s);
    val[0] = mk(0, 0);
    for(int i = 1; i <= n; ++i) {
        val[i] = getNext(val[i - 1], mk(s[i - 1], s[i - 1]), 1);
    }
 
    int h = n / 2;
    int r = n - 1;
 
    int ans = 0;
    int i = 0;
 
 
    while(i < h) {
        int len = 0;
        while (r - len >= n - h && getVal(i, i + len) != getVal(r - len, r)) {
            ++len;
        }
        if (r - len >= n - h) {
            ans += 2;
            ++len;
            i += len;
            r -= len;
        } else break;
    }
    //cout << i << " " << r << "\n";
    if (i <= r) {
        ans ++;
    }
    cout << ans << "\n";
}
 
 
int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
        //t1=clock();
    #endif
 
    init();
 
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
