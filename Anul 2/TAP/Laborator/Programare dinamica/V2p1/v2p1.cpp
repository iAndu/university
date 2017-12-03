#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first >= b.first;
}

int main() {
    vector< pair<int, int> > cubes;
    vector<int> best;
    vector<int> pre;
    int n, c, pozMax = 0, lMax = 1, nrTowers = 0;

    ifstream in("date.in");

    in >> n >> c;
    cubes.resize(n);
    best.resize(n);
    pre.resize(n);

    pair<int, int> e;
    for (auto it = cubes.begin(); it != cubes.end(); ++it) {
        in >> e.first >> e.second;
        *it = e;
    }

    in.close();

    sort(cubes.begin(), cubes.end(), cmp);

    for (int i = 0; i < n; ++i) {
        int maxim = 0;
        int save = -1;

        for (int j = 0; j < i; ++j) {
            if (cubes[j].second != cubes[i].second && cubes[j].first > cubes[i].first) {
                if (best[j] > maxim) {
                    maxim = best[j];
                    save = j;
                }
            }
        }

        best[i] = 1 + maxim;
        pre[i] = save;

        if (best[i] > lMax) {
            lMax = best[i];
            pozMax = i;
        }
    }

    ofstream out("date.out");

    do {
        out << cubes[pozMax].first << ' ' << cubes[pozMax].second << '\n';
        pozMax = pre[pozMax];
    } while (pozMax != -1);

    for (auto it = best.begin(); it != best.end(); ++it) {
        nrTowers += (*it == lMax ? 1 : 0);
    }

    out << nrTowers << '\n';

    out.close();

    return 0;
}