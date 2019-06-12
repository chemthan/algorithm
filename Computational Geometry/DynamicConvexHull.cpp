#include <bits/stdc++.h>
using namespace std;

const int RED = 0;
const int BLACK = 1;
const int LEFT = 0;
const int RIGHT = 1;

struct point_t {
    int x, y;
    point_t() {
        x = y = 0;
    }
    point_t(int x, int y) : x(x), y(y) {}
    point_t(const point_t& rhs) : x(rhs.x), y(rhs.y) {}
    int operator == (const point_t& rhs) const {
        return make_pair(x, y) == make_pair(rhs.x, rhs.y);
    }
    int operator != (const point_t& rhs) const {
        return make_pair(x, y) != make_pair(rhs.x, rhs.y);
    }
    int operator < (const point_t& rhs) const {
        return make_pair(x, y) < make_pair(rhs.x, rhs.y);
    }
    int operator > (const point_t& rhs) const {
        return make_pair(x, y) > make_pair(rhs.x, rhs.y);
    }
    int operator <= (const point_t& rhs) const {
        return make_pair(x, y) <= make_pair(rhs.x, rhs.y);
    }
    int operator >= (const point_t& rhs) const {
        return make_pair(x, y) >= make_pair(rhs.x, rhs.y);
    }
    long long cross(point_t rhs) {
        return (long long) x * rhs.y - (long long) y * rhs.x;
    }
};

struct Node {
    point_t key;
    Node *parent, *left, *right;
    Node *maxNode, *minNode, *prv, *nxt;
    long long sumcross;
    Node(point_t key) {
        this->key = key;
        parent = left = right = 0;
        maxNode = minNode = this;
        prv = nxt = 0;
        sumcross = 0;
    }
    inline int isRoot() {
        return parent == 0 || (parent->left != this && parent->right != this);
    }
    inline void pushup() {
        if (left != 0 && right != 0) {
            minNode = left->minNode;
            maxNode = right->maxNode;
            sumcross = left->sumcross + right->sumcross + left->maxNode->key.cross(key) + key.cross(right->minNode->key);
        }
        else if (left != 0) {
            minNode = left->minNode;
            maxNode = this;
            sumcross = left->sumcross + left->maxNode->key.cross(key);
        }
        else if (right != 0) {
            minNode = this;
            maxNode = right->maxNode;
            sumcross = right->sumcross + key.cross(right->minNode->key);
        }
        else {
            minNode = maxNode = this;
            sumcross = 0;
        }
    }
};

struct CQueue {
    Node* root;
    CQueue() {
        root = 0;
    }
    CQueue(point_t key) {
        root = new Node(key);
    }
    CQueue(Node* root) {
        this->root = root;
    }
    inline static void setchild(Node* p, Node* c, int isLeftChild) {
        if (~isLeftChild) {
            if (isLeftChild) {
                p->left = c;
            }
            else {
                p->right = c;
            }
        }
        if (c != 0) {
            c->parent = p;
        }
    }
    inline static void rotate(Node* x) {
        Node* p = x->parent;
        Node* g = p->parent;
        int isRootP = p->isRoot();
        int leftChildX = (x == p->left);
        setchild(g, x, !isRootP ? p == g->left : -1);
        setchild(p, leftChildX ? x->right : x->left, leftChildX);
        setchild(x, p, !leftChildX);
        p->pushup();
    }
    inline static void splay(Node* x) {
        if (!x) return;
        while (!x->isRoot()) {
            Node* p = x->parent;
            Node* g = p->parent;
            if (!p->isRoot())
                g->pushup();
            p->pushup();
            x->pushup();
            if (!p->isRoot())
                rotate((x == p->left) == (p == g->left) ? p : x);
            rotate(x);
        }
        x->pushup();
    }
    inline Node* insert(Node* x, point_t key) {
        Node* p = 0;
        while (x != 0) {
            p = x;
            if (x->key < key) x = x->right;
            else x = x->left;
        }
        x = new Node(key);
        x->parent = p;
        if (p == 0) {
            root = x;
        }
        else if (p->key < x->key) p->right = x;
        else p->left = x;
        splay(x);
        return root = x;
    }
    inline Node* findkey(Node* x, point_t key) {
        while (x != 0) {
            if (x->key < key) x = x->right;
            else if (x->key > key) x = x->left;
            else return x;
        }
        return 0;
    }
    inline static Node* join(Node* x, Node* y) {
        if (!x) return y;
        if (!y) return x;
        while (1) {
            if (x->right == 0) break;
            x = x->right;
        }
        splay(x);
        setchild(x, y, false);
        if (x != 0 && y != 0) {
            x->maxNode->nxt = y->minNode;
            y->minNode->prv = x->maxNode;
        }
        x->pushup();
        return x;
    }
    inline static CQueue* concatenate(CQueue* x, CQueue* y) {
        if (x == 0) return y;
        if (y == 0) return x;
        return new CQueue(join(x->root, y->root));
    }
    inline friend CQueue* concatenate(CQueue* x, CQueue* y) {
        if (x == 0) return y;
        if (y == 0) return x;
        return new CQueue(join(x->root, y->root));
    }
    inline CQueue* split(point_t p, int returnLoR, int inclusive) {
        Node *qLeft = 0, *qRight = 0;
        Node* y = findkey(root, p);
        if (y == 0) {
            Node *x = insert(root, p);
            if ((qLeft = x->left) != 0) {
                qLeft->parent = 0;
                qLeft->maxNode->nxt = 0;
            }
            if ((qRight = x->right) != 0) {
                qRight->parent = 0;
                qRight->minNode->prv = 0;
            }
        } else {
            splay(y);
            if ((returnLoR == LEFT && inclusive) || (returnLoR == RIGHT && !inclusive)) {
                if ((qRight = y->right) != 0) {
                    qRight->parent = 0;
                    qRight->minNode->prv = 0;
                }
                if ((qLeft = y) != 0) {
                    qLeft->right = 0;
                    qLeft->nxt = 0;
                    qLeft->pushup();
                }
            } else {
                if ((qLeft = y->left) != 0) {
                    qLeft->parent = 0;
                    qLeft->maxNode->nxt = 0;
                }
                if ((qRight = y) != 0) {
                    qRight->left = 0;
                    qRight->prv = 0;
                    qRight->pushup();
                }
            }
        }
        if (returnLoR == LEFT) {
            root = qRight;
            return new CQueue(qLeft);
        } else {
            root = qLeft;
            return new CQueue(qRight);
        }
    }
    inline friend CQueue* bridge(CQueue* lHull, CQueue* rHull) {
        Node* lItr = lHull->root;
        Node* rItr = rHull->root;
        int done = 0;
        int middleX = lHull->root->maxNode->key.x + rHull->root->minNode->key.x;
        while (!done) {
            int iL = determineCase(lItr, lItr->key, rItr->key);
            int iR = determineCase(rItr, lItr->key, rItr->key);
            switch (iL) {
            case -1:
                switch (iR) {
                case -1:
                    rItr = rItr->right;
                    break;
                case 0:
                    lItr = lItr->right;
                    break;
                case +1:
                    double lHeight = 2 * lItr->key.y + computeSlope(lItr->key, lItr->nxt->key) * (middleX - 2 * lItr->key.x);
                    double rHeight = 2 * rItr->key.y + computeSlope(rItr->prv->key, rItr->key) * (middleX - 2 * rItr->key.x);
                    if (lHeight <= rHeight) {
                        rItr = rItr->left;
                    } else {
                        lItr = lItr->right;
                    }
                    break;
                }
                break;
            case 0:
                switch (iR) {
                case -1:
                    rItr = rItr->right;
                    break;
                case 0:
                    done = true;
                    break;
                case +1:
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
                    break;
                case +1:
                    lItr = lItr->left;
                    break;
                }
                break;
            }
        }
        return concatenate(lHull->split(lItr->key, LEFT, true), rHull->split(rItr->key, RIGHT, true));
    }
    inline static double computeSlope(point_t pleft, point_t pright) {
        if (pright.x - pleft.x == 0) {
            if (pright.y - pleft.y > 0) return 1e9;
            return -1e9;
        }
        return ((double) (pright.y - pleft.y)) / (pright.x - pleft.x);
    }
    inline static int check(point_t a, point_t b, point_t c, point_t d) {
        long long x = (long long) (b.y - a.y) * (d.x - c.x);
        long long y = (long long) (d.y - c.y) * (b.x - a.x);
        if (x == y) return 0;
        if (x > y) return 1;
        return -1;
    }
    inline static int determineCase(Node* n, point_t s, point_t t) {
        int leftAbove = 1;
        int rightAbove = 0;
        if ((n->prv != 0) && check(n->prv->key, n->key, s, t) < 0) {
            leftAbove = 0;
        }
        if ((n->nxt != 0) && check(n->key, n->nxt->key, s, t) > 0) {
            rightAbove = 1;
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
};

struct CNode {
    int isLeaf, color;
    CNode *left, *right, *lMax;
    point_t px;
    CQueue *uhull, *dhull;
    CNode(point_t p) {
        this->isLeaf = 1;
        this->color = BLACK;
        this->px = p;
        this->lMax = this;
        uhull = new CQueue(p);
        dhull = new CQueue(point_t(-p.x, -p.y));
    }
    CNode(CNode *lMax, CNode *left, CNode *right) {
        this->isLeaf = 0;
        this->color = RED;
        this->left = left;
        this->right = right;
        this->lMax = lMax;
        uhull = bridge(left->uhull, right->uhull);
        dhull = bridge(right->dhull, left->dhull);
    }
    CNode(point_t p, CNode *leftLeaf, CNode *rightLeaf) {
        //assert((leftLeaf == NULL || leftLeaf->isLeaf) && (rightLeaf == NULL || rightLeaf->isLeaf));
        this->isLeaf = 1;
        this->color = BLACK;
        this->px = p;
        this->left = leftLeaf;
        this->right = rightLeaf;
        this->lMax = this;
        uhull = new CQueue(p);
        dhull = new CQueue(point_t(-p.x, -p.y));
    }
};

struct DynamicConvexHull {
    CNode* root;
    DynamicConvexHull() {
        root = 0;
    }
    inline static void Down(CNode* n) {
        //assert(n != NULL);
        //assert(!n->isLeaf);
        n->left->uhull = concatenate(n->uhull->split(n->lMax->px, LEFT, 1), n->left->uhull);
        n->right->uhull = concatenate(n->right->uhull, n->uhull);
        n->right->dhull = concatenate(n->dhull->split(point_t(-n->lMax->px.x, -n->lMax->px.y), LEFT, 0), n->right->dhull);
        n->left->dhull = concatenate(n->left->dhull, n->dhull);
    }
    inline static void Up(CNode* n) {
        //assert(n != NULL);
        //assert(!n->isLeaf);
        n->uhull = bridge(n->left->uhull, n->right->uhull);
        n->dhull = bridge(n->right->dhull, n->left->dhull);
    }
    inline static CNode* rotateLeft(CNode* n) {
        //assert(n != NULL);
        //assert(!n->isLeaf && !n->right->isLeaf && n->right->color == RED);
        Down(n);
        CNode* tempCNode = n->right;
        int tempColor = n->color;
        Down(tempCNode);
        n->right = tempCNode->left;
        n->color = tempCNode->color;
        Up(n);
        tempCNode->left = n;
        tempCNode->color = tempColor;
        Up(tempCNode);
        return tempCNode;
    }
    inline static CNode* rotateRight(CNode* n) {
        //assert(n != NULL);
        //assert(!n->isLeaf && !n->left->isLeaf && n->left->color == RED);
        Down(n);
        CNode* tempCNode = n->left;
        int tempColor = n->color;
        Down(tempCNode);
        n->left = tempCNode->right;
        n->color = tempCNode->color;
        Up(n);
        tempCNode->right = n;
        tempCNode->color = tempColor;
        Up(tempCNode);
        return tempCNode;
    }
    inline CNode* addLeaf(point_t p, CNode* nLeft, CNode* nRight) {
        return new CNode(p);
    }
    inline void removeLeaf(CNode* n) {
    }
    inline static void flipTripleColor(CNode* n) {
        //assert(n != NULL);
        //assert(!n->isLeaf && !n->left->isLeaf && !n->right->isLeaf);
        n->color = !n->color;
        n->left->color = !n->left->color;
        n->right->color = !n->right->color;
    }
    inline static CNode* fixUp(CNode* n) {
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
    inline CNode* insertAt(CNode* n, point_t p) {
        //assert(n != NULL);
        if (p <= n->lMax->px) {
            if (n->isLeaf) {
                if (p == n->px) {
                }
                else {
                    CNode* nNew = addLeaf(p, n->left, n);
                    n = new CNode(nNew, nNew, n);
                }
            }
            else {
                Down(n);
                n->left = insertAt(n->left, p);
                Up(n);
            }
        }
        else {
            if (n->isLeaf) {
                CNode* nNew = addLeaf(p, n, n->right);
                n = new CNode(n, n, nNew);
            }
            else {
                Down(n);
                n->right = insertAt(n->right, p);
                Up(n);
            }
        }
        n = fixUp(n);
        return n;
    }
    inline CNode* deleteAt(CNode* n, point_t p) {
        //assert(n != NULL);
        //assert(!n->isLeaf);
        //assert(n->color == RED || n->left->color == RED);
        if (p <= n->lMax->px) {
            if (n->left->isLeaf) {
                if (p != n->left->px) {
                    return n;
                }
                else {
                    //assert(n->color == RED);
                    //assert(n->right->isLeaf);
                    Down(n);
                    removeLeaf(n->left);
                    return n->right;
                }
            }
            Down(n);
            if (p == n->lMax->px) {
                //assert(!n->left->isLeaf);
                CNode* tempCNode = n->left;
                while (!tempCNode->right->isLeaf) {
                    tempCNode = tempCNode->right;
                }
                n->lMax = tempCNode->lMax;
            }
            if (n->left->color == RED || n->left->left->color == RED) {
                n->left = deleteAt(n->left, p);
                Up(n);
            }
            else {
                //assert(!n->right->isLeaf);
                flipTripleColor(n);
                n->left = deleteAt(n->left, p);
                if (n->left->color == RED) {
                    Up(n);
                    flipTripleColor(n);
                }
                else if (n->right->left->color == BLACK) {
                    Up(n);
                    n = rotateLeft(n);
                }
                else {
                    n->right = rotateRight(n->right);
                    Up(n);
                    n = rotateLeft(n);
                    flipTripleColor(n);
                }
            }
        }
        else {
            if (n->right->isLeaf) {
                if (p != n->right->px) {
                    return n;
                }
                else {
                    Down(n);
                    removeLeaf(n->right);
                    n->left->color = BLACK;
                    return n->left;
                }
            }
            else if (n->right->left->color == RED) {
                Down(n);
                n->right = deleteAt(n->right, p);
                Up(n);
            }
            else if (n->color == RED) {
                //assert(n->left->color == BLACK);
                flipTripleColor(n);
                Down(n);
                n->right = deleteAt(n->right, p);
                Up(n);
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
                Down(n);
                n->right = deleteAt(n->right, p);
                Up(n);
                if (n->right->color == RED) {
                    n = rotateLeft(n);
                }
            }
        }
        return n;
    }
    inline void insert(point_t p) {
        if (root == 0) {
            root = new CNode(p);
        }
        else {
            root = insertAt(root, p);
            if (root->color == RED) {
                root->color = BLACK;
            }
        }
    }
    inline void remove(point_t p) {
        if (root == 0) {
            return;
        }
        else if (root->isLeaf) {
            if (p == root->px) {
                root = 0;
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
    long long Area2() {
        if (root == 0) {
            return 0;
        }
        long long res = 0;
        if (root->uhull != 0 && root->uhull->root != 0) {
            res += root->uhull->root->sumcross;
        }
        if (root->dhull != 0 && root->dhull->root != 0) {
            res += root->dhull->root->sumcross;
        }
        return abs(res);
    }
};

int main() {
    DynamicConvexHull con;
    int seed = 0;
    for (int i = 0; i < 1000; i++) {
        seed = (seed * 1001 + 100621) % 999983;
        int u = seed & ((1 << 16) - 1);
        seed = (seed * 1001 + 100621) % 999983;
        int v = seed & ((1 << 16) - 1);
        con.insert(point_t(u, v));
    }
    cout << con.Area2() << "\n"; //Expected 8433900701
    return 0;
}
