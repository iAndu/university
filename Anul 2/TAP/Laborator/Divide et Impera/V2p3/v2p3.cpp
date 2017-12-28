/*
    Complexitate - Se folosesc partitionari de quick sort pana in momentul
    in care in stanga si in dreapta pivotului obtin valorile necesare.
*/

#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define NMAX 0.5

using namespace std;

vector< pair<int, double> > vec;

int partition(
    vector< pair<int, double> >::iterator left, 
    vector< pair<int, double> >::iterator right
    ) {
    
    int poz = rand() % (right - left + 1);
    vector< pair<int, double> >::iterator pivot = left + poz;
    vector< pair<int, double> >::iterator lt = left, rt = right;
    int pivotValue = pivot->first;

    while (lt <= rt) {
        while (lt->first < pivotValue) {
            ++lt;
        }

        while (rt->first > pivotValue) {
            --rt;
        }

        if (lt <= rt) {
            swap(*lt, *rt);
            ++lt;
            --rt;
        }
    }

    double sumLeft = 0, sumRight = 0;

    for (auto i : vec) {
        if (i.first < pivotValue) {
            sumLeft += i.second;
        } else if (i.first > pivotValue) {
            sumRight += i.second;
        }
    }

    if (sumLeft < NMAX && sumRight <= NMAX) {
        return pivotValue;
    } else if (sumLeft >= NMAX) {
        return partition(left, rt);
    } else {
        return partition(lt, right);
    }
}

int main() {
    int n;
    vector<int> x;
    vector<double> w;

    ifstream in("date.in");
    in >> n;
    x.resize(n);
    w.resize(n);
    vec.resize(n);

    for (int i = 0; i < n; ++i) {
        int e;
        in >> e;
        x[i] = e;
    }

    for (int i = 0; i < n; ++i) {
        double e;
        in >> e;
        w[i] = e;
    }

    for (int i = 0; i < n; ++i) {
        vec[i] = make_pair(x[i], w[i]);
    }

    srand(time(NULL));

    int xk = partition(vec.begin(), vec.end() - 1);

    ofstream out("date.out");
    out << xk << '\n';
    out.close();

    return 0;
}