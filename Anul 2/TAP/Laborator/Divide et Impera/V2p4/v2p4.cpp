#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector< pair<int, int> > points;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

bool cmp2(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

double distance(pair<int, int> a, pair<int, int> b) {
    return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

double partition(
    vector< pair<int, int> >::iterator left,
    vector< pair<int, int> >::iterator right
    ) {
        
        if (right - left < 3) {
            double minim = 9999999999;

            for (auto it = left; it < right; ++it) {
                for (auto jt = it + 1; jt <= right; ++jt) {
                    minim = min(minim, distance(*it, *jt));
                }
            }
            
            return minim;
        }

        int half = (right - left + 1) / 2;
        double minim = min(partition(left, left + half), partition(left + half, right));
        pair<int, int> halfPoint = *(left + half);

        vector< pair<int, int> > y;
        for (auto it = left; it <= right; ++it) {
            if (distance(*it, make_pair(halfPoint.first, it->second)) <= minim) {
                y.push_back(*it);
            }
        }

        sort(y.begin(), y.end(), cmp2);

        double minim2 = 9999999999;
        for (auto it = y.begin(); it != y.end(); ++it) {
            for (auto jt = it + 1; jt != y.end() && jt - it <= 7; ++jt) {
                minim2 = min(minim2, distance(*it, *jt));
            }
        }

        return min(minim, minim2);
}

int main() {
    int n;

    ifstream in("cmap.in");
    in >> n;
    points.resize(n);

    for (auto it = points.begin(); it != points.end(); ++it) {
        pair<int, int> e;
        in >> e.first >> e.second;
        *it = e;
    }

    in.close();

    sort(points.begin(), points.end(), cmp);

    double minim = partition(points.begin(), points.end() - 1);

    ofstream out("cmap.out");
    out.precision(17);
    out << minim << '\n';
    out.close();

    return 0;
}