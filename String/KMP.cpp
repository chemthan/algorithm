#include <bits/stdc++.h>
using namespace std;

int const MAXN = 100000 + 10;
struct KMP {
	char s[MAXN];
	int nsz, link[MAXN];
	void init(char* str) {
		strcpy(s, str); nsz = strlen(s);
		int cur = link[0] = -1;
		for (int i = 1; i < nsz; i++) {
			while (cur >= 0 && s[i] != s[cur + 1]) cur = link[cur];
			if (s[i] == s[cur + 1]) cur++;
			link[i] = cur;
		}
	}
	vector<int> search(char* t) {
		vector<int> res;
		int k = strlen(t);
		int cur = -1;
		for (int i = 0; i < k; i++) {
			while (cur >= 0 && t[i] != s[cur + 1]) cur = link[cur];
			if (t[i] == s[cur + 1]) cur++;
			if (cur == nsz - 1) {
				res.push_back(i - nsz + 1);
				cur = link[cur];
			}
		}
		return res;
	}
};

KMP kmp;

int main() {
	kmp.init("123123");
	vector<int> res = kmp.search("412312312312312312341231231231234");
	for (int i = 0; i < res.size(); i++) cout<<res[i] << " "; cout << "\n"; //Expected 1 4 7 10 13 20 23 26
	return 0;
}
