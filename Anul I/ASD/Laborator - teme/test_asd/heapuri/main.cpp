#include <iostream>
#include <vector>
#define NMAX 10
using namespace std;

vector<int> heap(NMAX), position(NMAX), order(NMAX);

void sift(int nod, int len) {
    while (nod << 1 <= len) {
        int maxim = heap[nod << 1], poz = nod << 1;
        if ((nod << 1) + 1 <= len && heap[(nod << 1) + 1] > maxim) {
            poz = (nod << 1) + 1;
        }
        if (heap[nod] < heap[poz]) {
            swap(heap[nod], heap[poz]);
            swap(position[nod], position[poz]);
            swap(order[position[nod]], order[position[nod >> 1]]);
            nod = poz;
        }
    }
}

void percolate(int nod) {
    if (nod >> 1 && heap[nod] < heap[nod >> 1]) {
        swap(position[nod], position[nod >> 1]);
        swap(heap[nod], heap[nod >> 1]);
        swap(order[position[nod]], order[position[nod >> 1]]);
        percolate(nod >> 1);
    }
}

void delete_nod(int nod, int &len) {
    heap[nod] = heap[len];
    position[nod] = position[len];
    order[position[len]] = nod;
    --len;
    if (nod > 1 && heap[nod] > heap[nod >> 1]) {
        percolate(nod);
    } else {
        sift(nod, len);
    }
}

int main() {
    int n, len = 0;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x;
        if (x == 1) {
            cin >> y;
            heap[++len] = y;
            position[len] = len;
            order[len] = len;
            percolate(len);
        } else if (x == 2) {
            cin >> y;
            delete_nod(order[y], len);
        } else {
            cout << heap[1] << ' ';
        }
    }
    return 0;
}
