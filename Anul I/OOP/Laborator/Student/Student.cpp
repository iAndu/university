#include "Student.h"
#include <cstring>
#include <iostream>

using namespace std;

Student::Student() : m_pName(nullptr), m_age(-1), m_length(0) {
    cout << "Constructor default\n";
}

Student::Student (const char *name, int len, int age) : m_age(age), m_length(len) {
    cout << "Constructor\n";
    m_pName = new char[len];
    memcpy(m_pName, name, len * sizeof(char));
}

Student::Student (const Student &obj) : m_age(obj.m_age), m_length(obj.m_length) {
    cout << "Constructor copiere\n";
    m_pName = new char[m_length];
    memcpy(m_pName, obj.m_pName, m_length * sizeof(char));
}

Student::~Student() {
    cout << "Desturctor\n";
    delete[] m_pName;
}

Student& Student::operator= (const Student &obj) {
    if (&obj != this) {
        cout << "Assignment constructor\n";
        if (m_length != obj.m_length && obj.m_length > 0) {
            delete[] m_pName;
            m_pName = new char[obj.m_length];
        }
        if (obj.m_length > 0) {
            memcpy(m_pName, obj.m_pName, m_length * sizeof(char));
        }
        m_age = obj.m_age;
        m_length = obj.m_length;
    }
    return *this;
}

ostream& operator<< (ostream &out, const Student &obj) {
    out << "Nume " << obj.m_pName << '\n';
    out << "Varsta " << obj.m_age << '\n';

    return out;
}
