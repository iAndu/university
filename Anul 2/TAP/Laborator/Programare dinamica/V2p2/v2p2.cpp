/*
    Relatie de recurenta - Stim cu siguranta ca robotul nostru poate veni doar
    dintr-o celula de mai jos sau de la stanga, astfel ca vom calcula profitul
    parcurgand matricea de jos in sus si de la stanga la dreapta, calculand
    profitul maxim pe care il putem obtine printr-un drum pana in coltul din
    dreapta sus
*/

#include <fstream>
#include <vector>

using namespace std;

ofstream out("date.out");

// Matrix where each cell has a value and the precedent cell coordinates
vector< vector< pair<int, pair<int, int> > > > matrix;

void print(const pair<int, int> &poz) {
    if (matrix[poz.first][poz.second].second != make_pair(-1, -1)) {
        print(matrix[poz.first][poz.second].second);
    }

    // + 1 because lines are 0-indexed, where columns are 1-indexed because of bordering
    out << poz.first + 1 << ' ' << poz.second << '\n';
}

int main() {
    int n, m;

    ifstream in("date.in");
    
    in >> n >> m;
    // Border with a bottom line
    matrix.resize(n + 1);

    for (auto it = matrix.begin(); it != matrix.end() - 1; ++it) {
        // Border with a left column
        it->resize(m + 1, make_pair(0, make_pair(-1, -1)));

        for (auto jt = it->begin() + 1; jt != it->end(); ++jt) {
            in >> jt->first;
        }
    }
    matrix.rbegin()->resize(m + 1, make_pair(0, make_pair(-1, -1)));

    in.close();

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 1; j <= m; ++j) {
            if (matrix[i][j].first + matrix[i][j - 1].first >= matrix[i][j].first + matrix[i + 1][j].first) {
                matrix[i][j].first += matrix[i][j - 1].first;
                matrix[i][j].second = make_pair(i, j - 1);
            } else {
                matrix[i][j].first += matrix[i + 1][j].first;
                matrix[i][j].second = make_pair(i + 1, j);
            }
        }
    }

    matrix[n - 1][1].second = make_pair(-1, -1);

    out << matrix[0][m].first << '\n';
    print(make_pair(0, m));

    out.close();

    return 0;
}