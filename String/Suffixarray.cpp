#include <bits/stdc++.h>
using namespace std;

//O(nlogn)
const int MAXN = 100010;
struct SuffixArray {
	char T[MAXN];
	int nsz;
	int RA[MAXN], tmpRA[MAXN];
	int SA[MAXN], tmpSA[MAXN];
	int c[MAXN];
	int Phi[MAXN], PLCP[MAXN];
	int LCP[MAXN];
	void init(char* str) {
		strcpy(T, str);
		nsz = strlen(T);
		for (int i = 0; i <= nsz; i++) {
			RA[i] = tmpRA[i] = 0;
			SA[i] = tmpSA[i] = 0;
			Phi[i] = PLCP[i] = LCP[i] = 0;
		}
		constructSA();
		computeLCP();
	}
	void countingsort(int k) {
		int sum = 0, maxi = max(300, nsz);
		memset(c, 0, sizeof(c));
		for (int i = 0; i < nsz; i++) c[i + k < nsz ? RA[i + k] : 0]++;
		for (int i = 0; i < maxi; i++) {
			int t = c[i]; c[i] = sum; sum += t;
		}
		for (int i = 0; i < nsz; i++) tmpSA[c[SA[i] + k < nsz ? RA[SA[i] + k] : 0]++] = SA[i];
		for (int i = 0; i < nsz; i++) SA[i] = tmpSA[i];
	}
	void constructSA() {
		int r;
		for (int i = 0; i < nsz; i++) RA[i] = T[i];
		for (int i = 0; i < nsz; i++) SA[i] = i;
		for (int k = 1; k < nsz; k <<= 1) {
			countingsort(k);
			countingsort(0);
			tmpSA[SA[0]] = r = 0;
			for (int i = 1; i < nsz; i++) tmpRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
			for (int i = 0; i < nsz; i++) RA[i] = tmpRA[i];
			if (RA[SA[nsz - 1]] == nsz - 1) break;
		}
	}
	void computeLCP() {
		int L = 0;
		Phi[SA[0]] = -1;
		for (int i = 1; i < nsz; i++) Phi[SA[i]] = SA[i - 1];
		for (int i = 0; i < nsz; i++) {
			if (!~Phi[i]) {PLCP[i] = 0; continue;}
			while (T[i + L] == T[Phi[i] + L]) L++;
			PLCP[i] = L;
			L = max(L - 1, 0);
		}
		for (int i = 0; i < nsz; i++) LCP[i] = PLCP[SA[i]];
	}
};

SuffixArray sa;

int main() {
	sa.init("stringsrandom$");
	for (int i = 0; i < sa.nsz; i++) cout<<sa.SA[i]<<" "; cout<<"\n";
	for (int i = 0; i < sa.nsz; i++) cout<<sa.RA[i]<<" "; cout<<"\n";
	for (int i = 0; i < sa.nsz; i++) cout<<sa.LCP[i]<<" "; cout<<"\n";
	return 0;
}
