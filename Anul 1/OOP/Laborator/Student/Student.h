#include <cstring>
#include <iostream>
#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

// Forward declaration
class Nas;

class Student {

private:
    char *m_pName;
    int m_age, m_length;
    Nas *m_nas;

public:
    Student ();
    Student (const char*, int, int);
    ~Student ();
    Student (const Student &);

    inline const char* const GetName () { return m_pName; }
    inline void SetName (const char* const m_pName, const int len) {
        if (m_length != len) {
            delete[] this->m_pName;
            this->m_pName = new char[len + 1];
            m_length = len;
        }
        memcpy(this->m_pName, m_pName, m_length);
    }

    Student& operator= (const Student &);
    friend void Print (const Student&);
    friend std::ostream& operator<< (std::ostream &, const Student &);
};

#endif // STUDENT_H_INCLUDED
