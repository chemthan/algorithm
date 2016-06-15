import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) {
		DynamicConvexHull con = new DynamicConvexHull();
		int seed = 0;
		for (int i = 0; i < 1000; i++) {
			seed = (seed * 1001 + 100621) % 999983;
			int u = seed & ((1 << 16) - 1);
			seed = (seed * 1001 + 100621) % 999983;
			int v = seed & ((1 << 16) - 1);
			con.insert(new Point(u, v));

		}
		System.out.println(con.Area2()); //Expected 8433900701
	}

	final static boolean RED = false;
	final static boolean BLACK = true;
	final static boolean LEFT = false;
	final static boolean RIGHT = true;
	public static class Point {
		protected int x, y;
		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}
		public Point(Point rhs) {
			this.x = rhs.x;
			this.y = rhs.y;
		}
		public int compareTo(Point rhs) {
			if (this.x < rhs.x) {
				return -1;
			}
			else if (this.x > rhs.x) {
				return +1;
			}
			else {
				if (this.y < rhs.y) {
					return -1;
				}
				else if (this.y > rhs.y) {
					return +1;
				}
				else {
					return 0;
				}
			}
		}
		public long cross(Point rhs) {
			return (long) this.x * rhs.y - (long) this.y * rhs.x;
		}
	}
	public static class Node {
		public Point key;
		public Node parent, left, right;
		public Node maxNode, minNode, prv, nxt;
		public long sumcross;
		public Node(Point key) {
			this.key = key;
			parent = left = right = null;
			maxNode = minNode = this;
			prv = nxt = null;
			sumcross = 0;
		}
		public boolean isRoot() {
			return parent == null || (parent.left != this && parent.right != this);
		}
		public void pushup() {
			if (left != null && right != null) {
				minNode = left.minNode;
				maxNode = right.maxNode;
				sumcross = left.sumcross + right.sumcross + left.maxNode.key.cross(key) + key.cross(right.minNode.key);
			}
			else if (left != null) {
				minNode = left.minNode;
				maxNode = this;
				sumcross = left.sumcross + left.maxNode.key.cross(key);
			}
			else if (right != null) {
				minNode = this;
				maxNode = right.maxNode;
				sumcross = right.sumcross + key.cross(right.minNode.key);
			}
			else {
				minNode = maxNode = this;
				sumcross = 0;
			}
		}
	}
	public static class CQueue {
		public Node root;
		public CQueue() {
			root = null;
		}
		public CQueue(Point key) {			
			root = new Node(key);
		}
		public CQueue(Node root) {
			this.root = root;
		}
		public static void setchild(Node p, Node c, Boolean isLeftChild) {
			if (isLeftChild != null) {
				if (isLeftChild) {
					p.left = c;
				}
				else {
					p.right = c;
				}
			}
			if (c != null) {
				c.parent = p;
			}
		}
		public static void rotate(Node x) {
			Node p = x.parent;
			Node g = p.parent;
			boolean isRootP = p.isRoot();
			boolean leftChildX = (x == p.left);
			setchild(g, x, !isRootP ? p == g.left : null);
			setchild(p, leftChildX ? x.right : x.left, leftChildX);
			setchild(x, p, !leftChildX);
			p.pushup();
		}
		public static void splay(Node x) {
			if (x == null) return;
			while (!x.isRoot()) {
				Node p = x.parent;
				Node g = p.parent;
				if (!p.isRoot())
					g.pushup();
				p.pushup();
				x.pushup();
				if (!p.isRoot())
					rotate((x == p.left) == (p == g.left) ? p : x);
				rotate(x);
			}
			x.pushup();
		}
		public Node insert(Node x, Point key) {
			Node p = null;
			while (x != null) {
				p = x;
				if (x.key.compareTo(key) < 0) x = x.right;
				else x = x.left;
			}
			x = new Node(key);
			x.parent = p;
			if (p == null) {
				root = x;
			}
			else if (p.key.compareTo(x.key) < 0) p.right = x;
			else p.left = x;
			splay(x);
			return root = x;
		}
		public Node findkey(Node x, Point key) {
			while (x != null) {
				if (x.key.compareTo(key) < 0) x = x.right;
				else if (x.key.compareTo(key) > 0) x = x.left;
				else return x;
			}
			return null;
		}
		public static Node join(Node x, Node y) {
			if (x == null) return y;
			if (y == null) return x;
			while (true) {
				if (x.right == null) break;
				x = x.right;
			}
			splay(x);
			setchild(x, y, false);
			if (x != null && y != null) {
				x.maxNode.nxt = y.minNode;
				y.minNode.prv = x.maxNode;
			}
			x.pushup();
			return x;
		}
		public static CQueue concatenate(CQueue x, CQueue y) {
			if (x == null) return y;
			if (y == null) return x;
			return new CQueue(join(x.root, y.root));
		}
		public CQueue split(Point p, boolean returnLoR, boolean inclusive) {
			Node qLeft = null, qRight = null;
			Node y = findkey(root, p);
			if (y == null) {
				Node x = insert(root, p);
				if ((qLeft = x.left) != null) {
					qLeft.parent = null;
					qLeft.maxNode.nxt = null;
				}
				if ((qRight = x.right) != null) {
					qRight.parent = null;
					qRight.minNode.prv = null;
				}
			}
			else {
				splay(y);
				if ((returnLoR == LEFT && inclusive) || (returnLoR == RIGHT && !inclusive)) {
					if ((qRight = y.right) != null) {
						qRight.parent = null;
						qRight.minNode.prv = null;
					}
					if ((qLeft = y) != null) {
						qLeft.right = null;
						qLeft.nxt = null;
						qLeft.pushup();
					}
				}
				else {
					if ((qLeft = y.left) != null) {
						qLeft.parent = null;
						qLeft.maxNode.nxt = null;
					}
					if ((qRight = y) != null) {
						qRight.left = null;
						qRight.prv = null;
						qRight.pushup();
					}
				}
			}
			if (returnLoR == LEFT) {
				root = qRight;
				return new CQueue(qLeft);
			}
			else {
				root = qLeft;
				return new CQueue(qRight);
			}
		}
		public static CQueue bridge(CQueue lHull, CQueue rHull) {
			Node lItr = lHull.root;
			Node rItr = rHull.root;
			boolean done = false;
			int middleX = lHull.root.maxNode.key.x + rHull.root.minNode.key.x;
			while (!done) {
				int iL = determineCase(lItr, lItr.key, rItr.key);
				int iR = determineCase(rItr, lItr.key, rItr.key);
				switch (iL) {
				case -1:
					switch (iR) {
					case -1:
						rItr = rItr.right;
						break;
					case 0:
						lItr = lItr.right;
						break;
					case +1:
						double lHeight = 2 * lItr.key.y + computeSlope(lItr.key, lItr.nxt.key) * (middleX - 2 * lItr.key.x);
						double rHeight = 2 * rItr.key.y + computeSlope(rItr.prv.key, rItr.key) * (middleX - 2 * rItr.key.x);
						if (lHeight <= rHeight) {
							rItr = rItr.left;
						}
						else {
							lItr = lItr.right;
						}
						break;
					}
					break;
				case 0:
					switch (iR) {
					case -1:
						rItr = rItr.right;
						break;
					case 0:
						done = true;
						break;
					case +1:
						rItr = rItr.left;
						break;
					}
					break;
				case +1:
					switch (iR) {
					case -1:
						lItr = lItr.left;
						rItr = rItr.right;
						break;
					case 0:
						lItr = lItr.left;
						break;
					case +1:
						lItr = lItr.left;
						break;
					}
					break;
				}
			}
			return concatenate(lHull.split(lItr.key, LEFT, true), rHull.split(rItr.key, RIGHT, true));
		}
		protected static double computeSlope(Point pleft, Point pright) {
			if (pright.x - pleft.x == 0) {
				if (pright.y - pleft.y > 0) return 1e9;
				return -1e9;
			}
			return ((double) (pright.y - pleft.y)) / (pright.x - pleft.x);
		}
		protected static int check(Point a, Point b, Point c, Point d) {
			long x = (long) (b.y - a.y) * (d.x - c.x);
			long y = (long) (d.y - c.y) * (b.x - a.x);
			if (x == y) return 0;
			if (x > y) return 1;
			return -1;
		}
		protected static int determineCase(Node n, Point s, Point t) {
			boolean leftAbove = true;
			boolean rightAbove = false;
			if ((n.prv != null) && check(n.prv.key, n.key, s, t) < 0) {
				leftAbove = false;
			}
			if ((n.nxt != null) && check(n.key, n.nxt.key, s, t) > 0) {
				rightAbove = true;
			}
			if (leftAbove && rightAbove) {
				return -1;
			}
			else if (!leftAbove && !rightAbove) {
				return +1;
			}
			else {
				return 0;
			}
		}
	}
	public static class CNode {
		protected boolean isLeaf, color;
		protected CNode left, right, lMax;
		protected Point px;
		protected CQueue uhull, dhull;
		public CNode(Point p) {
			this.isLeaf = true;
			this.color = BLACK;
			this.px = p;
			this.lMax = this;
			uhull = new CQueue(p);
			dhull = new CQueue(new Point(-p.x, -p.y));
		}
		public CNode(CNode lMax, CNode left, CNode right) {
			this.isLeaf = false;
			this.color = RED;
			this.left = left;
			this.right = right;
			this.lMax = lMax;
			uhull = CQueue.bridge(left.uhull, right.uhull);
			dhull = CQueue.bridge(right.dhull, left.dhull);
		}
		public CNode(Point p, CNode leftLeaf, CNode rightLeaf) {
			this.isLeaf = true;
			this.color = BLACK;
			this.px = p;
			this.left = leftLeaf;
			this.right = rightLeaf;
			this.lMax = this;
			uhull = new CQueue(p);
			dhull = new CQueue(new Point(-p.x, -p.y));
		}
	}
	public static class DynamicConvexHull {
		protected CNode root;
		public DynamicConvexHull() {
			this.root = null;
		}
		protected static void Down(CNode n) {
			n.left.uhull = CQueue.concatenate(n.uhull.split(n.lMax.px, LEFT, true), n.left.uhull);
			n.right.uhull = CQueue.concatenate(n.right.uhull, n.uhull);
			n.right.dhull = CQueue.concatenate(n.dhull.split(new Point(-n.lMax.px.x, -n.lMax.px.y), LEFT, false), n.right.dhull);
			n.left.dhull = CQueue.concatenate(n.left.dhull, n.dhull);
		}
		protected static void Up(CNode n) {
			n.uhull = CQueue.bridge(n.left.uhull, n.right.uhull);
			n.dhull = CQueue.bridge(n.right.dhull, n.left.dhull);
		}
		protected static CNode rotateLeft(CNode n) {
			Down(n);
			CNode tempCNode = n.right;
			boolean tempColor = n.color;
			Down(tempCNode);
			n.right = tempCNode.left;
			n.color = tempCNode.color;
			Up(n);
			tempCNode.left = n;
			tempCNode.color = tempColor;
			Up(tempCNode);
			return tempCNode;
		}
		protected static CNode rotateRight(CNode n) {
			Down(n);
			CNode tempCNode = n.left;
			boolean tempColor = n.color;
			Down(tempCNode);
			n.left = tempCNode.right;
			n.color = tempCNode.color;
			Up(n);
			tempCNode.right = n;
			tempCNode.color = tempColor;
			Up(tempCNode);
			return tempCNode;
		}
		protected static void flipTripleColor(CNode n) {
			n.color = !n.color;
			n.left.color = !n.left.color;
			n.right.color = !n.right.color;
		}
		protected static CNode fixUp(CNode n) {
			if (n.isLeaf) {
				return n;
			}
			if (n.left.color == BLACK && n.right.color == RED) {
				n = rotateLeft(n);
			}
			else {
				if (n.left.color == RED && n.left.left.color == RED) {
					n = rotateRight(n);
				}
				if (n.left.color == RED && n.right.color == RED) {
					flipTripleColor(n);
				}
			}
			return n;
		}
		protected CNode insertAt(CNode n, Point p) {
			if (p.compareTo(n.lMax.px) <= 0) {
				if (n.isLeaf) {
					if (p.compareTo(n.px) == 0) {
						n.px = p;
					}
					else {
						CNode nNew = new CNode(p);
						n = new CNode(nNew, nNew, n);
					}
				}
				else {
					Down(n);
					n.left = insertAt(n.left, p);
					Up(n);
				}
			}
			else {
				if (n.isLeaf) {
					CNode nNew = new CNode(p);
					n = new CNode(n, n, nNew);
				}
				else {
					Down(n);
					n.right = insertAt(n.right, p);
					Up(n);
				}
			}
			n = fixUp(n);
			return n;
		}
		protected CNode deleteAt(CNode n, Point p) {
			if (p.compareTo(n.lMax.px) <= 0) {
				if (n.left.isLeaf) {
					if (p.compareTo(n.left.px) != 0) {
						return n;
					}
					else {
						Down(n);
						return n.right;
					}
				}
				Down(n);
				if (p.compareTo(n.lMax.px) == 0) {
					CNode tempCNode = n.left;
					while (!tempCNode.right.isLeaf) {
						tempCNode = tempCNode.right;
					}
					n.lMax = tempCNode.lMax;
				}
				if (n.left.color == RED || n.left.left.color == RED) {
					n.left = deleteAt(n.left, p);
					Up(n);
				}
				else {
					flipTripleColor(n);
					n.left = deleteAt(n.left, p);
					if (n.left.color == RED) {
						Up(n);
						flipTripleColor(n);
					}
					else if (n.right.left.color == BLACK) {
						Up(n);
						n = rotateLeft(n);
					}
					else {
						n.right = rotateRight(n.right);
						Up(n);
						n = rotateLeft(n);
						flipTripleColor(n);
					}
				}
			}
			else {
				if (n.right.isLeaf) {
					if (p.compareTo(n.right.px) != 0) {
						return n;
					}
					else {
						Down(n);
						n.left.color = BLACK;
						return n.left;
					}
				}
				else if (n.right.left.color == RED) {
					Down(n);
					n.right = deleteAt(n.right, p);
					Up(n);
				}
				else if (n.color == RED) {
					flipTripleColor(n);
					Down(n);
					n.right = deleteAt(n.right, p);
					Up(n);
					if (n.right.color == RED) {
						flipTripleColor(n);
					}
					else if (n.left.left.color == RED) {
						n = rotateRight(n);
						flipTripleColor(n);
					}
				}
				else {
					n = rotateRight(n);
					Down(n);
					n.right = deleteAt(n.right, p);
					Up(n);
					if (n.right.color == RED) {
						n = rotateLeft(n);
					}
				}
			}
			return n;
		}
		public void insert(Point p) {
			if (root == null) {
				root = new CNode(p);
			}
			else {
				root = insertAt(root, p);
				if (root.color == RED) {
					root.color = BLACK;
				}
			}
		}
		public void delete(Point p) {
			if (root == null) {
				return;
			}
			else if (root.isLeaf) {
				if (p.compareTo(root.px) == 0) {
					root = null;
				}
			}
			else {
				if (root.left.color == BLACK && root.right.color == BLACK) {
					root.color = RED;
				}
				root = deleteAt(root, p);
				if (root.color == RED) {
					root.color = BLACK;
				}
			}
		}
		public long Area2() {
			if (root == null) {
				return 0;
			}
			long res = 0;
			if (root.uhull != null && root.uhull.root != null) {
				res += root.uhull.root.sumcross;
			}
			if (root.dhull != null && root.dhull.root != null) {
				res += root.dhull.root.sumcross;
			}
			return Math.abs(res);
		}
	}
}
