#include "Matrix.h"
#define SIGN (((i + j) % 2) ? Complex(-1, -1) : Complex(1, 1))

using namespace std;

/*
 *************************************************
 * CONSTRUCTORS / COPY-CONSTRUCTOR / DESTRUCTOR  *
 *************************************************
*/

Matrix :: Matrix(const int nr_lines, const int nr_columns, const Complex &comp)
                : m_lines(nr_lines), m_columns(nr_columns)
{
    int nr = this->m_lines * this->m_columns;
    this->m_matrix = new Complex[nr];

    for (int i = 0; i < nr; ++i)
        this->m_matrix[i] = comp;
}

Matrix :: Matrix() : m_lines(0), m_columns(0) { }

Matrix :: Matrix(const Matrix &obj) : m_lines(obj.m_lines), m_columns(obj.m_columns)
{
    if (this->m_matrix != nullptr)
        delete[] this->m_matrix;

    int nr = this->m_lines * this->m_columns;
    this->m_matrix = new Complex[nr];

    for (int i = 0; i < nr; ++i)
        this->m_matrix[i] = obj.m_matrix[i];
}

Matrix :: ~Matrix()
{
    delete[] this->m_matrix;
}







/*
 *****************
 * CLASS METHODS *
 *****************
*/

int Matrix :: GetLines() const
{
    return this->m_lines;
}

int Matrix :: GetColumns() const
{
    return this->m_columns;
}

/*
 * SUBMATRIX *
 *************
 * Returns a matrix formed by all elements of caller,
 * except those on line 'li' or column 'lj'
 *
 * Params: li and lj with specified roles
*/
Matrix Matrix :: SubMatrix(const int li, const int lj) const
{
    Matrix aux = *this;
    Matrix obj(this->m_lines - 1, this->m_columns - 1);
    int line = 0, column = 0;

    for (int i = 0; i < this->m_lines; ++i)
        for (int j = 0; j < this->m_columns; ++j)
            if (i != li && j != lj)
            {
                obj(line, column++) = aux(i, j);
                
                if (column >= obj.m_columns)
                {
                    column = 0;
                    ++line;
                }
            }

    return obj;
}

/*
 * DETERMINANT *
 ***************
 * Return the determinant of a matrix
*/

Complex Matrix :: Determinant()
{
    Matrix obj = *this;

    if (obj.m_lines == 1 && obj.m_columns == 1)
        return obj(0, 0);
    else
    {
        Matrix aux;
        Complex sum;
        const int j = 0;

        for (int i = 0; i < obj.m_columns; ++i)
            sum += SIGN * obj(0, i) * obj.SubMatrix(0, i).Determinant();

        return sum;
    }
}

/*
 * TRANSPOSE *
 *************
 * Returns the transposed matrix
*/

Matrix Matrix :: Transpose()
{
    Matrix obj = *this;
    Matrix aux = obj;

    for (int i = 0; i < obj.m_lines; ++i)
        for (int j = 0; j < obj.m_columns; ++j)
            aux(j, i) = obj(i, j);

    return aux;
}

/*
 * COMPLEMENT *
 **************
 * Returns the complement of a matrix
*/

Matrix Matrix :: Complement()
{
    Matrix obj = *this;
    Matrix aux = obj.Transpose();

    for (int i = 0; i < obj.m_lines; ++i)
        for (int j = 0; j < obj.m_columns; ++j)
            (*this)(i, j) = SIGN * aux.SubMatrix(i, j).Determinant();

    return obj;
}

/*
 * INVERT *
 **********
 * Returns a matrix A' such as A * A' = In
*/

Matrix Matrix :: Invert()
{
    Complex det = this->Determinant();
    const double nomitor = det.GetReal() * det.GetReal() + det.GetImaginary() * det.GetImaginary();
    Complex coef(det.GetReal() / nomitor, -det.GetImaginary() / nomitor);

    return coef * this->Complement();
}




/*
 *************************
 * OPERATORS OVERLOADING *
 *************************
*/

/*
 * () OVERLOAD *
 ***************
 * Return the element at line 'i', column 'j'
 *
 * Params: 'i' and 'j' with the specified roles
*/

Complex& Matrix :: operator()(const int i, const int j) const
{
    return *(this->m_matrix + i * this->m_columns + j);
}

Matrix Matrix :: operator+(const Matrix &obj) const
{
    Matrix aux = *this;
    for (int i = 0; i < aux.m_lines; ++i)
        for (int j = 0; j < aux.m_columns; ++j)
            aux(i, j) += obj(i, j);

    return aux;
}

Matrix Matrix :: operator-(const Matrix &obj) const
{
    Matrix aux = *this;
    for (int i = 0; i < aux.m_lines; ++i)
        for (int j = 0; j < aux.m_columns; ++j)
            aux(i, j) -= obj(i, j);

    return aux;
}

Matrix Matrix :: operator*(const Matrix &obj) const
{
    Matrix aux(this->m_lines, obj.m_columns);

    for (int i = 0; i < aux.m_lines; ++i)
        for (int j = 0; j < aux.m_columns; ++j) 
        {
            Complex sum(0, 0);

            for (int k = 0; k < this->m_columns; ++k)
                sum += (*this)(i, k) * obj(k, j);

            aux(i, j) = sum;
        }

    return aux;
}

Matrix Matrix :: operator=(const Matrix &obj)
{
    if (this->m_matrix != nullptr)
        delete[] this->m_matrix;

    this->m_lines = obj.m_lines;
    this->m_columns = obj.m_columns;

    int nr = this->m_lines * this->m_columns;
    this->m_matrix = new Complex[nr];

    for (int i = 0; i < nr; ++i)
        this->m_matrix[i] = obj.m_matrix[i];

    return *this;
}

void Matrix :: operator+=(const Matrix &obj)
{
    for (int i = 0; i < this->m_lines; ++i)
        for (int j = 0; j < this->m_columns; ++j)
            (*this)(i, j) += obj(i, j);
}

void Matrix :: operator-=(const Matrix &obj)
{
    for (int i = 0; i < this->m_lines; ++i)
        for (int j = 0; j < this->m_columns; ++j)
            (*this)(i, j) -= obj(i, j);
}

void Matrix :: operator*=(const Matrix &obj)
{
    Matrix aux(this->m_lines, obj.m_columns);

    for (int i = 0; i < aux.m_lines; ++i)
        for (int j = 0; j < aux.m_columns; ++j)
        {
            Complex sum(0, 0);

            for (int k = 0; k < this->m_columns; ++k)
                sum += (*this)(i, k) * obj(k, j);

            aux(i, j) = sum;
        }

    *this = aux;
}

/*
 * * OVERLOAD *
 **************
 * Returns the matrix 'obj' multiplied by a complex number
*/

Matrix Complex :: operator*(Matrix obj)
{
    for (int i = 0; i < obj.GetLines(); ++i)
        for (int j = 0; j < obj.GetColumns(); ++j)
            obj(i, j) *= *this;

    return obj;
}

bool Matrix :: operator!() const
{
    Matrix aux(this->m_lines, this->m_columns);

    return (*this == aux) ? true : false;
}

bool Matrix :: operator==(const Matrix &obj) const
{
    if (this->m_lines != obj.m_lines || this->m_columns != obj.m_columns)
        return false;

    for (int i = 0; i < this->m_lines; ++i)
        for (int j = 0; j < this->m_columns; ++j)
            if ((*this)(i, j) != obj(i, j))
                return false;

    return true;
}

bool Matrix :: operator!=(const Matrix &obj) const
{
    if (this->m_lines != obj.m_lines || this->m_columns != obj.m_columns)
        return true;

    for (int i = 0; i < this->m_lines; ++i)
        for (int j = 0; j < this->m_columns; ++j)
            if ((*this)(i, j) != obj(i, j))
                return true;

    return false;
}

/*
 * && OVERLOAD *
 ***************
 * Return true if both matrix are not equal to the 0-matrix of their size
*/

bool Matrix :: operator&&(const Matrix &obj) const
{
    Matrix A(this->m_lines, this->m_columns);
    Matrix B(obj.m_lines, obj.m_columns);

    return (*this != A && obj != B) ? true : false;
}

/*
 * || OVERLOAD *
 ***************
 * Return true if at least one matrix is not equal to the 0-matrix of it's size
*/

bool Matrix :: operator||(const Matrix &obj) const
{
    Matrix A(this->m_lines, this->m_columns);
    Matrix B(obj.m_lines, obj.m_columns);

    return (*this != A || obj != B) ? true : false;
}

Matrix Matrix :: operator-() const
{
    return Matrix(this->m_lines, this->m_columns) - *this;
}

Matrix Matrix :: operator+() const
{
    return *this;
}

ostream& operator<<(ostream &out, const Matrix &obj)
{
    out << obj.m_lines << ' ' << obj.m_columns << '\n';

    for (int i = 0; i < obj.m_lines; ++i) 
    {
        for (int j = 0; j < obj.m_columns; ++j)
            out << obj(i, j) << ' ';

        out << '\n';
    }

    return out;
}

istream& operator>>(istream &in, Matrix &obj)
{
    in >> obj.m_lines >> obj.m_columns;

    for (int i = 0; i < obj.m_lines; ++i)
        for (int j = 0; j < obj.m_columns; ++j)
            in >> obj(i, j);

    return in;
}
