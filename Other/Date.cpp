#include <bits/stdc++.h>
using namespace std;

string dayOfWeek[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
//converts Gregorian date to integer (Julian day number)
int dateToInt(int m, int d, int y) {
	return
	    1461 * (y + 4800 + (m - 14) / 12) / 4 +
	    367 * (m - 2 - (m - 14) / 12 * 12) / 12 -
	    3 * ((y + 4900 + (m - 14) / 12) / 100) / 4 +
	    d - 32075;
}
//converts Julian date to integer (Julian day number)
int dateToInt2(int m, int d, int y) {
	int a = (14 - m) / 12;
	int y2 = y + 4800 - a;
	int m2 = m + 12 * a - 3;
	return d + (153 * m2 + 2) / 5 + 365 * y2 + y2 / 4 - 32083;
}
//converts integer (Julian day number) to Gregorian date: month/day/year
void intToDate(int jd, int &m, int &d, int &y) {
	int x, n, i, j;

	x = jd + 68569;
	n = 4 * x / 146097;
	x -= (146097 * n + 3) / 4;
	i = (4000 * (x + 1)) / 1461001;
	x -= 1461 * i / 4 - 31;
	j = 80 * x / 2447;
	d = x - 2447 * j / 80;
	x = j / 11;
	m = j + 2 - 12 * x;
	y = 100 * (n - 49) + i + x;
}
//converts integer (Julian day number) to day of week
string intToDay(int jd) {
	return dayOfWeek[jd % 7];
}

int main() {
	return 0;
}
