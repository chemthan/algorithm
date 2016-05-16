static int fpow(int n, long k, int p) {
	int r = 1;
	for (; k > 0; k >>= 1) {
		if (k % 2 == 1) {
			r = (int) ((long) r * n % p);
		}
		n = (int) ((long) n * n % p);
	}
	return r;
}
static int ModularDeterminant(int[][] a, int mod) {
	int i, j, k, n = a.length, m = a[0].length;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			a[i][j] = (a[i][j] % mod + mod) % mod;
		}
	}
	int res = 1;
	for (i = 0; i < n; i++) {
		if (a[i][i] == 0) {
			for (j = i + 1; j < n; j++) {
				if (a[j][i] != 0) {
					for (k = 0; k < m; k++) a[i][k] = (a[i][k] + a[j][k]) % mod;
					break;
				}
			}
			if (j == n) return 0;
		}
		int tmp = a[i][i], inv = fpow(tmp, (long) mod - 2, mod);
		for (k = 0; k < m; k++) a[i][k] = (int) ((long) a[i][k] * inv % mod);
		res = (int) ((long) res * tmp % mod);
		for (j = 0; j < n; j++) {
			if (j == i) continue;
			tmp = a[j][i];
			for (k = 0; k < m; k++) a[j][k] = (int) ((a[j][k] - (long) a[i][k] * tmp % mod + mod) % mod);
		}
	}
	return res;
}