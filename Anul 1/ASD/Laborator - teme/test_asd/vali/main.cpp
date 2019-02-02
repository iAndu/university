#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct nod {
    int id;
    char keyword[100];
};

int main()
{
    nod mat[3];

    mat[0].id = 1;
    strcpy(mat[0].keyword, "unu");
    mat[1].id = 2;
    strcpy(mat[1].keyword, "doi");
    mat[2].id = 3;
    strcpy(mat[2].keyword, "trei");

    cout << "inainte de modificari\n";
    for (int i = 0; i < 3; ++i) {
        cout << mat[i].id << ' ' << mat[i].keyword << '\n';
    }

    ifstream in("fisier.in");
    char word[100];
    cout << "Dupa modificari\n";
    for (int i = 0; i < 3; ++i) {
        in >> word;
        strcpy(mat[i].keyword, word);
        cout << mat[i].id << ' ' << mat[i].keyword << '\n';
        in.get();
    }
    in.close();
    return 0;
}
