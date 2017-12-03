#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#define INF 999999
 
using namespace std;
 
struct edge { int x, y, cost; };
struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
};
 
int nr_settles, nr_forts, nr_edges;
vector< pair<int, int> > *adj;
unordered_set<int> forts;
priority_queue< pair<int, int>, vector< pair<int, int> >, cmp> que;
vector<int> dij_dist;
vector<bool> viz;
vector<int> father;
 
void read() {
    ifstream in("catun.in");
    in >> nr_settles >> nr_edges >> nr_forts;
    adj = new vector< pair<int,int> >[nr_settles + 1];
    for (int i = 0; i < nr_forts; ++i) {
        int x;
        in >> x;
        forts.insert(x);
    }
    for (int i = 0; i < nr_edges; ++i) {
        edge e;
        in >> e.x >> e.y >> e.cost;
        adj[e.x].push_back(make_pair(e.y, e.cost));
        adj[e.y].push_back(make_pair(e.x, e.cost));
    }
    in.close();
}
 
void dijsktra() {
    dij_dist.resize(nr_settles + 1, INF);
    viz.resize(nr_settles + 1, false);
    father.resize(nr_settles + 1, 0);
    // Insert all forts in heap
    for (auto i : forts) {
        dij_dist[i] = 0;
        que.push(make_pair(i, 0));
    }
    auto node = que.top();
    for (int i = 0; i < nr_settles && que.size(); ++i) {
        for (auto j : adj[node.first]) {
        	// If the settlement is equally distant to two settlements, attach it
        	// to the one which belongs to the minimum index fort
            if (node.second + j.second == dij_dist[j.first])
                father[j.first] = min(father[j.first], father[node.first] != 0 ? father[node.first] : node.first);
            if (node.second + j.second < dij_dist[j.first]) {
                dij_dist[j.first] = node.second + j.second;
                que.push(make_pair(j.first, dij_dist[j.first]));
                // If the node is a fort, make it it's father. Otherwise make the
                // settlement's father it's own father
                if (forts.find(node.first) != forts.end())
                    father[j.first] = node.first;
                else father[j.first] = father[node.first];
            }
        }
        viz[node.first] = true;
        // Select the best distance settlement until a not visited one is found
        do {
            que.pop();
            node = que.top();
        } while (que.size() && viz[node.first]);
    }
}
 
void print() {
    ofstream out("catun.out");
    for (int i = 1; i <= nr_settles; ++i)
        out << father[i] << ' ';
    out << '\n';
    out.close();
}
 
int main() {
    read();
    dijsktra();
    print();
 
    return 0;
}