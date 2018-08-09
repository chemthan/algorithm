import java.io.*;
import java.util.*;

public class Main {
	
	static PrintWriter out;
	
	static final double EPS = 1e-9;
	static final int INF = (int) 1e9;
	static final long LINF = (long) 1e18;
	static final int MOD = (int) 1e9 + 7;
	static final double PI = Math.acos(-1);
	
	static void solve() {
	}
	
	public static void main(String[] args) {
		out = new PrintWriter(System.out);
		//long stime = System.currentTimeMillis();
		solve();
		//out.println("\nTime elapsed: " + (System.currentTimeMillis() - stime) + "ms");
		out.close();
	}
	
	static class Input {
		static StringTokenizer token = null;
		static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		static int nextInt() {
			return Integer.parseInt(nextString());
		}
		static long nextLong() {
			return Long.parseLong(nextString());
		}
		static double nextDouble() {
			return Double.parseDouble(nextString());
		}
		static String nextString() {
			try {
				while (token == null || !token.hasMoreTokens()) {
					token = new StringTokenizer(in.readLine());
				}
			} catch (IOException e) {
			}
			return token.nextToken();
		}
	}
}