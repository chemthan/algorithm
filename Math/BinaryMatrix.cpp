#include <bits/stdc++.h>
using namespace std;

struct BinaryMatrix {
    static const int MAXN = 100;
    bitset<MAXN> x[MAXN];
    
    BinaryMatrix() {
        memset(x, 0, sizeof(x));
    }
    bitset<MAXN>& operator [] (int r) {
        return x[r];
    }
    static BinaryMatrix unit() {
        BinaryMatrix res;
        for (int i = 0; i < MAXN; i++) res[i][i] = 1;
        return res;
    }
    friend BinaryMatrix operator + (BinaryMatrix A, BinaryMatrix B) {
        BinaryMatrix res;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res[i][j] = A[i][j] ^ B[i][j];
        }
        return res;
    }
    friend BinaryMatrix operator * (BinaryMatrix A, BinaryMatrix B) {
        BinaryMatrix res, tmp;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            tmp[i][j] = B[j][i];
        }
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res[i][j] = (A[i] & tmp[j]).any();
        }
        return res;
    }
    friend BinaryMatrix operator ^ (BinaryMatrix A, long long k) {
        if (k == 0) return unit();
        BinaryMatrix res, tmp;
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) {
            res[i][j] = tmp[i][j] = A[i][j];
        }
        k--;
        while (k) {
            if (k & 1) res = res * tmp;
            tmp = tmp * tmp;
            k >>= 1;
        }
        return res;
    }
    //Calculate geometric series: A^0 + A^1 + ... + A^k
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
