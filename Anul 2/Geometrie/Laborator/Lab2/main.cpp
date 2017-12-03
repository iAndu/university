#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#define NR_POINTS 4

using namespace std;

class Point {
public:
    double x, y;

    Point(double xm = 0, double ym = 0) : x(xm), y(ym) { }

    bool isCollinearWith(const Point &a, const Point &b) {
        return !(x * a.y + a.x * b.y + b.x * y - b.x * a.y - a.x * y - x * b.y);
    }
    int orientation(const Point &p1, const Point &p2) {
        double ort = (p1.y - y) * (p2.x - p1.x) - (p1.x - x) * (p2.y - p1.y);

        if (!ort) {
            return 0;
        }

        return ort > 0 ? 1 : -1;
    }
    double dist(const Point &p) {
        return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
    }

    Point operator-(const Point &p) {
        return Point(x - p.x, y - p.y);
    }

    friend istream& operator>>(istream &in, Point &obj) {
        in >> obj.x >> obj.y;

        return in;
    }
    friend ostream& operator<<(ostream &out, Point &obj) {
        out << '(' << obj.x << ", " << obj.y << ')';

        return out;
    }
};

Point p0;

bool cmp(const Point &p1, const Point &p2) {
    int ort = p0.orientation(p1, p2);

    if (!ort) {
        return p0.dist(p2) <= p0.dist(p1);
    }

    return ort == -1;
}

int main() {
    vector<Point> points(NR_POINTS);
    Point first(100000, 10000);
    int firstIndex;

    for (int i = 0; i < NR_POINTS; ++i) {
        Point p;

        cin >> p;
        points[i] = p;

        if (p.y < first.y || (p.y == first.y && p.x < first.x)) {
            first = p;
            firstIndex = i;
        }
    }

    if (points[0].isCollinearWith(points[1], points[2]) &&
        points[1].isCollinearWith(points[2], points[3])) {
            cout << "I = {" << points[0] << ", " << points[3] << "}\n";
            cout << "J = {" << points[1] << ", " << points[2] << "}\n";

            return 0;
    }

    swap(points[firstIndex], points[0]);

    p0 = points[0];

    sort(points.begin() + 1, points.end(), cmp);

    if (points[1].orientation(points[2], points[3]) != -1) {
        cout << "I = {" << points[0] << ", " << points[1] << ", " << points[3] << "}\n";
        cout << "J = {" << points[2] << "}\n";
    } else {
        cout << "I = {" << points[0] << ", " << points[2] << "}\n";
        cout << "J = {" << points[1] << ", " << points[3] << "}\n";
    }

    return 0;
}
