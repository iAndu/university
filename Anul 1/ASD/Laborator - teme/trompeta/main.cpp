#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;

int main() {
    int n, m, length = 0, i, x;
    char s[1000000];
    stack<int> stiv;

    FILE *in = fopen("trompeta.in", "r");
    fscanf(in, "%d %d", &n, &m);
    fgetc(in);
    fscanf(in, "%s", &s);
    fclose(in);

    for (i = 0; i < n; i++) {
        x = s[i] - '0';
        length = stiv.size();
        while (!stiv.empty() && x > stiv.top() && length - 1 + n - i >= m) {
            stiv.pop();
            length--;
        }
        stiv.push(x);
        length++;
    }

    FILE *out = fopen("trompeta.out", "w");
    for (i = length - 1; i >= 0; i--) {
        s[i] = stiv.top() + '0';
        stiv.pop();
    }
    s[m] = '\0';
    fprintf(out, "%s\n", s);
    fclose(out);

    return 0;
}
