#include <iostream>
#include <unordered_map>
#include <queue>
#include <cstring>
#include <unordered_set>

using namespace std;

struct player {
    string name;
    int score;
};

void clear_hash(unordered_map<string, int> &my_hash) {
    unordered_map<string, int> clean;
    swap (clean, my_hash);
}

int main() {
    int n;
    player p;

    queue<player> que;
    unordered_map<string, int> my_hash;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p.name >> p.score;
        que.push(p);
        my_hash[p.name] += p.score;
    }

    int maxim = 0;
    for (unordered_map<string, int>::iterator it = my_hash.begin(); it != my_hash.end(); ++it) {
        maxim = max(maxim, it->second);
    }

    unordered_set<string> my_set;
    for (unordered_map<string, int>::iterator it = my_hash.begin(); it != my_hash.end(); ++it) {
        if (it->second == maxim) {
            my_set.insert(it->first);
        }
    }
    clear_hash(my_hash);
    while (!que.empty()) {
        if (my_set.find(que.front().name) != my_set.end()) {
            if (my_hash[que.front().name] + que.front().score >= maxim) {
                cout << que.front().name << '\n';
                return 0;
            }
            my_hash[que.front().name] += que.front().score;
        }
        que.pop();
    }

    return 0;
}
