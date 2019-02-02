#include<vector>
#include<cstdio>
#include<algorithm>

struct frnd {
    int money, fshp;
};

using namespace std;

bool cmp(frnd a, frnd b) {
    if (a.money < b.money)
        return true;
    return false;
}

int main() {
    int n = 0, d = 0, i = 0, j = 0;
    long long maxfshp = 0, maxim = 0;
    vector<frnd> friends;

    scanf("%d %d", &n, &d);
    for (int i = 0; i < n; ++i) {
        frnd x;
        x.money = 0;
        x.fshp = 0;
        scanf("%d %d", &x.money, &x.fshp);
        friends.push_back(x);
    }

    sort(friends.begin(), friends.end(), cmp);

    while (j <= n) {
        if (friends[j].money - friends[i].money < d) {
            maxim += friends[j].fshp;
            j++;
        } else {
            if (maxim > maxfshp) {
                maxfshp = maxim;
            }
            maxim -= friends[i].fshp;
            i++;
        }
    }

    printf("%I64d\n", maxfshp);
    //mlc
    return 0;
}
