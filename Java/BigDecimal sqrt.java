static BigDecimal sqrt(BigDecimal A, int SCALE) {
    BigDecimal x0 = new BigDecimal("0");
    BigDecimal x1 = new BigDecimal(Math.sqrt(A.doubleValue()));
    while (!x0.equals(x1)) {
        x0 = x1;
        x1 = A.divide(x0, SCALE, BigDecimal.ROUND_HALF_UP);
        x1 = x1.add(x0);
        x1 = x1.divide(BigDecimal.valueOf(2), SCALE, BigDecimal.ROUND_HALF_UP);
    }
    return x1;
}