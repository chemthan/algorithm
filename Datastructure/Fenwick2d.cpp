#include <bits/stdc++.h>
using namespace std;

//Binary Indexed Tree 2D
//O(n(logn)^2)
const int maxx = 1010;
const int maxy = 1010;
int fen[maxx][maxy];
void add(int x , int y , int val) {
	int y1;
	while (x <= maxx){
		y1 = y;
		while (y1 <= maxy) {
			fen[x][y1] += val;
			y1 += y1 & -y1;
		}
		x += x & -x;
	}
}
int get(int x, int y) {
	int res = 0;
	while (x) {
		int y1 = y;
		while (y1) {
			res += fen[x][y1];
			y1 -= y1 & -y1;
		}
		x -= x & -x;
	}
	return res;
}

int main() {
    add(1, 1, 1);
    add(1, 2, 1);
    add(2, 1, 1);
    add(3, 3, 1);
    printf("%d", get(2, 2));
    return 0;
}
