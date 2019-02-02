#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;

int main() {
    int n, k, length = 0, i, x, contor;
    char s[10000];
    stack<int> stiv;

    FILE *in = fopen("alibaba.in", "r");
    fscanf(in, "%d %d", &n, &k);
    contor = n - k;
    fgetc(in);
    fscanf(in, "%s", &s);
    fclose(in);

    for (i = 0; i < n; i++) {
        x = s[i] - '0';
        length = stiv.size();
        while (!stiv.empty() && x > stiv.top() && length - 1 + n - i >= contor) {
            stiv.pop();
            length--;
        }
        stiv.push(x);
        length++;
    }

    FILE *out = fopen("alibaba.out", "w");
    for (i = length - 1; i >= 0; i--) {
        s[i] = stiv.top() + '0';
        stiv.pop();
    }
    s[contor] = '\0';
    fprintf(out, "%s\n", s);
    fclose(out);

    return 0;
}
