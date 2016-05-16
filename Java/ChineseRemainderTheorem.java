static class ChineseRemainderTheorem {
	public int n;
	public int[] p;
	public int[] r;
	public int[][] inv;

	public ChineseRemainderTheorem(int[] p, int[] r) {
		n = p.length;
		this.p = new int[n];
		this.r = new int[n];
		this.inv = new int[n][n];
		for (int i = 0; i < n; i++) {
			this.p[i] = p[i];
			this.r[i] = r[i];
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				inv[i][j] = BigInteger.valueOf(p[i]).modInverse(BigInteger.valueOf(p[j])).intValue();
			}
		}
	}
	public BigInteger Calc() {
		BigInteger res = BigInteger.ZERO, prd = BigInteger.ONE;
		int[] x = new int[n];
		for (int i = 0; i < n; i++) {
			x[i] = r[i];
			for (int j = 0; j < i; j++) {
				long cur = (long) (x[i] - x[j]) * inv[j][i];
				x[i] = (int) ((cur % p[i] + p[i]) % p[i]);
			}
			res = res.add(prd.multiply(BigInteger.valueOf(x[i])));
			prd = prd.multiply(BigInteger.valueOf(p[i]));
		}
		return res.mod(prd);
	}
}