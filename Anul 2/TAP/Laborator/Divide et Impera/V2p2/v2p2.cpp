/*
    Complexitate - la fiecare moment pun o piesa, dupa care impart problema
    in patru sub-probleme identice, repetand procedeul pana la table de o
    singura gaura => 2^n * 2^n operatii
*/

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Point {
public:
    int x, y;

    Point(const int mx = 0, const int my = 0) : x(mx), y(my) { }

    friend istream& operator>>(istream &in, Point &obj) {
        in >> obj.x >> obj.y;

        return in;
    }
};

vector< vector<int> > table;

void partition(const Point &corner, const int n, const Point &hole) {
    static int pieceNo = 1;

    if (!n) {
        return;
    }

    unsigned long long half = 1 << (n - 1);

    // Left side of the table
    if (hole.x < corner.x + half) {
        // Upper side
        if (hole.y < corner.y + half) {
            Point rightUp = Point(corner.x + half, corner.y + half - 1);
            Point leftDown = Point(corner.x + half - 1, corner.y + half);
            Point rightDown = Point(corner.x + half, corner.y + half);

            table[rightUp.x][rightUp.y] = pieceNo;
            table[rightDown.x][rightDown.y] = pieceNo;
            table[leftDown.x][leftDown.y] = pieceNo;

            ++pieceNo;

            // Left up
            partition(corner, n - 1, hole);
            // Right up
            partition(Point(corner.x + half, corner.y), n - 1, rightUp);
            // Right down
            partition(Point(corner.x + half, corner.y + half), n - 1, rightDown);
            // Left down
            partition(Point(corner.x, corner.y + half), n - 1, leftDown);
        
        // Lower side
        } else {
            Point leftUp = Point(corner.x + half - 1, corner.y + half - 1);
            Point rightUp = Point(corner.x + half, corner.y + half - 1);
            Point rightDown = Point(corner.x + half, corner.y + half);

            table[leftUp.x][leftUp.y] = pieceNo;
            table[rightUp.x][rightUp.y] = pieceNo;
            table[rightDown.x][rightDown.y] = pieceNo; 

            ++pieceNo;

            // Left up
            partition(corner, n - 1, leftUp);
            // Right up
            partition(Point(corner.x + half, corner.y), n - 1, rightUp);
            // Right down
            partition(Point(corner.x + half, corner.y + half), n - 1, rightDown);
            // Left down
            partition(Point(corner.x, corner.y + half), n - 1, hole);              
        }

    // Right side of the table
    } else {
        // Upper side
        if (hole.y < corner.y + half) {
            Point leftUp = Point(corner.x + half - 1, corner.y + half - 1);
            Point leftDown = Point(corner.x + half - 1, corner.y + half);
            Point rightDown = Point(corner.x + half, corner.y + half);

            table[leftUp.x][leftUp.y] = pieceNo;
            table[leftDown.x][leftDown.y] = pieceNo;
            table[rightDown.x][rightDown.y] = pieceNo;

            ++pieceNo;

            // Left up
            partition(corner, n - 1, leftUp);
            // Right up
            partition(Point(corner.x + half, corner.y), n - 1, hole);
            // Right down
            partition(Point(corner.x + half, corner.y + half), n - 1, rightDown);
            // Left down
            partition(Point(corner.x, corner.y + half), n - 1, leftDown);
        
        // Lower side
        } else {
            Point leftUp = Point(corner.x + half - 1, corner.y + half - 1);
            Point rightUp = Point(corner.x + half, corner.y + half - 1);
            Point leftDown = Point(corner.x + half - 1, corner.y + half);

            table[rightUp.x][rightUp.y] = pieceNo;
            table[leftUp.x][leftUp.y] = pieceNo;
            table[leftDown.x][leftDown.y] = pieceNo; 

            ++pieceNo;

            // Left up
            partition(corner, n - 1, leftUp);
            // Right up
            partition(Point(corner.x + half, corner.y), n - 1, rightUp);
            // Right down
            partition(Point(corner.x + half, corner.y + half), n - 1, hole);
            // Left down
            partition(Point(corner.x, corner.y + half), n - 1, leftDown);              
        }
    }
}

int main() {
    int n;
    Point hole;

    ifstream in("date.in");
    in >> n >> hole;
    in.close();

    table.resize(1 << n);
    for (auto it = table.begin(); it != table.end(); ++it) {
        it->resize(1 << n);
    }

    table[--hole.x][--hole.y] = 0;
    partition(Point(0, 0), n, hole);

    ofstream out("date.out");
    for (auto i : table) {
        for (auto j : i) {
            out << j << ' ';
        }
        out << '\n';
    }
    out.close();

    return 0;
}