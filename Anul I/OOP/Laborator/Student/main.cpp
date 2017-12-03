#include <iostream>
#include "Student.h"

using namespace std;

Student create_object() {
    Student obj("Calin", 6, 19);
    return obj;
}

void Print(const Student &obj) {
    cout << obj.m_age << '\n';
}

int main()
{
    Student Ion("Ion", 3, 20);
    Student Calin;
    Calin = create_object();
    Student Vasile;

    //Ion = Calin = Vasile;

    Print(Ion);

    cout << Ion << Calin;

    return 0;
}
