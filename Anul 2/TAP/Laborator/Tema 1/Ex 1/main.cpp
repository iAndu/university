#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Node {
public:
    int pos, length, color;
};

bool cmp(Node &x, Node &y) {
    return x.length > y.length;
}

int main() {
    ifstream in("date.in");
    ofstream out("date.out");
    int n, p;
    vector<Node> vec;

    in >> n >> p;
    for (int i = 0; i < n; ++i) {
        Node x;

        in >> x.length >> x.color;
        x.pos = i + 1;
        vec.push_back(x);
    }

    sort(vec.begin(), vec.end(), cmp);
    int last_color = vec.front().color;
    int height = vec.front().length;
    queue<int> que;

    que.push(vec.front().pos);

    for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
        if (it->color != last_color) {
            last_color = it->color;
            height += it->length;
            que.push(it->pos);
        }
    }

    out << height << '\n';
    while (!que.empty()) {
        out << que.front() << ' ';
        que.pop();
    }

    out << '\n';
    in.close();
    out.close();

    return 0;
}
