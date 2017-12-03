#include <iostream>
#include <cstring>

using namespace std;

int** create_automata() {
    int **a = new int*[6];
    for (int i = 0; i < 6; ++i) {
        a[i] = new int[3];
    }
    a[0][0] = 2;
    a[0][1] = 1;
    a[0][2] = -1;

    a[1][0] = a[1][2] = -1;
    a[1][1] = 2;

    a[2][0] = a[2][1] = -1;
    a[2][2] = 3;

    a[3][0] = 3;
    a[3][1] = 4;
    a[3][2] = 5;

    a[4][0] = a[4][1] = a[4][2] = -1;

    a[5][0] = a[5][1] = a[5][2] = -1;

    return a;
}

bool check_word(int **formula, string word) {
    int state = 0;
    for (unsigned int i = 0; i < word.length(); ++i) {
        state = formula[state][word[i] - 'a'];
        if (state == -1) {
            return false;
        }
    }

    return (state == 4 || state == 5);
}

int main() {
    int **formula = create_automata();

    cout << "Introduceti cuvantul: ";
    string word;
    cin >> word;

    if (check_word(formula, word)) {
        cout << "Cuvantul este acceptat!\n";
    } else {
        cout << "Cuvantul nu este acceptat!\n";
    }

    return 0;
}
