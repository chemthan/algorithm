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



vii adj[N];
int n, m;

int maxDown[N], maxUp[N], longestUp[N], longestDown[N];
multiset<int> st;


int cnt = 0;


void dfs(int u, int r) {
    maxUp[u] = longestUp[u] = 0;
    
    for(int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j].first;
        if (v != r) {
            dfs(v, u);
            maxUp[u] = max(maxUp[u], maxUp[v]);
        }
    }
    
    st.clear();
    
    for(int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j].first;
        int c = adj[u][j].second;
        if (v != r) {
            st.insert(longestUp[v] + c);
            if (st.size() > 2) st.erase(st.begin());
        }
    }
    
    
    if (st.empty()) return;
    
    longestUp[u] = *st.rbegin();
    maxUp[u] = max(maxUp[u], longestUp[u]);
    
    
    if (st.size() >= 2) {
        __typeof(st.rbegin()) it = st.rbegin();
        int tol = *it; ++it;
        tol += *it;
        maxUp[u] = max(maxUp[u], tol);
    }
    
}


ll ans = 0;

int mLeft[N], mRight[N];

void calc(int u, int r) {
    st.clear();
    st.insert(longestDown[u]);
    
    for(int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j].first;
        int c = adj[u][j].second;
        mLeft[j] = 0;
        if (j > 0) mLeft[j] = mLeft[j - 1];
        if (v != r) {
            st.insert(longestUp[v] + c);
            if (st.size() > 3) st.erase(st.begin());
            mLeft[j] = max(mLeft[j], maxUp[v]);
        }
    }
    
    for(int j = sz(adj[u]) - 1; j >= 0; --j) {
        int v = adj[u][j].first;
        mRight[j] = 0;
        if (j + 1 < adj[u].size()) mRight[j] = mRight[j + 1];
        if (v != r) {
            mRight[j] = max(mRight[j], maxUp[v]);
        }
    }
    
    for(int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j].first;
        int c = adj[u][j].second;
        
        if (v != r) {
            bool rm1 = false;
            ft(st) it = st.find(longestUp[v] + c);
            if (it != st.end()) {
                st.erase(it);
                rm1 = true;
            }
            
            int tmp = maxDown[u];
            if (j > 0) tmp = max(tmp, mLeft[j - 1]);
            if (j + 1 < adj[u].size()) tmp = max(tmp, mRight[j + 1]);
            if (st.size() > 1) {
                __typeof(st.rbegin()) it = st.rbegin();
                int cur = *it; it++;
                cur += *it;
                tmp = max(tmp, cur);
            }
            
//            if (v == 22) cout <<"shit " << v << " " << tmp << " " << st.size() << "\n";
            
            ans += max(maxUp[v], tmp);
            
            longestDown[v] = *st.rbegin() + c;
            
            maxDown[v] = max(tmp, longestDown[v]);
            
            if (rm1) st.insert(longestUp[v] + c);
            
        }
    }
    
    for(int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j].first;
        if (v != r)
            calc(v, u);
    }
    
}





void solve() {
    
    int T;
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        
        for(int i = 1; i <= n; ++i) adj[i].clear();
        
        for(int i = 1; i < n; ++i) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            adj[u].push_back(mk(v, c));
            adj[v].push_back(mk(u, c));
        }
        
        ans = 0;
        dfs(1, -1);
        
        calc(1, -1);
        

        cout << ans << "\n";
        
    }
}

void createTest() {
    freopen("in.txt", "w", stdout);
    cout << 5 << "\n";
    for(int t = 0; t < 5; ++t) {
    n = 100000;
    cout << n << "\n";
    for(int i = 1; i < n; ++i) {
        cout << (rand() % i) + 1 << " " << i + 1 << " " << rand() % 1000 << "\n";
    }
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
