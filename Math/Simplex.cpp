#include <bits/stdc++.h>
using namespace std;

/*
 * This is a simplex solver. Given m x n matrix A, m-vector b, n-vector c,
 * finds n-vector x such that Ax <= b (component-wise)
 * maximizing <c, x>
 * where <x, y> is the dot product of x and y.
 */
template<typename num_t>
struct LPsolver {
    const num_t eps = 1e-9;

    inline int sign(num_t x) {return x < -eps ? -1 : +eps < x;}
    inline int sign(num_t x, num_t y) {return sign(x - y);}
    int m, n;
    vector<int> B, N;
    vector<vector<double>> D;
    LPsolver(const vector<vector<double>> &A, const vector<num_t> &b, const vector<num_t> &c) : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<num_t>(n + 2)) {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }
    void pivot(int r, int s) {
        for (int i = 0; i < m + 2; i++) if (i != r) {
            for (int j = 0; j < n + 2; j++) if (j != s) {
                D[i][j] -= D[r][j] * D[i][s] / D[r][s];
            }
        }
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] /= D[r][s];
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] /= -D[r][s];
        D[r][s] = 1.0 / D[r][s];
        swap(B[r], N[s]);
    }
    int simple(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (1) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
            }
            if (sign(D[x][s]) >= 0) return 1;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (sign(D[i][s]) <= 0) continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] || D[i][n + 1] / D[i][s] == D[r][n + 1] / D[r][s] && B[i] < B[r]) r = i;
            }
            if (r == -1) return 0;
            pivot(r, s);
        }
    }
    num_t solve(vector<num_t>& x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (sign(D[r][n + 1]) < 0) {
            pivot(r, n);
            if (!simple(1) || sign(D[m + 1][n + 1]) < 0) return -numeric_limits<num_t>::infinity();
            for (int i = 0; i < m; i++) if (B[i] == -1) {
                int s = -1;
                for (int j = 0; j <= n; j++) {
                    if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
                }
                pivot(i, s);
            }
        }
        if (!simple(2)) return numeric_limits<num_t>::infinity();
        x = vector<num_t>(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};

int main() {
    int m = 4, n = 3;
    double _A[m][n] = {
        {6, -1, 0},
        {-1, -5, 0},
        {1, 5, 1},
        {-1, -5, -1}
    };
    double _b[m] = {10, -4, 5, -3};
    double _c[n] = {1, -1, 0};
    vector<vector<double>> A(m);
    vector<double> b(_b, _b + m);
    vector<double> c(_c, _c + n);
    for (int i = 0; i < m; i++) A[i] = vector<double>(_A[i], _A[i] + n);
    LPsolver<double> solver(A, b, c);
    vector<double> x;
    double value = solver.solve(x);
    cout << "Value: " << value << "\n";
    cout << "Solution: ";
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << " \n"[i == x.size() - 1];
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
