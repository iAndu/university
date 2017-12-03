#include <iostream>
#include <vector>
using namespace std;

vector<int> vec;

void merge_sort(int st, int dr) {
    if (st == dr) { // Daca e un singur element
        return;
    }
    int mij = st + ((dr - st) >> 1);
    merge_sort(st, mij); // Sorteaza stanga
    merge_sort(mij + 1, dr); // Sorteaza dreapta

    vector<int> aux;
    int i = st, j = mij + 1;
    while (i <= mij || j <= dr) { // Interclaseaza
        if (j > dr || vec[i] <= vec[j]) {
            aux.push_back(vec[i++]);
        } else if (i > mij || vec[j] <= vec[i]) {
            aux.push_back(vec[j++]);
        }
    }
    for (int i = 0; i < aux.size(); ++i) {
        vec[st + i] = aux[i];
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        vec.push_back(x);
    }

    merge_sort(0, n - 1);

    for (int i = 0; i < n; ++i) {
        cout << vec[i] << ' ';
    }

    return 0;
}
