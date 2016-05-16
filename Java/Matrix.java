static class Matrix {
	public int n, MOD;
	public int[][] x;

	public Matrix(int n, int MOD) {
		this.n = n;
		this.MOD = MOD;
		x = new int[n][n];
	}
	public Matrix add(Matrix A) {
		Matrix res = new Matrix(n, MOD);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				res.x[i][j] = x[i][j] + A.x[i][j];
				if (res.x[i][j] >= MOD) res.x[i][j] -= MOD;
			}
		return res;
	}
	public Matrix mul(Matrix A) {
		Matrix res = new Matrix(n, MOD);
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < n; k++) {
				for (int j = 0; j < n; j++) {
					res.x[i][j] = (int) ((res.x[i][j] + (long) x[i][k] * A.x[k][j]) % MOD);
				}
			}
		}
		return res;
	}
	public Matrix pow(long k) {
		Matrix res = this, tmp = this;
		k--;
		while (k > 0) {
			if ((k & 1) == 1) {
				res = res.mul(tmp);
			}
			tmp = tmp.mul(tmp);
			k >>= 1;
		}
		return res;
	}
	public Matrix sumpower(Matrix A, long k) {
		if (k == 1) return A;
		ArrayList<Integer> bit = new ArrayList<>();
		while (k > 0) {
			bit.add((int) (k & 1));
			k >>= 1;
		}
		Matrix res = A, tmp = A;
		for (int i = bit.size() - 2; i >= 0; i--) {
			res = res.add(res.mul(tmp));
			tmp = tmp.mul(tmp);
			if (bit.get(i) % 2 == 1) {
				tmp = tmp.mul(A);
				res = res.add(tmp);
			}
		}
		return res;
	}
}