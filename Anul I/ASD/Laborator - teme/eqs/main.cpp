#include <unordered_map>
#include <fstream>
using namespace std;

int main() {
    unordered_map<int, int> my_hash;

    int a, b, c, d, e;
    ifstream in("eqs.in");
    in >> a >> b >> c >> d >> e;
    in.close();

    for (int i = -50; i <= 50; ++i) {
        for (int j = -50; j <= 50; ++j) {
            if (i && j) {
                ++my_hash[a * i * i * i + b * j * j * j];
            }
        }
    }

    int nrsol = 0;
    for (int i = -50; i <= 50; ++i) {
        for (int j = -50; j <= 50; ++j) {
            for (int k = -50; k <= 50; ++k) {
                if (i && j && k) {
                    int prod = c * i * i * i + d * j * j * j + e * k * k * k;
                    if (my_hash[prod]) {
                        nrsol += my_hash[prod];
                    }
                }
            }
        }
    }

    ofstream out("eqs.out");
    out << nrsol << '\n';
    out.close();

    return 0;
}
