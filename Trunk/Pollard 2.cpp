#include <bits/stdc++.h>
using namespace std;

//O(N^(1/4))
#define T unsigned long long
#define MAXNUMFACT 64
int nfact = 0;
T Fa[MAXNUMFACT];
T gcd(T a, T b) {
	T tmp;
	while (b != 0) {tmp = b; b = a % b; a = tmp;}
	return a;
}
T mulmod64(T a, T b, T p) {
	a %= p; b %= p;
	T r = 0;
	int block = 1;
	T base = 1LL << block;
	for (; b; b >>= block) {
		r = (r + a * (b & (base - 1))) % p;
		a = a * base % p;
	}
	return r;
}
T powmod64(T n, T k, T p) {
	if (!n) return 0;
	T r = 1;
	for (; k; k >>= 1) {
		if (k & 1) r = mulmod64(r, n, p);
		n = mulmod64(n, n, p);
	}
	return r;
}
T random64() {
	T n = 0;
	int l = rand() % (RAND_MAX - 2) + 2;
	int r = rand() % (RAND_MAX) + rand() % 2;
	n |= 1ULL * r; n <<= 32; n |= 1ULL * l;
	return n;
}
void decompose(T p, int* k, T* m) {
	int i = 0;
	while ((p & 1) == 0) {i++; p >>= 1;}
	*k = i; *m = p;
}
int witness(T a, T N) {
	T m;
	int k; decompose(N - 1, &k, &m);
	T B[k + 1];
	B[0] = powmod64(a, m, N);
	if (B[0] == 1) return 1;
	int i = 1;
	while (i <= k) {
		B[i] =  mulmod64(B[i - 1], B[i - 1], N);
		if (B[i] == 1) {
			if (B[i - 1] == N - 1) return 1;
			else return 0;
		}
		i++;
	}
	return 0;
}
int miller_rabin_testing(int acc, T N) {
	T a = 0;
	for (int i = 0; i <= acc; i++){
		a = random64() % (N - 2) + 2;
		if (gcd(a, N) != 1) return 0;
		else if (powmod64(a, N - 1, N) != 1) return 0;
		else if (witness(a, N) == 0) return 0;
	}
	return 1;
}

T sqrt(T N) {
	T X, A2, R;
	X = N, A2 = 1ULL << 62, R = 0;
	while (N < A2)  A2 >>= 2;
	while (A2 > 0) {
		if (X >= R + A2) {X -= R + A2; R = (R >> 1) + A2; A2 >>= 2;}
		else {A2 >>= 2; R >>= 1;}
	}
	return R;
}
T next_prng(T x, T N) {
	T xs = mulmod64(x, x, N);
	return xs + 1ULL;
}
T find_factor(T N) {
	T x = random64() % N;
	T y = x;
	T p = 1;
	do {
		x = next_prng(x, N);
		y = next_prng(next_prng(y, N), N);
		if (x > y) p = gcd(x - y, N);
		else p = gcd(y - x, N);
	}
	while (p == 1);
	return p;
}
void fast_native_fact(T N) {
	while (N % 2 == 0) {
		Fa[nfact++] = 2ULL;
		N >>= 1;
	}
	while (N % 3 == 0) {
		Fa[nfact++] = 3ULL;
		N /= 3;
	}
	if (N == 1) return;
	if (miller_rabin_testing(10, N) == 1) {
		Fa[nfact++] = N;
		return;
	}
	T Q = 5;
	int diff = 2;
	int sqrtN = sqrt(N);
	while (Q <= sqrtN) {
		if (N %Q == 0) {
			Fa[nfact++] = Q; N /= Q; sqrtN = sqrt(N);
			if (miller_rabin_testing(10, N) == 1) {
				Fa[nfact++] = N;
				return;
			}
		}
		else {
			Q = Q + (T) diff;
			diff = (diff & 2) + 2;
		}
	}
}
void pollard_rho_fact(T N) {
	if (N == 1ULL) return;
	else if (N < (1ULL << 10)) fast_native_fact(N);
	else if(miller_rabin_testing(10, N) == 1) Fa[nfact++] = N;
	else {
		T p = 0ULL;
		while (p == 0 || p == N) p = find_factor(N);
		pollard_rho_fact(p);
		pollard_rho_fact(N / p);
	}
}

int main() {
	srand(time(NULL));
	T n = random64();
	pollard_rho_fact(n);
	sort(Fa, Fa + nfact);
	T t = 1;
	for (int i = 0; i < nfact; i++) {
		cout << Fa[i] << " ";
		t *= Fa[i];
	}
	cout << "\n";
	if (n != t) {
		cout << "Wrong!\n";
	}
	else {
		cout << "Correct!\n";
	}
	return 0;
}
