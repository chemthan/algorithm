#include <bits/stdc++.h>
using namespace std;

//z[i] the length of the longest substr begins at i
const int maxn = 100010;
char S[maxn];
int n;
int z[maxn];
void zfunction() {
	int L = 0, R = 0;
	z[0] = n;
	for (int i = 1; i < n; i++) {
		if (i > R)
		{
			L = R = i;
			while (R < n && S[R] == S[R - L]) R++;
			z[i] = R - L; R--;
		}
		else
		{
			int k = i - L;
			if (z[k] < R - i + 1) z[i] = z[k];
			else
			{
				L = i;
				while (R < n && S[R] == S[R - L]) R++;
				z[i] = R - L; R--;
			}
		}
	}
}

int main() {
	strcpy(S, "stringsrandom");
	n = strlen(S);
	zfunction();
	for (int i = 0; i < n; i++) printf("%d ", z[i]);
	return 0;
}
