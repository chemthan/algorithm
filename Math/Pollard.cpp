#include <bits/stdc++.h>
using namespace std;

//Pollard Rho Algorithm
//N^(1/4)
#define MAXNUMFACT 64
int nfact = 0;
unsigned long long Fa[MAXNUMFACT];
unsigned long long gcd(unsigned long long a, unsigned long long b) {
	unsigned long long tmp;
	while (b != 0) {tmp = b; b = a % b; a = tmp;}
	return a;
}
unsigned long long mod_mul(unsigned long long a, unsigned long long b, unsigned long long p) {
	if (b == 0) return 0;
	if (b == 1) return a % p;
	unsigned long long x = mod_mul(a, b >> 1, p);
	if ((b & 1) == 0) return (x << 1) % p;
	else return (((x << 1) % p) + a) % p;
}
unsigned long long mod_power(unsigned long long a, unsigned long long b, unsigned long long p) {
	if (a == 0) return 0;
	if (b == 0) return 1 % p;
	if (b == 1) return a % p;
	unsigned long long x = mod_power(a, b / 2, p);
	if ((b & 1) == 0) return mod_mul(x, x, p);
	else return (mod_mul(mod_mul(x, x, p), a, p));
}
unsigned long long random64() {
	unsigned long long n = 0;
	int l = rand() % (RAND_MAX - 2) + 2;
	int r = rand() % (RAND_MAX) + rand() % 2;
	n |= 1ULL * r; n <<= 32; n |= 1ULL * l;
	return n;
}
void decompose(unsigned long long p, int* k, unsigned long long* m) {
	int i = 0;
	while ((p & 1) == 0) {i++; p >>= 1;}
	*k = i; *m = p;
}
int witness(unsigned long long a, unsigned long long N) {
	unsigned long long m;
	int k; decompose(N - 1, &k, &m);
	unsigned long long B[k + 1];
	B[0] = mod_power(a, m, N);
	if (B[0] == 1) return 1;
	int i = 1;
	while (i <= k) {
		B[i] =  mod_mul(B[i - 1], B[i - 1], N);
		if (B[i] == 1) {
			if (B[i - 1] == N - 1) return 1;
			else return 0;
		}
		i++;
	}
	return 0;
}
int miller_rabin_testing(int acc, unsigned long long N) {
	unsigned long long a = 0;
	for (int i = 0; i <= acc; i++){
		a = random64() % (N - 2) + 2;
		if (gcd(a, N) != 1) return 0;
		else if (mod_power(a, N - 1, N) != 1) return 0;
		else if (witness(a, N) == 0) return 0;
	}
	return 1;
}

unsigned long long sqrt(unsigned long long N) {
	unsigned long long X, A2, R;
	X = N, A2 = 1ULL << 62, R = 0;
	while (N < A2)  A2 >>= 2;
	while (A2 > 0) {
		if (X >= R + A2) {X -= R + A2; R = (R >> 1) + A2; A2 >>= 2;}
		else {A2 >>= 2; R >>= 1;}
	}
	return R;
}
unsigned long long next_prng(unsigned long long x, unsigned long long N) {
	unsigned long long xs = mod_mul(x, x, N);
	return xs + 1ULL;
}
unsigned long long find_factor(unsigned long long N) {
	unsigned long long x = random64() % N;
	unsigned long long y = x;
	unsigned long long p = 1;
	do {
		x = next_prng(x, N);
		y = next_prng(next_prng(y, N), N);
		if (x > y) p = gcd(x - y, N);
		else p = gcd(y - x, N);
	}
	while (p == 1);
	return p;
}
void fast_native_fact(unsigned long long N) {
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
	unsigned long long Q = 5;
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
			Q = Q + (unsigned long long) diff;
			diff = (diff & 2) + 2;
		}
	}
}
void pollard_rho_fact(unsigned long long N) {
	if (N == 1ULL) return;
	else if (N < (1ULL << 10)) fast_native_fact(N);
	else if(miller_rabin_testing(10, N) == 1) Fa[nfact++] = N;
	else {
		unsigned long long p = 0ULL;
		while (p == 0 || p == N) p = find_factor(N);
		pollard_rho_fact(p);
		pollard_rho_fact(N / p);
	}
}

int main() {
	pollard_rho_fact(123568412123568412LL);
	sort(Fa, Fa + nfact);
	for (int i = 0; i < nfact; i++) printf("%lld ", Fa[i]);
	return 0;
}
