#include <bits/stdc++.h>
using namespace std;

const int MAXN = 7654321;
typedef int TKEY;
typedef int TVAL;
const TVAL NOTFOUND = -1;
struct HashMap {
	int cur, head[MAXN], next[MAXN];
	TKEY l[MAXN];
	TVAL x[MAXN];
	
	HashMap() {
		cur = 0; fill_n(head, MAXN, 0); fill_n(next, MAXN, 0);
	}
	TVAL find(TKEY key) {
		for (int i = head[key % MAXN]; i; i = next[i]) {
			if (l[i] == key) {
				return x[i];
			}
		}
		return NOTFOUND;
	}
	void insert(TKEY key, TVAL val) {
		if (find(key) != NOTFOUND) return;
		l[++cur] = key; x[cur] = val;
		next[cur] = head[key % MAXN];
		head[key % MAXN] = cur;
	}
} hm;

int main() {
	hm.insert(3234234, 4);
	hm.insert(4123123, 5);
	cout << hm.find(3234234) << "\n";
	cout << hm.find(4123123) << "\n";
	return 0;
}
