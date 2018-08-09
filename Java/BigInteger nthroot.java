static BigInteger FloorOfNthRoot(BigInteger x, int n) {
	int sign = x.signum();
	if (n <= 0 || sign < 0) {
		throw new IllegalArgumentException();
	}
	if (sign == 0) {
		return BigInteger.ZERO;
	}
	if (n == 1) {
		return x;
	}
	BigInteger a;
	BigInteger bigN = BigInteger.valueOf(n);
	BigInteger bigNMinusOne = BigInteger.valueOf(n - 1);
	BigInteger b = BigInteger.ZERO.setBit(1 + x.bitLength() / n);
	do {
		a = b;
		b = a.multiply(bigNMinusOne).add(x.divide(a.pow(n - 1))).divide(bigN);
	}
	while (b.compareTo(a) == -1);
	return a;
}