#include <iostream>
#include <cstdlib>

using namespace std;

class Exemplu {
    int nr_cuv;
public:
    Exemplu(int param) {
        cout << "Constructor cu parametru\n";
        nr_cuv = param;
    }
    Exemplu() {
        cout << "Constructor default\n";
        nr_cuv = 0;
    }
    ~Exemplu() {
        cout << "Destructor\n";
    }
    int GetNrCuv() {
        return nr_cuv;
    }
    void SetNrCuv(int param) {
        nr_cuv = param;
    }
    void Increment(int param) {
        nr_cuv += param;
    }
};

int main()
{
    Exemplu a(5);

    //Exemplu *p = new Exemplu(5);
    Exemplu *p = (Exemplu*)malloc(sizeof(Exemplu));
    cout << p->GetNrCuv() << '\n';
    delete p;

    Exemplu vec[3] = { Exemplu(0), Exemplu(2), Exemplu(4) };
    //a.SetNrCuv(5);
    cout << a.GetNrCuv() << endl;
    for (int i = 0; i < 3; ++i) {
        cout << vec[i].GetNrCuv() << ' ';
    }
    cout << '\n' << (*(vec + 2)).GetNrCuv() << '\n';
    return 0;
}
