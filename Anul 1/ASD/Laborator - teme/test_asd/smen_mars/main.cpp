#include <iostream>
#include <vector>
using namespace std;

vector<int> vec, mars(100);

int main() {
    int n, m;

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        vec.push_back(x);
    }

    for (int i = 0; i < m; ++i) {
        int st, dr, x;
        cin >> st >> dr >> x;
        mars[st - 1] += x;
        mars[dr] -=x;
    }

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += mars[i];
        cout << vec[i] + sum << ' ';
    }

    return 0;
}
