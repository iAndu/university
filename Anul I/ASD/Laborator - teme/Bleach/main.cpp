#include <fstream>
#include <queue>
#include <iostream>
using namespace std;

struct compare
 {
   bool operator()(const long long& l, const long long& r)
   {
       return l > r;
   }
 };

int main() {
    priority_queue<long long, vector<long long>, compare> heap;
    int n, k;
    long long sum = 0, pov = 0;

    ifstream in("bleach.in");
    in >> n >> k;
    for (int i = 0; i < n; i++) {
        int x;
        in >> x;
        heap.push(x);
        if (i > k) {
            pov = max(pov, heap.top() - sum);
            sum += heap.top();
            heap.pop();
        }
    }
    in.close();

    while (!heap.empty()) {
            pov = max(pov, heap.top() - sum);
            sum += heap.top();
            heap.pop();
    }
    ofstream out("bleach.out");
    out << pov << '\n';
    out.close();

    return 0;
}
