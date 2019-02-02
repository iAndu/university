#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 1001

using namespace std;

int flux[NMAX][NMAX], capacity[NMAX][NMAX], father[NMAX], nrNodes, src, dest, nrEdges;
vector<int> adj[NMAX];

bool valid();
bool BFS();
int getMaxFlux();
void print();

int main() {
    ifstream in("retea.in");
    in >> nrNodes >> src >> dest >> nrEdges;

    for (int i = 1; i <= nrEdges; ++i) {
        int node1, node2, eCap, eFlux;
        in >> node1 >> node2 >> eCap >> eFlux;

        capacity[node1][node2] += eCap;
        flux[node1][node2] += eFlux;
        adj[node1].push_back(node2);
        adj[node2].push_back(node1);
    }

    if (!valid()) {
        cout << "NU\n";
        return 0;
    }

    cout << "DA\n";

    for (int i = 1; i <= nrNodes; ++i)
        for (int j = 1; j <= nrNodes; ++j)
            if (capacity[i][j] > 0)
                flux[j][i] = -flux[i][j];

    int maxFlux = getMaxFlux();

    cout << maxFlux << "\n";

    for (int i = 1; i <= nrNodes; ++i)
        for (int j = 1; j <= nrNodes; ++j)
            if (capacity[i][j] > 0)
                cout << i << " " << j << " " << flux[i][j] << "\n";

    cout << maxFlux << "\n";

    print();

    return 0;
}

bool valid() {
    for (int i = 1; i <= nrNodes; ++i) {
        int in = 0;
        int ex = 0;
        for (int j = 1; j <= nrNodes; ++j) {
            // flow must be greater or equal to 0 and lower or equal then the capacity
            if (flux[i][j] > capacity[i][j] || flux[i][j] < 0)
                return false;
            in += flux[j][i];
            ex += flux[i][j];
        }
        // what goes in, must go out, except for source and destination
        if (i == src && in != 0)
            return false;
        else if(i == dest && ex != 0)
            return false;
        else if(i != src && i != dest && in != ex)
            return false;
    }
    return true;
}

bool BFS() {
    for (int i = 1; i <= nrNodes; ++i)
        father[i] = -1;
    father[src] = 0;
    queue<int> que;
    que.push(src);
    while (!que.empty()) {
        int node = que.front();
        que.pop();
        for (int i = 0; i < adj[node].size(); ++i) {
            int child = adj[node][i];
            if (father[child] == -1 && capacity[node][child] > flux[node][child]) {
                father[child] = node;
                if (child == dest)
                    return true;
                que.push(child);
            }
        }
    }
    return false;
}

int getMaxFlux() {
    while (BFS()) {
        int node = dest;
        int minim = capacity[father[dest]][dest] - flux[father[dest]][dest];
        while (father[node]) {
            minim = min(minim, capacity[father[node]][node] - flux[father[node]][node]);
            node = father[node];
        }
        node = dest;
        while (father[node]) {
            flux[father[node]][node] += minim;
            flux[node][father[node]] -= minim;
            node = father[node];
        }
    }
    int sol = 0;
    for (int i = 1; i <= nrNodes; ++i)
        sol += flux[src][i];
    return sol;
}

void print() {
    queue<int> que;
    que.push(src);

    bool viz[NMAX];
    for(int i = 1; i <= nrNodes; ++i)
        viz[i] = false;
    viz[src] = true;

    while (!que.empty()) {
        int node = que.front();
        que.pop();
        for (int i = 0; i < adj[node].size(); ++i) {
            int child = adj[node][i];
            if (viz[child] || capacity[node][child] <= flux[node][child])
                continue;
            viz[child] = true;
            que.push(child);
        }
    }
    for (int k = 1; k <= nrNodes; ++k) {
        if (!viz[k])
            continue;

        for (int i = 0; i < adj[k].size(); ++i) {
            int j = adj[k][i];
            if (flux[k][j] == capacity[k][j] && capacity[k][j] != 0)
                cout << k << " " << j << "\n";
        }
    }
}