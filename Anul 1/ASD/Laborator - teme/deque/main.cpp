#include <fstream>
#include <deque>
#include <vector>
using namespace std;

int main() {
    int n, k, i, x;
    long long sum = 0;
    vector<int> v;
    deque<int> deq;

    ifstream in("deque.in");
    in >> n >> k;
    for (i = 0; i < n; i++){
        in >> x;
        v.push_back(x);
    }
    in.close();

    for (i = 0; i < n; i++) {
        while (!deq.empty() && v[i] <= v[deq.back()]) {
            deq.pop_back();
        }
        deq.push_back(i);
        if (deq.front() == i - k) {
            deq.pop_front();
        }
        if (i >= k - 1) {
            sum += v[deq.front()];
        }
    }

    ofstream out("deque.out");
    out << sum << '\n';
    out.close();

    return 0;
}
