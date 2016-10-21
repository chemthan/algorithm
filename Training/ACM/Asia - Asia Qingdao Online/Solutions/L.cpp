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
#include <cfloat>
#include <iomanip>
#include <stack>
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
#define pii pair<int, int>


typedef complex<ld> cplex;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;

const int N = 100000 + 7;
const int M = 100 + 3;
const int inf = 1e9 + 7;
const long long linf = 1e18 + 7;
const double pi = acos(-1);
const double eps = 1e-6;
const bool multipleTest = false;

int a[N];
bitset<88> can[12];
set<ll> st;

void solve() {
    
    int T;
    cin >> T;
    while (T-- > 0) {
        int n, m;
        cin >> n;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            //cout
        }
        st.clear();
        can[0].reset();
        for(int u = 1; u <= n; ++u) {
            for(int v = u; v <= n; ++v) {
                for(int k = v; k <= n; ++k) {
                    
                    for(int j = 1; j <= 10; ++j)can[j].reset();
                    can[0].set(0);
                    
                    for(int j = 1; j <= n; ++j) {
                        if (j != u && j != v && j != k && a[j] <= 87) {
                            for(int t = 10; t > 0; --t)
                                can[t] |= (can[t - 1] << a[j]);
                        }
                    }
                    
                    
                    if (can[10][87]) {
                        ll mask = (1ll << u) | (1ll << v) | (1ll << k);
                        st.insert(mask);
                    }
                }
            }
        }
        cin >> m;
        while (m-- > 0) {
            int u, v, k; scanf("%d%d%d", &u, &v, &k);
            ll mask = (1ll << u) | (1ll << v) | (1ll << k);
            if (st.count(mask)) puts("Yes"); else puts("No");
        }
    }
        
    
}


void createTest() {
    freopen("in.txt", "w", stdout);
    cout << 5 << "\n";
    for(int t = 0; t < 5; ++t) {
        cout << 50 << "\n";
        for(int i = 1; i <= 50; ++i) {
            cout << rand() % 100000<< " ";
        }
        puts("");
        cout << 1 << "\n1 2 3\n";
    }
}



int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    clock_t t1 = clock();
#endif
//    createTest();
//    return 0;
//    freopen("out.txt", "w", stdout);
    
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
    
    for(int i = 0; i < Test; ++i) {
//        printf("Case #%d: ", i + 1);
        solve();
    }
    
#ifndef ONLINE_JUDGE
    cout << "\n";
    cout << std::setprecision(5);
    cout << ((double)clock() - t1) / CLOCKS_PER_SEC << "\n";
#endif
}
