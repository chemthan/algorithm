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
 
const int N = 200000 + 7;
const int M = 23000;
const int inf = 1e9 + 7;
const long long linf = (ll) inf * inf + 7;
const double pi = acos(-1);
const double eps = 1e-20;
const bool multipleTest = true;
 
int get(char s[]) {
    int c = 0;
    int p = 1;
    if (s[p] == 'D') c = 0;
    if (s[p] == 'C') c = 1;
    if (s[p] == 'H') c = 2;
    if (s[p] == 'S') c = 3;
 
        if (s[0] <= '9') return (s[0] - '2') * 4 + c;
        else {
            if (s[0] == 'T') return 8 * 4 + c;
            else if (s[0] == 'J') return 9 * 4 +  c;
            else if (s[0] == 'Q') return 10 * 4 + c;
            else if (s[0] == 'K') return 11 * 4 + c;
            else return 12 * 4 + c;
        }
 
}
 
vi list1, list2;
 
bool check[N];
 
void solve() {
    for(int i = 0; i < 52; ++i) check[i] = 0;
    char s[5];
    for(int i = 0; i < 26; ++i) {
        scanf("%s", s);
        check[get(s)] = 1;
//        cout << get(s) << " ";
    }
//    cout << "\n";
//    exit(0);
    list1.clear();
    list2.clear();
 
    for(int i = 0; i < 52; ++i) if (check[i]) list1.push_back(i);
    else list2.push_back(i);
 
    int j = 0;
    int ans = 0;
    for(int i = 0; i < list1.size(); ++i) {
        if (j < list2.size() && list2[j] < list1[i]) {
//            cout << elist2[j] << " " << list1[i] << "\n";
            ++j;
            ++ans;
        }
    }
    cout << ans << "\n";
}
 
int main() {
 
    //    createTest();
    //    return 0;
 
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//    auto t1 = clock();
//#endif
 
 
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
