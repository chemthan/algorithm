#include <bits/stdc++.h>
using namespace std;

//O(n)
void lyndon(string s) {
	int n = s.size(), i = 0;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j]) k = i;
			else k++;
			j++;
		}
		while (i <= k) {
			cout << s.substr(i, j - k) << " ";
			i += j - k;
		}
	}
}

int main() {
	string s = "basdafswaer";
	lyndon(s); cout << "\n";
	return 0;
}
