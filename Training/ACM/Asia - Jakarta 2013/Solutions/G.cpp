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
const int M = 101;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-7;
//const double PI = acos(-1);
const bool multipleTest = true;
 
 
priority_queue<ll> heap[M];
 
 
void solve() {
    for(int i = 0; i < M; ++i) {
        while (!heap[i].empty()) heap[i].pop();
    }
    puts("");
    int Q;
    cin >> Q;
    char s[5];
    while (Q-- > 0) {
        scanf("%s", s);
        ll t0;
        int s0, r;
        if (s[0] == 'P') {
            scanf("%lld%d%d", &t0, &s0, &r);
            heap[r].push(s0 - (ll)t0 * r);
//            cout << s0 - t0 * r << "\n";
//            exit(0);
        } else {
            scanf("%lld", &t0);
            ll mx = -linf;
            int r = 0;
            for(int i = M - 1; i >= 0; --i) {
                if (!heap[i].empty() && heap[i].top() + (ll) i * t0 > mx) {
 
                    mx = heap[i].top() + (ll) i * t0;
                    r = i;
                }
            }
            printf("%lld %d\n", mx, r);
            heap[r].pop();
        }
    }
 
}
 
 
int main() {
 
 
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
 
    for(int i = 0; i < Test; ++i) {
        printf("Case #%d:", i + 1);
        solve();
    }
 
    //#ifndef ONLINE_JUDGE
    //    cout<<"\n" << diff / CLOCKS_PER_SEC<<endl;
    //#endif
}
