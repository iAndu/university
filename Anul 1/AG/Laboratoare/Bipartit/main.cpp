#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct edge {
	int x, y;
};

vector<int> father;
vector<int> viz;
vector<int> *adj;
vector<int> disjoint;
bool sw = false;
int ceva = 0;

void dfs(int node, int fnode) {
	viz[node] = 1; // The node is currently being checked
	for (auto i = adj[node].begin(); i != adj[node].end(); ++i)
		if (!viz[*i]) {
			father[*i] = node;
			dfs(*i, node);
			// If we arrived at the beginning of the cicle, end the printing
			if (ceva == node) {
				ceva = 0;
				return;
			}
			// If we are still in the cicle, print the node
			if (ceva) {
				viz[node] = 2;
				cout << node << ' ';
				return;
			}
		// If the node is being visited and it isn't the father node, we found a cicle
		} else if (viz[*i] == 1 && fnode != *i) {
			ceva = *i; // Remember the node where the cicle begins
			cout << *i << ' ' << node << ' ';
			viz[node] = 2;
			return;
		}
	viz[node] = 2;
}

void color(int node) {
	disjoint[node] = 1;
	queue<int> aux;
	aux.push(node);
	while (!aux.empty()) {
		auto x = aux.front();
		aux.pop();
		for (auto i : adj[x]) {
			if (disjoint[i] == disjoint[x]) {
				cout << "Nu este posibil!\n";
				sw = true;
				return;
			} else if (!disjoint[i]) {
				switch(disjoint[x]) {
					case 1: disjoint[i] = 2;
							break;
					case 2: disjoint[i] = 1;
							break;
				}
				aux.push(i);
			}
		}
	}
}

int main() {
	ifstream in("graf.in");
	int nr_nodes, nr_edges;
	in >> nr_nodes >> nr_edges;

	vector<edge> edges;
	adj = new vector<int>[nr_nodes + 1];
	disjoint.resize(nr_nodes + 1, 0);

	for (int i = 0; i < nr_edges; ++i) {
		edge e;
		in >> e.x >> e.y;
		adj[e.x].push_back(e.y);
		adj[e.y].push_back(e.x);
		edges.push_back(e);
	}

	for (int i = 1; i <= nr_nodes; ++i)
		if (!disjoint[i])
			color(i);

	// If a partition is possible
	if (!sw) {
		int nr = 0;
		for (auto i = disjoint.begin(); i != disjoint.end(); ++i)
			if (*i == 1) {
				cout << i - disjoint.begin() << ' ';
				++nr;
			}
		cout << '\n';
		for (auto i = disjoint.begin(); i != disjoint.end(); ++i)
			if (*i == 2)
				cout << i - disjoint.begin() << ' ';
		cout << '\n';
		if (nr_edges == nr * (nr_nodes - nr))
			cout << "Bipartit complet!\n";
		else cout << "Nu este bipartit complet!\n";
	} else {
		father.resize(nr_nodes + 1, 0);
		viz.resize(nr_nodes + 1, 0);
		dfs(1, 0);
		cout << '\n';
	}

	in.close();

	return 0;
}