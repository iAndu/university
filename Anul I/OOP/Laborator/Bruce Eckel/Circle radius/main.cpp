#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

using namespace std;

#ifndef CIRCLE
#define CIRCLE
class Circle {
    double radius;

    public:
    Circle(double param = 0) {
        this->radius = param;
    }

    void SetRadius(double param) {
        this->radius = param;
    }

    double GetRadius() {
        return this->radius;
    }

    double GetArea() {
        return PI * this->radius * this->radius;
    }
};
#endif // Circle

int main() {
    double radius;
    Circle circle;

    cout << "Introduce circle radius: ";
    cin >> radius;
    circle.SetRadius(radius);

    cout << "Circle with radius " << circle.GetRadius() << " has area of " << circle.GetArea();

    return 0;
}
