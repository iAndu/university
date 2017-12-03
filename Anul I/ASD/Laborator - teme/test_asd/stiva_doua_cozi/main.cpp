#include <iostream>
#include <queue>
using namespace std;

queue<int> que1, que2;

void func_push() {
    int x;
    cin >> x;
    que1.push(x);
}

void clear_que() {
    queue<int> aux;
    swap(que2, aux);
}

void func_pop() {
    clear_que();
    if (que1.size()) {
        while (que1.size() != 1) {
            que2.push(que1.front());
            que1.pop();
        }
        que1.pop();

        swap(que1, que2);
    }
}

void func_list() {
    que2 = que1;
    for (int i = 1; i <= que1.size(); ++i) {
        while (que1.size() != i) {
            que1.pop();
        }
        cout << que1.front() << ' ';
        que1 = que2;
    }
}

int main() {

    int op;
    cin >> op;
    while (op != 4) {
        switch (op) {
            case 1: func_push();
                    break;
            case 2: func_pop();
                    break;
            case 3: func_list();
                    break;
        }
        cin >> op;
    }

    return 0;
}
