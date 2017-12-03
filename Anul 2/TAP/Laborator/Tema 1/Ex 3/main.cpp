#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Element {
public:
    int profit, pos, time;

    friend istream& operator>>(istream &in, Element &obj) {
        in >> obj.profit >> obj.time;

        return in;
    }
};

bool cmp(Element &a, Element &b) {
    if (a.time == b.time) {
        return a.profit > b.profit;
    }
    return a.time < b.time;
}

int main()
{
    int n;

    ifstream in("date.in");
    in >> n;
    vector<Element> actv(n);

    for (auto it = actv.begin(); it != actv.end(); ++it) {
        Element activity;

        in >> activity;

        activity.pos = it - actv.begin() + 1;
        *it = activity;
    }

    in.close();

    sort(actv.begin(), actv.end(), cmp);

    int time = 0, profit = 0;
    vector<int> chosen;

    for (auto i : actv) {
        if (i.time > time) {
            profit += i.profit;
            chosen.push_back(i.pos);
            ++time;
        }
    }

    ofstream out("date.out");
    out << profit << '\n';

    for (auto i : chosen) {
        out << i << ' ';
    }

    out << '\n';
    out.close();

    return 0;
}
