#include <bits/stdc++.h>
using namespace std;

const long long oo = (long long) 1e18;
struct Triple {
    long long x, y, d;
    Triple() {x = y = d = 0;}
    Triple(long long x, long long y, long long d) : x(x), y(y), d(d) {}
};
Triple euclid(long long a, long long b) {
    if (b == 0) return Triple(1, 0, a);
    Triple r = euclid(b, a % b);
    return Triple(r.y, r.x - a / b * r.y, r.d);
}
int sign(long long a) {
    if (a == 0) return 0;
    return a < 0 ? -1 : +1;
}
long long up(long long a, long long b) {
    if (a % b == 0) return a / b;
    if (sign(a) * sign(b) < 0) return a / b;
    return a / b + 1;
}
long long down(long long a, long long b) {
    if (a % b == 0) return a / b;
    if (sign(a) * sign(b) < 0) return a / b - 1;
    return a / b;
}
long long howmany(long long A, long long B, long long C, long long X1, long long Y1, long long X2, long long Y2) {
    if (X1 > X2 || Y1 > Y2) return 0;
    if (A < 0) {A = -A; long long X = X1; X1 = -X2; X2 = -X;}
    if (B < 0) {B = -B; long long Y = Y1; Y1 = -Y2; Y2 = -Y;}
    C = -C;
    if (A == 0 && B == 0) {
        return C == 0 ? (X2 - X1 + 1) * (Y2 - Y1 + 1) : 0;
    }
    if (A == 0) {
        if (C % B != 0) return 0;
        long long Y = C / B;
        return Y1 <= Y && Y <= Y2 ? X2 - X1 + 1 : 0;
    }
    if (B == 0) {
        if (C % A != 0) return 0;
        long long X = C / A;
        return X1 <= X && X <= X2 ? Y2 - Y1 + 1 : 0;
    }
    Triple r = euclid(A, B);
    if (C % r.d != 0) return 0;
    long long alpha = A / r.d, beta = B / r.d, gama = C / r.d;
    long long X0 = (r.x % beta + beta) * (gama % beta + beta) % beta;
    long long Y0 = (gama - alpha * X0) / beta;
    long long K1 = -oo, K2 = +oo;
    if (alpha > 0) {
        K1 = max(K1, up(Y0 - Y2, alpha));
        K2 = min(K2, down(Y0 - Y1, alpha));
    }
    else {
        K1 = max(K1, up(Y0 - Y1, alpha));
        K2 = min(K2, down(Y0 - Y2, alpha));
    }
    if (beta > 0) {
        K1 = max(K1, up(X1 - X0, beta));
        K2 = min(K2, down(X2 - X0, beta));
    }
    else {
        K1 = max(K1, up(X2 - X0, beta));
        K2 = min(K2, down(X1 - X0, beta));
    }
    return K1 <= K2 ? K2 - K1 + 1 : 0;
}

int main() {
    return 0;
}
