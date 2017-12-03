#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Element {
public:
    int pos, freq, length;

    friend istream& operator>>(istream &in, Element &obj) {
        in >> obj.freq >> obj.length;

        return in;
    }
};

bool cmp(const Element &a, const Element &b) {
    return a.length / a.freq < b.length / b.freq;
}

int main()
{
    int n;
    ifstream in("date.in");

    in >> n;
    vector<Element> texts(n);
    vector<int> perm(n + 1);

    for (auto it = texts.begin(); it != texts.end(); ++it) {
        Element text;

        in >> text;
        text.pos = it - texts.begin() + 1;
        *it = text;
    }

    in.close();

    sort(texts.begin(), texts.end(), cmp);

    for (auto it = texts.begin(); it != texts.end(); ++it) {
        perm[it->pos] = it - texts.begin() + 1;
    }

    ofstream out("date.out");

    for (auto it = perm.begin() + 1; it != perm.end(); ++it) {
        out << *it << ' ';
    }

    out << '\n';

    out.close();

    return 0;
}
