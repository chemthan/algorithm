#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int d[MAXN]; //Radius odd palindrome
int e[MAXN]; //Radius even palindrome
int manacher(char s[], int n) {
	int res = 0;
	int l = 0, r = -1;
	for (int i = 0; i < n; ++i) {
		int k = (i > r) ? 1 : min(d[l + r - i], r - i) + 1;
		while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
		d[i] = --k;
		res = max(res, k + k + 1);
		if (r < i + k) {
			l = i - k;
			r = i + k;
		}
	}
	l = 0; r = -1;
	for (int i = 0; i < n; ++i) {
		int k = (i > r) ? 1 : min(e[l + r - i + 1], r - i + 1) + 1;
		while (i - k >= 0 && i + k - 1 < n && s[i - k] == s[i + k - 1]) k++;
		e[i] = --k;
		res = max(res, k + k);
		if (r < i + k - 1) {
			l = i - k;
			r = i + k - 1;
		}
	}
	return res;
}

int main() {
	cout<<manacher("aaadefede", 9)<<"\n";
	for (int i = 0; i < 9; i++) {
		cout<<d[i]<<" ";
	}
	cout<<"\n";
	for (int i = 0; i < 9; i++) {
		cout<<e[i]<<" ";
	}
	cout<<"\n";
	return 0;
}
