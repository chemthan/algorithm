#include <bits/stdc++.h>
using namespace std;

#define RL long double
#define EPS 1e-9
const RL PI = acos((RL) -1.0);

RL sqr(const RL x) {return x * x;}
RL dist(RL x1, RL y1, RL x2, RL y2) {return sqrt(sqr(x1 - x2) + sqr(y1 - y2));}
RL angle(RL A, RL B, RL C) {return acos((sqr(A) + sqr(B) - sqr(C)) / (2 * A * B));}
int sign(RL x) {return x < -EPS ? -1 : x > EPS;}
int sign(RL x, RL y) {return sign(x - y);}

const int MAXN = 1e5 + 10;
int n;
RL x[MAXN], y[MAXN], r[MAXN];
int covered[MAXN];
vector<pair<RL, RL> > seg, cover;
RL arc, pol;

void getarea(int i, RL lef, RL rig) {
    arc += 0.5 * r[i] * r[i] * (rig - lef - sin(rig - lef));
    RL x1 = x[i] + r[i] * cos(lef), y1 = y[i] + r[i] * sin(lef);
    RL x2 = x[i] + r[i] * cos(rig), y2 = y[i] + r[i] * sin(rig);
    pol += x1 * y2 - x2 * y1;
}
int main() {
    srand(2311);
    n = 100;
    for (int i = 0; i < n; i++) {
        x[i] = rand(), y[i] = rand(), r[i] = rand();
        for (int j = 0; j < i; j++) {
            if (!sign(x[i] - x[j]) && !sign(y[i] - y[j]) && !sign(r[i] - r[j])) {
                r[i] = 0.0;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && sign(r[j] - r[i]) >= 0 && sign(dist(x[i], y[i], x[j], y[j]) - (r[j] - r[i])) <= 0) {
                covered[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (sign(r[i]) && !covered[i]) {
            seg.clear();
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    RL d = dist(x[i], y[i], x[j], y[j]);
                    if (sign(d - (r[j] + r[i])) >= 0 || sign(d - abs(r[j] - r[i])) <= 0) {
                        continue;
                    }
                    RL alpha = atan2(y[j] - y[i], x[j] - x[i]);
                    RL beta = angle(r[i], d, r[j]);
                    pair<RL, RL> tmp(alpha - beta, alpha + beta);
                    if (sign(tmp.first) <= 0 && sign(tmp.second) <= 0) {
                        seg.push_back(pair<RL, RL>(2 * PI + tmp.first, 2 * PI + tmp.second));
                    }
                    else if (sign(tmp.first) < 0) {
                        seg.push_back(pair<RL, RL>(2 * PI + tmp.first, 2 * PI));
                        seg.push_back(pair<RL, RL>(0, tmp.second));
                    }
                    else {
                        seg.push_back(tmp);
                    }
                }
            }
            sort(seg.begin(), seg.end());
            RL rig = 0;
            for (vector<pair<RL, RL> >::iterator iter = seg.begin(); iter != seg.end(); iter++) {
                if (sign(rig - iter->first) >= 0) {
                    rig = max(rig, iter->second);
                }
                else {
                    getarea(i, rig, iter->first);
                    rig = iter->second;
                }
            }
            if (!sign(rig)) {
                arc += r[i] * r[i] * PI;
            }
            else {
                getarea(i, rig, 2 * PI);
            }
        }
    }
    cout << fixed << setprecision(9) << pol / 2.0 + arc << "\n";
}
