#include <fstream>
#include <vector>
#include <utility>
#define NMAX 500001
using namespace std;

vector<int> rsd, srd;
vector< pair<int, int> > arb(NMAX);
int poz;

int reconstruct(int st, int dr) {
    if (st > dr || dr < st) {
        return 0;
    }

    int el = rsd[poz];
    int i;
    for (i = st; i <= dr; ++i) {
        if (srd[i] == rsd[poz]) {
            break;
        }
    }
    poz++;
    arb[el].first = reconstruct(st, i - 1);
    arb[el].second = reconstruct(i + 1, dr);

    return el;
}

int main () {
    int n;

    ifstream in("curatenie.in");
    in >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        srd.push_back(x);
    }
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        rsd.push_back(x);
    }
    in.close();

    int mlc = reconstruct(0, n - 1);

    ofstream out("curatenie.out");
    for (int i = 1; i <= n; ++i) {
        out << arb[i].first << ' ' << arb[i].second << '\n';
    }
    out.close();

    return 0;
}
