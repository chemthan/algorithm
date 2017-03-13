#include <bits/stdc++.h>
using namespace std;

struct BinaryMatrix {
    static const int MAXN = 100;
    bitset<MAXN> x[MAXN];
    
    BinaryMatrix() {
        memset(x, 0, sizeof(x));
    }
    static BinaryMatrix unit() {
        BinaryMatrix res;
        for (int i = 0; i < MAXN; i++) res.x[i][i] = 1;
        return res;
    }
    BinaryMatrix operator + (BinaryMatrix A) {
        BinaryMatrix res;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res.x[i][j] = x[i][j] ^ A.x[i][j];
        }
        return res;
    }
    BinaryMatrix operator * (BinaryMatrix A) {
        BinaryMatrix res, tmp;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            tmp.x[i][j] = A.x[j][i];
        }
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res.x[i][j] = (x[i] & tmp.x[j]).any();
        }
        return res;
    }
    BinaryMatrix operator ^ (long long k) {
        if (k == 0) return unit();
        BinaryMatrix res, tmp;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res.x[i][j] = tmp.x[i][j] = x[i][j];
        }
        k--;
        while (k) {
            if (k & 1) res = res * tmp;
            tmp = tmp * tmp;
            k >>= 1;
        }
        return res;
    }
    //Caculate geometric series: A^0 + A^1 + ... + A^k
    friend BinaryMatrix geometricseries(BinaryMatrix A, long long k) {
        if (k == 0) return unit();
        if (k == 1) return A + unit();
        vector<int> bit;
        while (k) {
            bit.push_back(k & 1);
            k >>= 1;
        }
        BinaryMatrix res = A, tmp = A;
        for (int i = bit.size() - 2; i >= 0; i--) {
            res = res + (res * tmp);
            tmp = tmp * tmp;
            if (bit[i] & 1) {
                tmp = tmp * A;
                res = res + tmp;
            }
        }
        res = res + unit();
        return res;
    }
};

int main() {
  return 0;
}
