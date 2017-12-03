#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, m;
    priority_queue< int, vector<int>, greater<int> > min_heap;
    priority_queue< int, vector<int> > max_heap;

    cin >> n >> m;
    int x;
    for (int i = 0; i < m; ++i) {
        cin >> x;
        min_heap.push(x);
        max_heap.push(x);
    }

    int sum_max = 0, sum_min = 0, top;
    for (int i = 0; i < n; ++i) {
        sum_max += max_heap.top();
        sum_min += min_heap.top();
        top = max_heap.top() - 1;
        max_heap.pop();
        if (top) {
            max_heap.push(top);
        }
        top = min_heap.top() - 1;
        min_heap.pop();
        if (top) {
            min_heap.push(top);
        }
    }

    cout << sum_max << ' ' << sum_min << '\n';

    return 0;
}
