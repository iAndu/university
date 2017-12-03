#include <fstream>
#define NMAX 200001
using namespace std;

int heap[NMAX], poz[NMAX], vec[NMAX];

void sift(int nr, int k) {
    int son;
    do {
        son = 0;
        if (k << 1 <= nr) {
            son = k << 1;
            if ((k << 1) + 1 <= nr && heap[k << 1] > heap[(k << 1) + 1]) {
                son = (k << 1) + 1;
            }
            if (heap[son] > heap[k]) {
                son = 0;
            }
            if (son) {
                swap(heap[k], heap[son]);
                swap(vec[k], vec[son]);
                swap(poz[vec[son]], poz[vec[k]]);
                k = son;
            }
        }

    } while (son);
}

void percolate(int k) {
    while (k > 1 && heap[k >> 1] > heap[k]) {
        swap(vec[k >> 1], vec[k]);
        swap(heap[k >> 1], heap[k]);
        swap(poz[vec[k]], poz[vec[k >> 1]]);
        k >>= 1;
    }
}

void cut(int &nr, int k) {
    heap[k] = heap[nr];
    vec[k] = vec[nr];
    poz[vec[nr--]] = k;

    if (k > 1 && heap[k] < heap[k >> 1]) {
        percolate(k);
    } else {
        sift(nr, k);
    }
}

void heap_insert(int &nr, int val, int &ordin) {
    vec[++nr] = ++ordin;
    heap[nr] = val;
    poz[ordin] = nr;

    percolate(nr);
}

int main() {
    int i, n, op, nr = 0, ordin = 0;

    ifstream in("heapuri.in");
    ofstream out("heapuri.out");
    in >> n;
    for (i = 0; i < n; ++i) {
        in >> op;
        switch (op) {
            case 1: in >> op;
                    heap_insert(nr, op, ordin);
                    break;
            case 2: in >> op;
                    cut(nr, poz[op]);
                    break;
            case 3: out << heap[1] << '\n';
        }
    }
    in.close();
    out.close();

    return 0;
}
