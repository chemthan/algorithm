#include <bits/stdc++.h>
using namespace std;

//O(nlogn)
int const MAXN = 100010;
int b[MAXN];
char T[MAXN];
char P[MAXN];
int nT, nP;
void preprocess() {
	int i = 0, j = -1; b[0] = -1;
	while (i < nP) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}
void search() {
	preprocess();
	int i = 0, j = 0;
	while (i < nT) {
		while (j >= 0 && T[i] != P[j]) j = b[j];
		i++; j++;
		if (j == nP) {
			printf("%d ", i - j);
			j = b[j];
		}
	}
}

int main() {
	strcpy(T, "123123123");
	strcpy(P, "123");
	nT = strlen(T); nP = strlen(P);
	search();
	return 0;
}
