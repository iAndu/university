#include "Complex.h"
#include <cmath>
using namespace std;

/*
 *************************************************
 * CONSTRUCTORS / COPY-CONSTRUCTOR / DESTRUCTOR  *
 *************************************************
*/

Complex :: Complex(const double real, const double img) : m_real(real), m_imaginary(img) { }

Complex :: Complex(const Complex &obj) : m_real(obj.m_real), m_imaginary(obj.m_imaginary) { }






/*
 *****************
 * CLASS METHODS *
 *****************
*/

double Complex :: GetReal() const
{
    return this->m_real;
}

double Complex :: GetImaginary() const
{
    return this->m_imaginary;
}

void Complex :: SetReal(const double value)
{
    this->m_real = value;
}

void Complex :: SetImaginary(const double value)
{
    this->m_imaginary = value;
}

Complex Complex :: Conjugate() const
{
    return Complex(this->m_real, -this->m_imaginary);
}

double Complex :: Abs() const
{
    double a = this->m_real, b = this->m_imaginary;

    return sqrt(a * a + b * b);
}

Complex Complex :: Exp(const Complex &obj, const int exp) const
{
    Complex aux = obj;

    for (int i = 0; i < exp; ++i)
        aux *= obj;

    return aux;
}

double abs(const Complex &obj)
{
    double a = obj.GetReal(), b = obj.GetImaginary();

    return sqrt(a * a + b * b);
}

Complex pow(const Complex &obj, const int exp)
{
    Complex aux = obj;

    for (int i = 0; i < exp; ++i)
        aux *= obj;

    return aux;
}




/*
 *************************
 * OPERATORS OVERLOADING *
 *************************
*/

Complex Complex :: operator+(const Complex &obj) const
{
    return Complex(this->m_real + obj.m_real, this->m_imaginary + obj.m_imaginary);
}

Complex Complex :: operator-(const Complex &obj) const
{
    return Complex(this->m_real - obj.m_real, this->m_imaginary - obj.m_imaginary);
}

Complex Complex :: operator*(const Complex &obj) const
{
    double a = this->m_real, b = this->m_imaginary, c = obj.m_real, d = obj.m_imaginary;

    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex :: operator/(const Complex &obj) const
{
    double a = this->m_real, b = this->m_imaginary, c = obj.m_real, d = obj.m_imaginary;
    double nomitor = c * c + d * d;

    return Complex((a * c + b * d) / nomitor, (b * c - a * d) / nomitor);
}

Complex Complex :: operator%(const Complex &obj) const
{
    Complex aux = *this / obj;

    return Complex(aux.m_real - (int)aux.m_real, aux.m_imaginary - (int)aux.m_imaginary);
}

Complex Complex :: operator=(const Complex &obj)
{
    this->m_real = obj.m_real;
    this->m_imaginary = obj.m_imaginary;

    return *this;
}

void Complex :: operator+=(const Complex &obj)
{
    this->m_real += obj.m_real;
    this->m_imaginary += obj.m_imaginary;
}

void Complex :: operator-=(const Complex &obj)
{
    this->m_real -= obj.m_real;
    this->m_imaginary -= obj.m_imaginary;
}

void Complex :: operator*=(const Complex &obj)
{
    double a = this->m_real, b = this->m_imaginary, c = obj.m_real, d = obj.m_imaginary;

    this->m_real = a * c - b * d;
    this->m_imaginary = b * c + a * d;
}

void Complex :: operator/=(const Complex &obj)
{
    double a = this->m_real, b = this->m_imaginary, c = obj.m_real, d = obj.m_imaginary;
    double nomitor = c * c + d * d;

    this->m_real = (a * c + b * d) / nomitor;
    this->m_imaginary = (b * c - a * d) / nomitor;
}

void Complex :: operator%=(const Complex &obj)
{
    Complex aux = *this / obj;

    this->m_real = aux.m_real - (int)aux.m_real;
    this->m_imaginary = aux.m_imaginary - (int)aux.m_imaginary;
}

Complex Complex :: operator-() const
{
    return Complex(0, 0) - *this;
}

Complex Complex :: operator+() const
{
    return *this;
}

bool Complex :: operator!() const
{
    return (!this->m_real && !this->m_imaginary) ? true : false;
}

bool Complex :: operator==(const Complex &obj) const
{
    return (this->m_real == obj.m_real && this->m_imaginary == obj.m_imaginary) ? true : false;
}

bool Complex :: operator!=(const Complex &obj) const
{
    return (this->m_real != obj.m_real || this->m_imaginary != obj.m_imaginary) ? true : false;
}

/*
 * && OVERLOAD *
 ***************
 * Returns true if both numbers are not equal to '0+0i'
*/

bool Complex :: operator&&(const Complex &obj) const
{
    Complex aux;

    return (*this != aux && obj != aux) ? true : false;
}

/*
 * || OVERLOAD *
 ***************
 * Returns true if at least one number is not equal to '0+0i'
*/

bool Complex :: operator||(const Complex &obj) const
{
    Complex aux;

    return (*this != aux || obj != aux) ? true : false;
}

ostream& operator<<(ostream &out, const Complex &obj)
{
    out << obj.m_real;
    out << showpos << obj.m_imaginary << 'i' << noshowpos;

    return out;
}

istream& operator>>(istream &in, Complex &obj)
{
    in >> obj.m_real >> obj.m_imaginary;
    in.get();

    return in;
}
