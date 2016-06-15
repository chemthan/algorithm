#include <bits/stdc++.h>
using namespace std;

//Source https://github.com/yunchi/Dynamic_Convex_Hull
struct Point {
	long long x, y;
	Point() {x = y = 0;}
	Point(long long x, long long y) : x(x), y(y) {}
	Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}
	int operator == (const Point& rhs) const {
		return make_pair(x, y) == make_pair(rhs.x, rhs.y);
	}
	int operator != (const Point& rhs) const {
		return make_pair(x, y) != make_pair(rhs.x, rhs.y);
	}
	int operator < (const Point& rhs) const {
		return make_pair(x, y) < make_pair(rhs.x, rhs.y);
	}
	int operator > (const Point& rhs) const {
		return make_pair(x, y) > make_pair(rhs.x, rhs.y);
	}
	int operator <= (const Point& rhs) const {
		return make_pair(x, y) <= make_pair(rhs.x, rhs.y);
	}
	int operator >= (const Point& rhs) const {
		return make_pair(x, y) >= make_pair(rhs.x, rhs.y);
	}
	long long cross(Point rhs) {
		return x * rhs.y - y * rhs.x;
	}
} nil;

void init() {
	nil.x = nil.y = (int) 1e9;
}

const int RED = 0;
const int BLACK = 1;
const int LEFT = 0;
const int RIGHT = 1;

struct Node {
	Point ex, mn, mx;
	Node *left, *right, *lMax;
	int color, isLeaf;
	long long sumcross;
	Node() {
		ex = mn = mx = nil;
		left = right = lMax = NULL;
		color = isLeaf = 0;
		sumcross = 0;
	}
	Node(Point p) {
		isLeaf = 1;
		color = BLACK;
		ex = mn = mx = p;
		left = right = lMax = NULL;
		lMax = this;
		sumcross = 0;
	}
	Node(Node* lMax, Node* left, Node* right) {
		this->ex = this->mn = this->mx = nil;
		this->isLeaf = 0;
		this->color = RED;
		this->lMax = lMax;
		this->left = left;
		this->right = right;
		this->sumcross = 0;
		pushup();
	}
	Node(Point p, Node* leftLeaf, Node* rightLeaf) {
		//assert((leftLeaf == NULL || leftLeaf->isLeaf) && (rightLeaf == NULL || rightLeaf->isLeaf));
		this->ex = this->mn = this->mx = p;
		this->isLeaf = 1;
		this->color = BLACK;
		this->lMax = this;
		this->left = leftLeaf;
		this->right = rightLeaf;
		this->sumcross = 0;
	}
	void pushup() {
		Node *left = this->left, *right = this->right;
		this->mn = this->mx = nil;
		this->sumcross = 0;
		if (left != NULL) {
			if (this->mn == nil || (left->mn != nil && this->mn > left->mn)) {
				this->mn = left->mn;
			}
			if (this->mx == nil || (left->mx != nil && this->mx < left->mx)) {
				this->mx = left->mx;
			}
			this->sumcross += left->sumcross;
		}
		if (right != NULL) {
			if (this->mn == nil || (right->mn != nil && this->mn > right->mn)) {
				this->mn = right->mn;
			}
			if (this->mx == nil || (right->mx != nil && this->mx < right->mx)) {
				this->mx = right->mx;
			}
			this->sumcross += right->sumcross;
		}
		if (left != NULL && right != NULL && left->mx != nil && right->mn != nil) {
			this->sumcross += left->mx.cross(right->mn);
		}
	}
};

struct TopTree {
	Node* root;
	int size;
	TopTree() {
		root = NULL;
		size = 0;
	}
	int getSize() {
		return size;
	}
	static Node* rotateLeft(Node* n) {
		//assert(n != NULL);
		//assert(!n->isLeaf && !n->right->isLeaf && n->right->color == RED);
		Node* tempNode = n->right;
		int tempColor = n->color;
		n->right = tempNode->left;
		n->color = tempNode->color;
		tempNode->left = n;
		tempNode->color = tempColor;
		n->pushup(); tempNode->pushup();
		return tempNode;
	}
	static Node* rotateRight(Node* n) {
		//assert(n != NULL);
		//assert(!n->isLeaf && !n->left->isLeaf && n->left->color == RED);
		Node* tempNode = n->left;
		int tempColor = n->color;
		n->left = tempNode->right;
		n->color = tempNode->color;
		tempNode->right = n;
		tempNode->color = tempColor;
		n->pushup(); tempNode->pushup();
		return tempNode;
	}
	static void flipTripleColor(Node* n) {
		//assert(n != NULL);
		//assert(!n->isLeaf && !n->left->isLeaf && !n->right->isLeaf);
		n->color = !n->color;
		n->left->color = !n->left->color;
		n->right->color = !n->right->color;
	}
	static Node* fixUp(Node* n) {
		//assert(n != NULL);
		if (n->isLeaf) {
			return n;
		}
		if (n->left->color == BLACK && n->right->color == RED) {
			n = rotateLeft(n);
		}
		else {
			if (n->left->color == RED && n->left->left->color == RED) {
				//assert(n->right->color == BLACK);
				n = rotateRight(n);
			}
			if (n->left->color == RED && n->right->color == RED) {
				flipTripleColor(n);
			}
		}
		return n;
	}
	Node* addLeaf(Point p, Node* leftLeaf, Node* rightLeaf) {
		//assert(p != nil);
		//assert((leftLeaf == NULL || leftLeaf->isLeaf) && (rightLeaf == NULL || rightLeaf->isLeaf));
		Node* n = new Node(p);
		size++;
		return n;
	}
	void removeLeaf(Node* n) {
		//assert(n != NULL && n->isLeaf);
		size--;
		//assert(size >= 0);
		delete n;
	}
	Node* insertAt(Node* n, Point p) {
		//assert(n != NULL);
		if (p <= n->lMax->ex) {
			if (n->isLeaf) {
				if (p == n->ex) {
					n->ex = n->mn = n->mx = p;
				}
				else {
					Node* nNew = addLeaf(p, n->left, n);
					n = new Node(nNew, nNew, n);
				}
			}
			else {
				n->left = insertAt(n->left, p);
				//n->pushup();
			}
		}
		else {
			if (n->isLeaf) {
				Node* nNew = addLeaf(p, n, n->right);
				n = new Node(n, n, nNew);
			}
			else {
				n->right = insertAt(n->right, p);
				//n->pushup();
			}
		}
		n = fixUp(n);
		return n;
	}
	Node* deleteAt(Node* n, Point p) {
		//assert(n != NULL);
		//assert(!n->isLeaf);
		//assert(n->color == RED || n->left->color == RED);
		if (p <= n->lMax->ex) {
			if (n->left->isLeaf) {
				if (p != n->left->ex) {
					return n;
				}
				else {
					//assert(n->color == RED);
					//assert(n->right->isLeaf);
					removeLeaf(n->left);
					//n->pushup();
					return n->right;
				}
			}
			if (p == n->lMax->ex) {
				//assert(!n->left->isLeaf);
				Node* tempNode = n->left;
				while (!tempNode->right->isLeaf) {
					tempNode = tempNode->right;
				}
				n->lMax = tempNode->lMax;
			}
			if (n->left->color == RED || n->left->left->color == RED) {
				n->left = deleteAt(n->left, p);
				//n->pushup();
			}
			else {
				//assert(!n->right->isLeaf);
				//assert(n->color == RED);
				flipTripleColor(n);
				n->left = deleteAt(n->left, p);
				//n->pushup();
				if (n->left->color == RED) {
					flipTripleColor(n);
				}
				else if (n->right->left->color == BLACK) {
					n = rotateLeft(n);
				} 
				else {
					n->right = rotateRight(n->right);
					//n->pushup();
					n = rotateLeft(n);
					flipTripleColor(n);
				}
			}
		}
		else {
			if (n->right->isLeaf) {
				if (p != n->right->ex) {
					return n;
				}
				else {
					removeLeaf(n->right);
					//n->pushup();
					n->left->color = BLACK;
					return n->left;
				}
			}
			else if (n->right->left->color == RED) {
				n->right = deleteAt(n->right, p);
				//n->pushup();
			}
			else if (n->color == RED) {
				//assert(n->left->color == BLACK);
				flipTripleColor(n);
				n->right = deleteAt(n->right, p);
				//n->pushup();
				if (n->right->color == RED) {
					flipTripleColor(n);
				}
				else if (n->left->left->color == RED) {
					n = rotateRight(n);
					flipTripleColor(n);
				}
			}
			else {
				//assert(n->left->color == RED);
				n = rotateRight(n);
				n->right = deleteAt(n->right, p);
				//n->pushup();
				if (n->right->color == RED) {
					n = rotateLeft(n);
				}
			}
		}
		return n;
	}
	Point search(Point p) {
		if (root == NULL) {
			return nil;
		}
		Node* n = root;
		while (!n->isLeaf) {
			if (p == n->lMax->ex) {
				return n->lMax->ex;
			}
			else if (p < n->lMax->ex) {
				n = n->left;
			}
			else {
				n = n->right;
			}
		}
		if (p != n->ex) {
			return nil;
		}
		else {
			return n->ex;
		}
	}
	void insert(Point p) {
		if (root == NULL) {
			root = new Node(p);
			size = 1;
		}
		else {
			root = insertAt(root, p);
			//root->pushup();
			if (root->color == RED) {
				root->color = BLACK;
			}
		}
	}
	void remove(Point p) {
		if (root == NULL) {
			return;
		}
		else if (root->isLeaf) {
			if (p == root->ex) {
				root = NULL;
				size = 0;
			}
			return;
		}
		else {
			if (root->left->color == BLACK && root->right->color == BLACK) {
				root->color = RED;
			}
			root = deleteAt(root, p);
			//root->pushup();
			if (root->color == RED) {
				root->color = BLACK;
			}
			return;
		}
	}
};

struct CQueue : TopTree {
	int height;
	Node *minNode, *maxNode;
	CQueue() {
		root = NULL;
		height = -1;
		minNode = NULL;
		maxNode = NULL;
	}
	CQueue(Point p) {
		root = new Node(p);
		height = 0;
		minNode = root;
		maxNode = root;
	}
	CQueue(Node* root, int height, Node* minNode, Node* maxNode) {
		this->root = root;
		this->height = height;
		this->minNode = minNode;
		this->maxNode = maxNode;
	}
	void shallowCopy(CQueue* rhs) {
		if (rhs == NULL) {
			return;
		}
		else {
			this->root = rhs->root;
			this->height = rhs->height;
			this->minNode = rhs->minNode;
			this->maxNode = rhs->maxNode;
		}
	}
	int getSize() {
		if (minNode == NULL) {
			return 0;
		}
		else {
			Node* tempNode = minNode;
			int i = 1;
			while (tempNode->right != NULL) {
				i++;
				tempNode = tempNode->right;
			}
			return i;
		}
	}
	Node* addLeaf(Point p, Node* leftLeaf, Node* rightLeaf) {
		//assert((leftLeaf == NULL || leftLeaf->isLeaf) && (rightLeaf == NULL || rightLeaf->isLeaf));
		Node* n = new Node(p, leftLeaf, rightLeaf);
		if (n->left != NULL) {
			n->left->right = n;
		}
		else {
			minNode = n;
		}
		if (n->right != NULL) {
			n->right->left = n;
		}
		else {
			maxNode = n;
		}
		return n;
	}
	void removeLeaf(Node* n) {
		//assert(n->isLeaf);
		if (n->left != NULL) {
			n->left->right = n->right;
		}
		else {
			minNode = n->right;
		}
		if (n->right != NULL) {
			n->right->left = n->left;
		}
		else {
			maxNode = n->left;
		}
		delete n;
	}
	void insert(Point p) {
		if (root == NULL) {
			root = minNode = maxNode = new Node(p);
			height = 0;
		}
		else {
			root = insertAt(root, p);
			//root->pushup();
			if (root->color == RED) {
				root->color = BLACK;
				height++;
			}
		}
	}
	void remove(Point p) {
		if (root == NULL) {
			return;
		}
		else if (root->isLeaf) {
			if (p == root->ex) {
				root = minNode = maxNode = NULL;
				height = -1;
			}
		}
		else {
			if (root->left->color == BLACK && root->right->color == BLACK) {
				root->color = RED;
				height--;
			}
			root = deleteAt(root, p);
			if (root->color == RED) {
				root->color = BLACK;
				height++;
			}
		}
	}
	static Node* glueTree(Node* lN, Node* rN, int lH, int rH, Node* lMax) {
		//assert(!(lN->color == RED && rN->color == RED));
		if (lN == NULL) {
			//rN->pushup();
			return rN;
		}
		else if (rN == NULL) {
			//lN->pushup();
			return lN;
		}
		else if (lH == rH) {
			//assert(lN->color == BLACK && rN->color == BLACK);
			return new Node(lMax, lN, rN);
		}
		else if (lH > rH) {
			lN->right = glueTree(lN->right, rN, lH - 1, rH, lMax);
			lN->pushup();
			lN = fixUp(lN);
			return lN;
		}
		else {
			if (rN->left->color == RED) {
				rN->left = glueTree(lN, rN->left, lH, rH, lMax);
				rN->pushup();
				rN = fixUp(rN);
			}
			else {
				rN->left = glueTree(lN, rN->left, lH, rH - 1, lMax);
				rN->pushup();
			}
			return rN;
		}
	}
	friend CQueue* concatenate(CQueue* qLeft, CQueue* qRight) {
		if (qLeft == NULL || qLeft->height == -1) {
			return qRight;
		}
		else if (qRight == NULL || qRight->height == -1) {
			return qLeft;
		}
		qLeft->maxNode->right = qRight->minNode;
		qRight->minNode->left = qLeft->maxNode;
		int newHeight = max(qLeft->height, qRight->height);
		Node* newRoot = glueTree(qLeft->root, qRight->root, qLeft->height, qRight->height, qLeft->maxNode);
		newRoot->pushup();
		if (newRoot->color == RED) {
			newRoot->color = BLACK;
			newHeight++;
		}
		return new CQueue(newRoot, newHeight, qLeft->minNode, qRight->maxNode);
	}
	static void cutAt(Node* n) {
		//assert(n == NULL || n->isLeaf);
		if (n != NULL && n->right != NULL) {
			n->right->left = NULL;
			delete n->right->left;
			n->right = NULL;
			delete n->right;
		}
	}
	static void splitAt(Node* n, int h, Point p, CQueue* qLeft, CQueue* qRight) {
		//assert(p != nil && n != NULL);
		//assert(qLeft != NULL && qRight != NULL);
		//assert(n->color == BLACK);
		if (n->isLeaf) {
			if (p < n->ex) {
				qRight->root = n;
				qRight->minNode = n;
				qRight->height = 0;
				qLeft->maxNode = n->left;
				cutAt(n->left);
			}
			else {
				qLeft->root = n;
				qLeft->maxNode = n;
				qLeft->height = 0;
				qRight->minNode = n->right;
				cutAt(n);
			}
		}
		else {
			if (p == n->lMax->ex) {
				qLeft->root = n->left;
				qLeft->height = h - 1;
				qLeft->maxNode = n->lMax;
				if (qLeft->root->color == RED) {
					qLeft->root->color = BLACK;
					qLeft->height++;
				}
				qRight->root = n->right;
				qRight->height = h - 1;
				qRight->minNode = n->lMax->right;
				cutAt(n->lMax);
			}
			else if (p < n->lMax->ex) {
				if (n->left->color == RED) {
					n->left->color = BLACK;
					splitAt(n->left, h, p, qLeft, qRight);
				}
				else {
					splitAt(n->left, h - 1, p, qLeft, qRight);
				}
				int tempHeight = qRight->height;
				qRight->root = glueTree(qRight->root, n->right, qRight->height, h - 1, n->lMax);
				//qRight->root->pushup();
				qRight->height = max(tempHeight, h - 1);
				if (qRight->root->color == RED) {
					qRight->root->color = BLACK;
					qRight->height++;
				}
			}
			else {
				splitAt(n->right, h - 1, p, qLeft, qRight);
				if (n->left->color == RED) {
					n->left->color = BLACK;
					qLeft->root = glueTree(n->left, qLeft->root, h, qLeft->height, n->lMax);
					//qLeft->root->pushup();
					qLeft->height = h;
				} else {
					qLeft->root = glueTree(n->left, qLeft->root, h - 1, qLeft->height, n->lMax);
					//qLeft->root->pushup();
					qLeft->height = h - 1;
				}
				if (qLeft->root->color == RED) {
					qLeft->root->color = BLACK;
					qLeft->height++;
				}
			}
		}
	}
	CQueue* split(Point p, int returnLoR, int inclusive) {
		CQueue* qLeft = new CQueue();
		CQueue* qRight = new CQueue();
		if (root == NULL) {
			return qLeft;
		}
		else if (p < minNode->ex || (p == minNode->ex && !inclusive)) {
			if (returnLoR == RIGHT) {
				qRight->shallowCopy(this);
				this->shallowCopy(qLeft);
				return qRight;
			}
			else {
				return qLeft;
			}
		}
		else if (p > maxNode->ex || (p == maxNode->ex && inclusive)) {
			if (returnLoR == RIGHT) {
				return qRight;
			}
			else {
				qLeft->shallowCopy(this);
				this->shallowCopy(qRight);
				return qLeft;
			}
		}
		else {
			Node* itr = root;
			while (!itr->isLeaf) {
				if (p <= itr->lMax->ex) {
					itr = itr->left;
				}
				else {
					itr = itr->right;
				}
			}
			if (p == itr->ex) {
				if (inclusive) {
					p = itr->ex;
				}
				else {
					p = itr->left->ex;
				}
			}
			else if (p < itr->ex) {
				p = itr->left->ex;
			}
			else {
				p = itr->ex;
			}
		}
		qLeft->minNode = this->minNode;
		qRight->maxNode = this->maxNode;
		splitAt(this->root, this->height, p, qLeft, qRight);
		if (returnLoR == RIGHT) {
			this->shallowCopy(qLeft);
			return qRight;
		}
		else {
			this->shallowCopy(qRight);
			return qLeft;
		}

	}
};

struct SubHull : CQueue {
	SubHull() : CQueue() {}
	SubHull(Point c) : CQueue(c) {}
	SubHull(CQueue* q) : CQueue(q->root, q->height, q->minNode, q->maxNode) {}
	friend SubHull* bridge(SubHull* lHull, SubHull* rHull) {
		//assert(lHull != NULL && rHull != NULL);
		//assert(lHull->root != NULL && rHull->root != NULL);
		Node* lItr = lHull->root;
		Node* rItr = rHull->root;
		int done = 0;
		double middleX = (lHull->maxNode->ex.x + rHull->minNode->ex.x) / 2.0;
		while (!done) {
			double t = computeSlope(lItr->lMax, rItr->lMax);
			int iL = determineCase(lItr->lMax, t);
			int iR = determineCase(rItr->lMax, t);
			switch (iL) {
			case -1:
				switch (iR) {
				case -1:
					rItr = rItr->right;
					break;
				case 0:
					lItr = lItr->right;
					if (!rItr->isLeaf && rItr->right != NULL) {
						rItr = rItr->right;
					}
					break;
				case +1:
					double lHeight = lItr->lMax->ex.y + computeSlope(lItr->lMax, lItr->lMax->right) * (middleX - lItr->lMax->ex.x);
					double rHeight = rItr->lMax->ex.y + computeSlope(rItr->lMax->left, rItr->lMax) * (middleX - rItr->lMax->ex.x);
					if (lHeight <= rHeight) {
						rItr = rItr->left;
					}
					else {
						lItr = lItr->right;
					}
					break;
				}
				break;
			case 0:
				switch (iR) {
				case -1:
					if (!lItr->isLeaf && lItr->left != NULL) {
						lItr = lItr->left;
					}
					rItr = rItr->right;
					break;
				case 0:
					lItr = lItr->lMax;
					rItr = rItr->lMax;
					done = 1;
					break;
				case +1:
					if (!lItr->isLeaf && lItr->left != NULL) {
						lItr = lItr->left;
					}
					rItr = rItr->left;
					break;
				}
				break;
			case +1:
				switch (iR) {
				case -1:
					lItr = lItr->left;
					rItr = rItr->right;
					break;
				case 0:
					lItr = lItr->left;
					if (!rItr->isLeaf && rItr->right != NULL) {
						rItr = rItr->right;
					}
					break;
				case +1:
					lItr = lItr->left;
					break;
				}
				break;
			}
		}
		//assert(sanityCheck(lHull, rHull, lItr, rItr));
		//assert(lItr != NULL && rItr != NULL);
		return new SubHull(concatenate(lHull->split(lItr->ex, LEFT, 1), rHull->split(rItr->ex, RIGHT, 0)));
	}
	static double computeSlope(Node* leftN, Node* rightN) {
		//assert(leftN != NULL && rightN != NULL);
		//assert(leftN->isLeaf && rightN->isLeaf);
		if (rightN->ex.x - leftN->ex.x == 0) {
			if (rightN->ex.y - leftN->ex.y > 0) return 1e9;
			return -1e9;
		}
		return ((double) (rightN->ex.y - leftN->ex.y)) / ((double) (rightN->ex.x - leftN->ex.x));
	}
	static int determineCase(Node* n, double t) {
		//assert(n != NULL);
		//assert(n->isLeaf);
		int leftAbove = 1, rightAbove = 0;
		if ((n->left != NULL) && computeSlope(n->left, n) < t) {
			leftAbove = 0;
		}
		if ((n->right != NULL) && computeSlope(n, n->right) > t) {
			rightAbove = 1;
		}
		if (leftAbove && rightAbove) {
			return -1;
		}
		else if (!leftAbove && !rightAbove) {
			return +1;
		}
		else {
			//assert(leftAbove && !rightAbove);
			return 0;
		}
	}
	static int sanityCheck(SubHull* lHull, SubHull* rHull, Node* lPtr, Node* rPtr) {
		double t = computeSlope(lPtr, rPtr);
		if (lPtr->left != NULL && computeSlope(lPtr->left, lPtr) < t) {
			return 0;
		}
		if (lPtr->right != NULL && computeSlope(lPtr, lPtr->right) > t) {
			return 0;
		}
		if (rPtr->left != NULL && computeSlope(rPtr->left, rPtr) < t) {
			return 0;
		}
		if (rPtr->right != NULL && computeSlope(rPtr, rPtr->right) > t) {
			return 0;
		}
		return 1;
	}
	void printHull() {
		if (root == NULL) {
			return;
		}
		Node* n = minNode;
		while (n != NULL) {
			cout<<"("<<n->ex.x<<","<<n->ex.y<<")\n";
			n = n->right;
		}
	}
};

struct CNode : Node {
	CNode *left, *right, *lMax;
	SubHull* hull;
	CNode(Point c) {
		this->isLeaf = 1;
		this->color = BLACK;
		this->ex = this->mn = this->mx = c;
		this->lMax = this;
		this->hull = new SubHull(c);
	}
	CNode(CNode *lMax, CNode *left, CNode *right) {
		this->isLeaf = 0;
		this->color = RED;
		this->lMax = lMax;
		this->left = left;
		this->right = right;
		this->hull = NULL;
		this->hull = bridge(left->hull, right->hull);
	}
	CNode(Point c, CNode *leftLeaf, CNode *rightLeaf) {
		//assert((leftLeaf == NULL || leftLeaf->isLeaf) && (rightLeaf == NULL || rightLeaf->isLeaf));
		this->isLeaf = 1;
		this->color = BLACK;
		this->ex = c;
		this->lMax = this;
		this->left = leftLeaf;
		this->right = rightLeaf;
		this->hull = new SubHull(c);
	}
};

struct DynamicConvexHull {
	CNode* root;
	int size;
	DynamicConvexHull() {root = NULL; size = 0;}
	static void DOWN(CNode* n) {
		//assert(n != NULL);
		//assert(!n->isLeaf);
		n->left->hull = new SubHull(concatenate(n->hull->split(n->lMax->ex, LEFT, 1), n->left->hull));
		n->right->hull = new SubHull(concatenate(n->right->hull, n->hull));
	}
	static void UP(CNode* n) {
		//assert(n != NULL);
		//assert(!n->isLeaf);
		n->hull = bridge(n->left->hull, n->right->hull);
	}
	static CNode* rotateLeft(CNode* n) {
		//assert(n != NULL);
		//assert(!n->isLeaf && !n->right->isLeaf && n->right->color == RED);
		DOWN(n);
		CNode* tempCNode = n->right;
		int tempColor = n->color;
		DOWN(tempCNode);
		n->right = tempCNode->left;
		n->color = tempCNode->color;
		UP(n);
		tempCNode->left = n;
		tempCNode->color = tempColor;
		UP(tempCNode);
		return tempCNode;
	}
	static CNode* rotateRight(CNode* n) {
		//assert(n != NULL);
		//assert(!n->isLeaf && !n->left->isLeaf && n->left->color == RED);
		DOWN(n);
		CNode* tempCNode = n->left;
		int tempColor = n->color;
		DOWN(tempCNode);
		n->left = tempCNode->right;
		n->color = tempCNode->color;
		UP(n);
		tempCNode->right = n;
		tempCNode->color = tempColor;
		UP(tempCNode);
		return tempCNode;
	}
	CNode* addLeaf(Point c, CNode* nLeft, CNode* nRight) {
		size++;
		return new CNode(c);
	}
	void removeLeaf(Node* n) {
		size--;
		delete n;
	}
	static void flipTripleColor(CNode* n) {
		//assert(n != NULL);
		//assert(!n->isLeaf && !n->left->isLeaf && !n->right->isLeaf);
		n->color = !n->color;
		n->left->color = !n->left->color;
		n->right->color = !n->right->color;
	}
	static CNode* fixUp(CNode* n) {
		//assert(n != NULL);
		if (n->isLeaf) {
			return n;
		}
		if (n->left->color == BLACK && n->right->color == RED) {
			n = rotateLeft(n);
		}
		else {
			if (n->left->color == RED && n->left->left->color == RED) {
				//assert(n->right->color == BLACK);
				n = rotateRight(n);
			}
			if (n->left->color == RED && n->right->color == RED) {
				flipTripleColor(n);
			}
		}
		return n;
	}
	CNode* insertAt(CNode* n, Point p) {
		//assert(n != NULL);
		if (p <= n->lMax->ex) {
			if (n->isLeaf) {
				if (p == n->ex) {
					n->ex = n->mn = n->mx = p;
				}
				else {
					CNode* nNew = addLeaf(p, n->left, n);
					n = new CNode(nNew, nNew, n);
				}
			}
			else {
				DOWN(n);
				n->left = insertAt(n->left, p);
				UP(n);
			}
		}
		else {
			if (n->isLeaf) {
				CNode* nNew = addLeaf(p, n, n->right);
				n = new CNode(n, n, nNew);
			}
			else {
				DOWN(n);
				n->right = insertAt(n->right, p);
				UP(n);
			}
		}
		n = fixUp(n);
		return n;
	}
	CNode* deleteAt(CNode* n, Point p) {
		//assert(n != NULL);
		//assert(!n->isLeaf);
		//assert(n->color == RED || n->left->color == RED);
		if (p <= n->lMax->ex) {
			if (n->left->isLeaf) {
				if (p != n->left->ex) {
					return n;
				}
				else {
					//assert(n->color == RED);
					//assert(n->right->isLeaf);
					DOWN(n);
					removeLeaf(n->left);
					return n->right;
				}
			}
			DOWN(n);
			if (p == n->lMax->ex) {
				//assert(!n->left->isLeaf);
				CNode* tempCNode = n->left;
				while (!tempCNode->right->isLeaf) {
					tempCNode = tempCNode->right;
				}
				n->lMax = tempCNode->lMax;
			}
			if (n->left->color == RED || n->left->left->color == RED) {
				n->left = deleteAt(n->left, p);
				UP(n);
			}
			else {
				//assert(!n->right->isLeaf);
				flipTripleColor(n);
				n->left = deleteAt(n->left, p);
				if (n->left->color == RED) {
					UP(n);
					flipTripleColor(n);
				}
				else if (n->right->left->color == BLACK) {
					UP(n);
					n = rotateLeft(n);
				}
				else {
					n->right = rotateRight(n->right);
					UP(n);
					n = rotateLeft(n);
					flipTripleColor(n);
				}
			}
		}
		else {
			if (n->right->isLeaf) {
				if (p != n->right->ex) {
					return n;
				}
				else {
					DOWN(n);
					removeLeaf(n->right);
					n->left->color = BLACK;
					return n->left;
				}
			}
			else if (n->right->left->color == RED) {
				DOWN(n);
				n->right = deleteAt(n->right, p);
				UP(n);
			}
			else if (n->color == RED) {
				//assert(n->left->color == BLACK);
				flipTripleColor(n);
				DOWN(n);
				n->right = deleteAt(n->right, p);
				UP(n);
				if (n->right->color == RED) {
					flipTripleColor(n);
				}
				else if (n->left->left->color == RED) {
					n = rotateRight(n);
					flipTripleColor(n);
				}
			}
			else {
				//assert(n->left->color == RED);
				n = rotateRight(n);
				DOWN(n);
				n->right = deleteAt(n->right, p);
				UP(n);
				if (n->right->color == RED) {
					n = rotateLeft(n);
				}
			}
		}
		return n;
	}
	void insert(Point p) {
		if (root == NULL) {
			root = new CNode(p);
			size = 1;
		}
		else {
			root = insertAt(root, p);
			if (root->color == RED) {
				root->color = BLACK;
			}
		}
	}
	void remove(Point p) {
		if (root == NULL) {
			return;
		}
		else if (root->isLeaf) {
			if (p == root->ex) {
				root = NULL;
				size = 0;
			}
		}
		else {
			if (root->left->color == BLACK && root->right->color == BLACK) {
				root->color = RED;
			}
			root = deleteAt(root, p);
			if (root->color == RED) {
				root->color = BLACK;
			}
		}
	}
};

int main() {
	return 0;
}