#include <bits/stdc++.h>
using namespace std;

template<const int n>
struct BinaryMatrix {
    bitset<n> x[n];
    
    BinaryMatrix() {
        memset(x, 0, sizeof(x));
    }
    bitset<n>& operator [] (int r) {
        return x[r];
    }
    static BinaryMatrix unit() {
        BinaryMatrix res;
        for (int i = 0; i < n; i++) res[i][i] = 1;
        return res;
    }
    friend BinaryMatrix operator + (BinaryMatrix A, BinaryMatrix B) {
        BinaryMatrix res;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            res[i][j] = A[i][j] ^ B[i][j];
        }
        return res;
    }
    friend BinaryMatrix operator * (BinaryMatrix A, BinaryMatrix B) {
        BinaryMatrix<n> res, tmp;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            tmp[i][j] = B[j][i];
        }
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            res[i][j] = (A[i] & tmp[j]).any();
        }
        return res;
    }
    friend BinaryMatrix operator ^ (BinaryMatrix A, long long k) {
        if (k == 0) return unit();
        BinaryMatrix<n> res, tmp;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
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
        BinaryMatrix<n> res = A, tmp = A;
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
    BinaryMatrix<100> mat;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            mat[i][j] = rand() & 1;
        }
    }
    mat = mat ^ 123456;
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
