#include <iostream>
#include <string>
#include <stack>

using namespace std;

void print_error(int i, string &str) {
    int start = max(0, i - 2);
    int stop = min((int)str.length() - 1, i + 2);

    for (; start <= stop; ++start) {
        cout << str[start];
    }
}

bool isOpenPar(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool isClosedPar(char c) {
    return c == ')' || c == ']' || c == '}';
}

int main() {
    string str;
    stack< pair<char, int> > st;

    cout << "Introduceti sirul: ";
    cin >> str;

    int length = str.length();
    for (int i = 0; i < length; ++i) {
        if (isOpenPar(str[i])) {
            st.push(make_pair(str[i], i));
        } else if (isClosedPar(str[i])) {
            if (st.empty()) {
                print_error(i, str);

                return 0;
            }

            switch (str[i]) {
                case ')':
                    if (st.top().first == '(') {
                        st.pop();
                    } else {
                        print_error(i, str);

                        return 0;
                    }

                    break;

                case ']':
                    if (st.top().first == '[') {
                        st.pop();
                    } else {
                        print_error(i, str);

                        return 0;
                    }

                    break;

                case '}':
                    if (st.top().first == '}') {
                        st.pop();
                    } else {
                        print_error(i, str);

                        return 0;
                    }

                    break;
            }
        }
    }

    if (!st.empty()) {
        print_error(st.top().second, str);

        return 0;
    }

    cout << "Este corect parantezat.";

    return 0;
}
