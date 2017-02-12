#include <bits/stdc++.h>
using namespace std;

struct Lehmer {
	static const int MAXX = 100 + 5;
	static const int MAXY = 100000 + 5;
	static const int MAXN = 10000000 + 5;
	static const int MAXP = 1000000 + 5;
	int np;
	int fl[MAXN], sp[MAXN];
	int pr[MAXP], cn[MAXN];
	long long f[MAXX][MAXY];

	Lehmer() {
		for (int i = 2; i < MAXN; i += 2) sp[i] = 2;
		for (int i = 3; i < MAXN; i += 2) if (!fl[i]) {
			sp[i] = i;
			for (int j = i; (long long) i * j < MAXN; j += 2) if (!fl[i * j]) {
				fl[i * j] = 1;
				sp[i * j] = i;
			}
		}
		np = 0;
		for (int i = 2; i < MAXN; i++) {
			if (sp[i] == i) {
				pr[np++] = i;
			}
			cn[i] = np;
		}
		for (int i = 0; i < MAXX; i++) {
			for (int j = 0; j < MAXY; j++) {
				if (!i) f[i][j] = j;
				else f[i][j] = f[i - 1][j] - f[i - 1][j / pr[i - 1]];
			}
		}
	}
	long long LegendreSum(long long m, int n) {
		if (!n) return m;
		if (pr[n - 1] >= m) return 1;
		if (m < MAXY && n < MAXX) return f[n][m];
		return LegendreSum(m, n - 1) - LegendreSum(m / pr[n - 1], n - 1);
	}
	long long calc(long long m) {
		if (m < MAXN) return cn[m];
		int x = sqrt(m + 0.9), y = cbrt(m + 0.9);
		int a = cn[y];
		long long res = LegendreSum(m, a) + a - 1;
		for (int i = a; pr[i] <= x; i++) res = res - calc(m / pr[i]) + calc(pr[i]) - 1;
		return res;
	}
} lehmer;

int main() {
	cout << lehmer.calc(1e12) << "\n"; //Expected 37607912018
	return 0;
}
