#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "Complex.h"

class Matrix
{
public:
    Matrix(const int, const int, const Complex &comp = Complex(0, 0));
    Matrix();
    Matrix(const Matrix &);
    ~Matrix();

    int GetLines() const;
    int GetColumns() const;

    Matrix SubMatrix(const int, const int) const;
    Matrix Transpose();
    Matrix Complement();
    Matrix Invert();
    Complex Determinant();

    Complex& operator()(const int, const int) const;

    Matrix operator+(const Matrix &) const;
    Matrix operator-(const Matrix &) const;
    Matrix operator*(const Matrix &) const;
    Matrix operator=(const Matrix &);
    void operator+=(const Matrix &);
    void operator-=(const Matrix &);
    void operator*=(const Matrix &);

    Matrix operator-() const;
    Matrix operator+() const;

    bool operator!() const;
    bool operator==(const Matrix &) const;
    bool operator!=(const Matrix &) const;
    bool operator&&(const Matrix &) const;
    bool operator||(const Matrix &) const;

    friend std::ostream& operator<<(std::ostream &, const Matrix &);
    friend std::istream& operator>>(std::istream &, Matrix &);

private:
    int m_lines, m_columns;
    Complex *m_matrix = nullptr;

};

#endif // MATRIX_H_INCLUDED
