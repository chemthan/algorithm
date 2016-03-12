#include <bits/stdc++.h>
using namespace std;

//O(nlogn)
const int MAXN = 100010;
char T[MAXN];
int nlen;
int RA[MAXN], tempRA[MAXN];
int SA[MAXN], tempSA[MAXN];
int c[MAXN];
int Phi[MAXN], PLCP[MAXN];
int LCP[MAXN];
void countingsort(int k) {
	int sum = 0, maxi = max(300, nlen);
	memset(c, 0, sizeof(c));
	for (int i = 0; i < nlen; i++) c[i + k < nlen ? RA[i + k] : 0]++;
	for (int i = 0; i < maxi; i++) {
		int t = c[i]; c[i] = sum; sum += t;
	}
	for (int i = 0; i < nlen; i++) tempSA[c[SA[i] + k < nlen ? RA[SA[i] + k] : 0]++] = SA[i];
	for (int i = 0; i < nlen; i++) SA[i] = tempSA[i];
}
void constructSA() {
	int r;
	for (int i = 0; i < nlen; i++) RA[i] = T[i];
	for (int i = 0; i < nlen; i++) SA[i] = i;
	for (int k = 1; k < nlen; k <<= 1) {
		countingsort(k);
		countingsort(0);
		tempSA[SA[0]] = r = 0;
		for (int i = 1; i < nlen; i++) tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
		for (int i = 0; i < nlen; i++) RA[i] = tempRA[i];
		if (RA[SA[nlen - 1]] == nlen - 1) break;
	}
}
void computeLCP() {
	int L = 0;
	Phi[SA[0]] = -1;
	for (int i = 1; i < nlen; i++) Phi[SA[i]] = SA[i - 1];
	for (int i = 0; i < nlen; i++) {
		if (Phi[i] == -1) {PLCP[i] = 0; continue;}
		while (T[i + L] == T[Phi[i] + L]) L++;
		PLCP[i] = L;
		L = max(L - 1, 0);
	}
	for (int i = 0; i < nlen; i++) LCP[i] = PLCP[SA[i]];
}

int main() {
	memset(T, 0, sizeof(T));
	strcpy(T, "stringsrandom");
	nlen = strlen(T);
	T[nlen++] = '$';
	constructSA(); computeLCP();
	for (int i = 0; i < nlen; i++) cout<<SA[i]<<" "; cout<<"\n";
	for (int i = 0; i < nlen; i++) cout<<RA[i]<<" "; cout<<"\n";
	for (int i = 0; i < nlen; i++) cout<<LCP[i]<<" "; cout<<"\n";
	return 0;
}
