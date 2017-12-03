#include <iostream>

using namespace std;

bool valid(int k, int n) {
    int desc = 1, total = 1;;
    for (int i = 2; i < k; ++i) {
        if (v[k] == 1) {
            ++desc;
            ++total;
        } else {
            --desc;
        }
    }
    if (v[k] == 1 && total == n) {
        return 0;
    }
    if (desc > 0) {
        return 1;
    }
    return 0;
}

void backt(int k, int n) {
    while (k <= n) {
        if (k == n + 1) {
            if (valid(k)) {
                scrie_sol();
            }
        } else if (v[k] < 2) {
            ++v[k];
            if (valid(k)) {
                ++k;
            }
        } else {
            v[k--] = 0;
        }
    }
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
