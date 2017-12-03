#include <iostream>
#include <stack>
using namespace std;

stack<int> st1, st2;

void func_push() {
    int x;
    cin >> x;
    st1.push(x);
}

void func_pop() {
    if (st1.size()) {
        while (st1.size() != 1) {
            st2.push(st1.top());
            st1.pop();
        }
        st1.pop();
        while (st2.size()) {
            st1.push(st2.top());
            st2.pop();
        }
    }
}

void func_list() {
    while (st1.size()) {
        st2.push(st1.top());
        st1.pop();
    }
    while (st2.size()) {
        cout << st2.top() << ' ';
        st1.push(st2.top());
        st2.pop();
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
