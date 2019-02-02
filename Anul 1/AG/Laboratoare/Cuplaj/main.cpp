#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define NMAX 10011

using namespace std;

vector<int> adj[NMAX];
int capacity[NMAX][NMAX], flux[NMAX][NMAX], nrNodes, nrEdges, source, dest, color[NMAX], father[NMAX];

// Assuming the graph is bipartite
void dfs(int node, int pColor);

bool bfs();

int maxFlux();

int main() {
    ifstream in("graf.in");

    in >> nrNodes >> nrEdges;

    for (int i = 0; i < nrEdges; ++i) {
        int node1, node2;
        in >> node1 >> node2;

        adj[node1].push_back(node2);
        adj[node2].push_back(node1);
    }

    in.close();

    dfs(1, -1);

    //Unim toate nodurile dintr-o multime cu destinatia si sursa cum nodurile din cealalta multime
    //setam capacitatea 1 pe orice muchie
    source = 0;
    dest = nrNodes + 1;
    for (int node = 1; node <= nrNodes; ++node) {
        if (color[node] == 1) {
            adj[source].push_back(node);
            adj[node].push_back(source);
            capacity[source][node] = 1;
            for (int i = 0; i < adj[node].size(); ++i) {
                int child = adj[node][i];
                capacity[node][child] = 1;
            }
        } else {
            adj[node].push_back(dest);
            adj[dest].push_back(node);
            capacity[node][dest] = 1;
        }
    }

    ++nrNodes;

    cout << maxFlux() << "\n";

    for (int node = 1; node <= nrNodes; ++node)
        for (int i = 0; i < adj[node].size(); ++i) {
            int child = adj[node][i];
            if(flux[node][child] == 1 && child != dest)
                cout << node << " " << child << "\n";
        }

    return 0;

}

int maxFlux()
{
    int sol = 0;
    while (bfs())
    {
        int node = dest;
        int minim = capacity[father[dest]][dest] - flux[father[dest]][dest];
        while (node) {
            minim = min(minim, capacity[father[node]][node] - flux[father[node]][node]);
            node = father[node];
        }

        node = dest;
        while (node) {
            flux[father[node]][node] += minim;
            flux[node][father[node]] -= minim;
            node = father[node];
        }
        sol += minim;
    }
    return sol;
}

bool bfs() {
    for (int node = 1; node <= nrNodes; ++node)
        father[node] = -1;
    father[source] = 0;

    queue<int> que;
    que.push(source);

    while (!que.empty()) {
        int node = que.front();
        for (int i = 0; i < adj[node].size (); ++i) {
            int child = adj[node][i];

            if (father[child] == -1 && capacity[node][child] > flux[node][child]) {
                father[child] = node;
                if (child == dest)
                    return true;

                que.push(child);
            }

        }
        que.pop();
    }
    return false;
}

void dfs(int node, int pColor) {
    color[node] = (-1) * pColor;

    for (int i = 0; i < adj[node].size(); ++i) {
        int child = adj[node][i];
        if (!color[child])
            dfs(child, color[node]);
    }
}