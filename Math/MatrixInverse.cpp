#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N^3)
*/
#define EPS 1e-9
typedef double T;
typedef vector<T> ROW;
typedef vector<ROW> MATRIX;

inline int sign(T x) {return x < -EPS ? -1 : x > +EPS;}
MATRIX MatrixInverse(MATRIX a) {
    int i, j, k, n = a.size();
    MATRIX res;
    res.resize(n);
    for (i = 0; i < n; i++) {
        res[i].resize(n);
        for (j = 0; j < n; j++) res[i][j] = 0;
        res[i][i] = 1;
    }
    for (i = 0; i < n; i++) {
        if (!sign(a[i][i])) {
            for (j = i + 1; j < n; j++) {
                if (sign(a[j][i])) {
                    for (k = 0; k < n; k++) {
                        a[i][k] += a[j][k];
                        res[i][k] += res[j][k];
                    }
                    break;
                }
            }
            if (j == n) {
                res.clear();
                return res;
            }
        }
        T tmp = a[i][i];
        for (k = 0; k < n; k++) {
            a[i][k] /= tmp;
            res[i][k] /= tmp;
        }
        for (j = 0; j < n; j++) {
            if (j == i) continue;
            tmp = a[j][i];
            for (k = 0; k < n; k++) {
                a[j][k] -= a[i][k] * tmp;
                res[j][k] -= res[i][k] * tmp;
            }
        }
    }
    return res;
}

int main() {
    srand(time(NULL));
    int n = 100;
    MATRIX a(n, ROW(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand();
        }
    }
    MATRIX ia = MatrixInverse(a);
    MATRIX b(n, ROW(n, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                b[i][j] += a[i][k] * ia[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (sign(b[i][i] - 1)) {
            cout << "Wrong!\n";
            return 0;
        }
        for (int j = 0; j < n; j++) {
            if (i != j && sign(b[i][j])) {
                cout << "Wrong!\n";
                return 0;
            }
        }
    }
    cout << "Correct!\n";
    return 0;
}
