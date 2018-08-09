BitSet shiftLeft(BitSet a, int k) {
	long[] ar = a.toLongArray();
	int d = k >> 6;
	int r = k & 63;
	long[] rs = new long[ar.length + d + 1];
	for (int i = d; i < rs.length; i++) {
		if (i - d < ar.length) {
			rs[i] = ar[i - d] << r;
		}
		if (i - d - 1 >= 0 && r > 0) {
			rs[i] |= ar[i - d - 1] >>> 64 - r;
		}
	}
	return BitSet.valueOf(rs);
}

BitSet shiftRight(BitSet a, int k) {
	long[] ar = a.toLongArray();
	int d = k >> 6;
	int r = k & 63;
	for (int i = 0; i + d < ar.length; i++) {
		ar[i] = ar[i + d] >>> r;
		if (i + d + 1 < ar.length && r > 0) {
			ar[i] |= ar[i + d + 1] << 64 - r;
		}
	}
	for (int i = Math.max(0, ar.length - d); i < ar.length; i++) {
		ar[i] = 0;
	}
	return BitSet.valueOf(ar);
}