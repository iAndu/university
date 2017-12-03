#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    /*Complex a, b(1, -2);

    cout << a + b << '\n';
    a.SetReal(1);
    a.SetImaginary(1);
    cout << a + b << '\n';
    cout << a - b << '\n';
    cout << a * b << '\n';
    cout << a / b << '\n';
    a = Complex(2, -5);
    b = a;
    a /= b;
    cout << a << '\n';
    cout << a.GetReal() << ' ' << a.GetImaginary() << '\n';

    Complex c, d;
    cin >> c >> d;
    cout << c << d;

    Matrix a = Matrix(3, 3, Complex(1, 1));
    cout << a;
    Matrix b;
    cout << b;
    b = a;
    cout << b;
    Matrix c(3, 3, Complex(-3, 2));
    b = c;
    cout << b;
    cout << a + b;
    cout << a - b;
    a(0, 0) = a(2, 1) = a(2, 2) = a(1, 2) = 2;
    a(0, 1) = 4; a(0, 2) = 8; a(1, 0) = 3; a(1, 1) = 1;
    a(2, 0) = 6;
    cout << a.Determinant();
    cout << a.Invert() << '\n';
    cout << a * a.Invert() << '\n';*/

    const Matrix a(3, 3, Complex(1, 1));
    Complex b;
    b = a(0, 0);

    return 0;
}
