#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <iostream>

class Matrix;

class Complex
{
public:
    Complex(const double = 0, const double = 0);
    Complex(const Complex &);

    double GetReal() const;
    double GetImaginary() const;

    void SetReal(const double);
    void SetImaginary(const double);

    double Abs() const;
    Complex Exp(const Complex &, const int) const;
    Complex Conjugate() const;

    Complex operator+(const Complex &) const;
    Complex operator-(const Complex &) const;
    Complex operator*(const Complex &) const;
    Complex operator/(const Complex &) const;
    Complex operator%(const Complex &) const;
    Complex operator=(const Complex &);
    void operator+=(const Complex &);
    void operator-=(const Complex &);
    void operator*=(const Complex &);
    void operator/=(const Complex &);
    void operator%=(const Complex &);

    Matrix operator*(Matrix);

    Complex operator-() const;
    Complex operator+() const;

    bool operator!() const;
    bool operator==(const Complex &) const;
    bool operator!=(const Complex &) const;
    bool operator&&(const Complex &) const;
    bool operator||(const Complex &) const;

    friend std::ostream& operator<<(std::ostream &, const Complex &);
    friend std::istream& operator>>(std::istream &, Complex &);

private:
    double m_real, m_imaginary;

};

#endif // COMPLEX_H_INCLUDED
