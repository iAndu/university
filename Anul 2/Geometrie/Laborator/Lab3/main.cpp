#include <iostream>

using namespace std;

class Point {
public:
    double x, y;

    Point(double xi = 0, double yi = 0) : x(xi), y(yi) { }

    bool isCollinearWith(const Point &a, const Point &b) {
        return !(x * a.y + a.x * b.y + b.x * y - b.x * a.y - a.x * y - x * b.y);
    }

    friend istream& operator>>(istream &in, Point &obj) {
        in >> obj.x >> obj.y;

        return in;
    }

    friend ostream& operator<<(ostream &out, const Point &obj) {
        out << obj.x << ' ' << obj.y;

        return out;
    }
};

double det(Point arr[4]) {
    return (arr[1].y - arr[0].y) * (arr[2].x - arr[3].x) -
            (arr[0].x - arr[1].x) * (arr[3].y - arr[2].y);
}

int main() {
    Point arr[4];
    Point sol;

    double a[2], b[2], c[2];

    for (int i = 0; i < 4; ++i) {
        cin >> arr[i];
    }

    a[0] = arr[1].y - arr[0].y;
    a[1] = arr[3].y - arr[2].y;

    b[0] = arr[0].x - arr[1].x;
    b[1] = arr[2].x - arr[3].x;

    c[0] = arr[1].x * arr[0].y - arr[0].x * arr[1].y;
    c[1] = arr[3].x * arr[2].y - arr[2].x * arr[3].y;

    cout << a[0] << ' ' << a[1] << ' ' << b[0] << ' ' << b[1] << ' ' << c[0] << ' ' << c[1] << endl;

    double deter = det(arr);

    if (deter) {
        sol.x = (-c[0] * b[1] + b[0] * c[1]) / deter;
        sol.y = (a[0] * -c[1] + c[0] * a[1]) / deter;

        if (sol.x >= min(arr[0].x, arr[1].x) && sol.x <= max(arr[0].x, arr[1].x) &&
            sol.y >= min(arr[0].y, arr[1].y) && sol.y <= max(arr[0].y, arr[1].y) &&
            sol.x >= min(arr[2].x, arr[3].x) && sol.x <= max(arr[2].x, arr[3].x) &&
            sol.y >= min(arr[2].y, arr[3].y) && sol.y <= max(arr[2].y, arr[3].y)) {
                cout << sol << '\n';
        } else {
            cout << "Multime vida\n";
        }
    } else if (arr[1].isCollinearWith(arr[2], arr[3])) {
        if (min(arr[0].x, arr[1].x) < min(arr[2].x, arr[3].x) &&
                   max(arr[0].x, arr[1].x) > max(arr[2].x, arr[3].x)) {
                    cout << (arr[2].x < arr[3].x ? arr[2] : arr[3]) << ' ' <<
                        (arr[2].x > arr[3].x ? arr[2] : arr[3]) << '\n';
       } else if (min(arr[0].x, arr[1].x) > min(arr[2].x, arr[3].x) &&
                   max(arr[0].x, arr[1].x) < max(arr[2].x, arr[3].x)) {
                    cout << (arr[0].x < arr[1].x ? arr[0] : arr[1]) << ' ' <<
                        (arr[0].x > arr[1].x ? arr[0] : arr[1]) << '\n';
       } else if (max(arr[0].x, arr[1].x) > min(arr[2].x, arr[3].x) &&
            max(arr[0].x, arr[1].x) < max(arr[2].x, arr[3].x)) {
            cout << (arr[2].x < arr[3].x ? arr[2] : arr[3]) << ' ' <<
                (arr[0].x > arr[1].x ? arr[0] : arr[1]) << '\n';
        } else if (min(arr[0].x, arr[1].x) < max(arr[2].x, arr[3].x) &&
                   min(arr[0].x, arr[1].x) > min(arr[2].x, arr[3].x)) {
            cout << (arr[0].x < arr[1].x ? arr[0] : arr[1]) << ' ' <<
                (arr[2].x > arr[3].x ? arr[2] : arr[3]) << '\n';
        } else {
            cout << "Multime vida\n";
        }
    } else {
        cout << "Multime vida\n";
    }

    return 0;
}
