#include <bits/stdc++.h>
using namespace std;

//O(N + M)
int const MAXN = 100010;
int nP;
char P[MAXN];
int r[MAXN];
void KMP() {
	r[0] = -1;
	int cur = -1;
	for (int i = 0; i < nP; i++) {
		while (cur >= 0 && P[i] != P[cur]) cur = r[cur];
		r[i + 1] = ++cur;
	}
}
void search(char* T) {
	int nT = strlen(T), cur = 0;
	for (int i = 0; i < nT; i++) {
		while (cur >= 0 && T[i] != P[cur]) cur = r[cur];
		if (++cur == nP) {
			cout<<i - cur + 1<<" ";
		}
	}
}

int main() {
	strcpy(P, "123123");
	nP = strlen(P); KMP();
	search((char*) "412312312312312312341231231231234"); //Expect 1 4 7 10 13 20 23 26
	return 0;
}
