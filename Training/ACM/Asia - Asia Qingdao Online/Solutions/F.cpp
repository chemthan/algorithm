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
int r[N];

int get(int u) {
    return r[u] < 0 ? u : r[u] = get(r[u]);
}

void uni(int u, int v) {
    if (r[u] > r[v]) swap(u, v);
    r[u] += r[v];
    r[v] = u;
}

//vii adj[N];
//bool state[N * 5];
//
//int res = 0;
//
//void DFS(int u, int st){
//    
//    while (adj[u].size() > 0){
//        int v = adj[u].back().fi;
//        int c = adj[u].back().se;
//        adj[u].pop_back();
//        if (state[c] == 1) continue;
//        state[c] = 1;
//        DFS(v, 1 - st);
//    }
//    //cout << u << " " << a[u] << "\n";
//    res ^= a[u];
//}

int cnt[N];


void solve() {
    
    int T;
    cin >> T;
    while (T-- > 0) {
        int n, m;
        cin >> n >> m;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            //adj[i].clear();
            r[i] = -1;
            cnt[i] = 0;
        }
        
        int tol = n;
        
        for(int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
//            adj[u].push_back(mk(v, i));
//            adj[v].push_back(mk(u, i));
//            state[i] = 0;
            cnt[u] ++;
            cnt[v] ++;
            
            if (get(u) != get(v)) {
                uni(get(u), get(v));
                tol--;
            }
        }
        
        if (tol > 1) {
            puts("Impossible");
            continue;
        }
        
        int sl1 = 0, sl2 = 0;
        for(int i = 1; i <= n; ++i) if (cnt[i] & 1) sl1++;
        else sl2++;
        
        if (sl1 == 0) {
            int ans = 0;
            for(int i = 1; i <= n; ++i) if ((cnt[i] >> 1) & 1) ans ^= a[i];
            int mx = 0;
            for(int i = 1; i <= n; ++i) {
                mx = max(mx, ans ^ a[i]);
            }
            printf("%d\n", mx);
            
        } else if (sl1 == 2) {
            int res = 0;
            for(int i = 1; i <= n; ++i) if (cnt[i] & 1) {
                int tmp = 1 + (cnt[i] - 1) / 2;
                if (tmp & 1) res ^= a[i];
            } else  if ((cnt[i] >> 1) & 1) res ^= a[i];
            printf("%d\n", res);
        }
        else {
            puts("Impossible");
        }
        
        
        
        
        
        
    }
}



int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    clock_t t1 = clock();
#endif
//    freopen("out.txt", "w", stdout);
    
    int Test = 1;
    if (multipleTest) {
        cin >> Test;
    }
    
    for(int i = 0; i < Test; ++i) {
//        printf("Case #%d: ", i + 1);
        solve();
    }
    
//#ifndef ONLINE_JUDGE
//    cout << "\n";
//    cout << std::setprecision(5);
//    cout << ((double)clock() - t1) / CLOCKS_PER_SEC << "\n";
//#endif
}
