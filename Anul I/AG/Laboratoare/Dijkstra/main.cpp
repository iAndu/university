#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#define INF 999999

using namespace std;

struct edge { int x, y, cost; };
struct cmp {
	bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
		return a.second > b.second;
	}
};

int nr_nodes, nr_edges, nr_control, s_point;
vector< pair<int, int> > *adj;
vector<int> controls;
vector<int> dij_dist;
priority_queue< pair<int, int>, vector< pair<int, int> >, cmp> p_que;
vector<int> father;
vector<bool> viz;

void read() {
	ifstream in("grafpond.in");
	in >> nr_nodes >> nr_edges;
	adj = new vector< pair<int, int> >[nr_nodes + 1];
	for (int i = 0; i < nr_edges; ++i) {
		edge e;
		in >> e.x >> e.y >> e.cost;
		adj[e.x].push_back(make_pair(e.y, e.cost));
		adj[e.y].push_back(make_pair(e.x, e.cost));
	}
	in.close();
	cin >> nr_control;
	for (int i = 0; i < nr_control; ++i) {
		int x;
		cin >> x;
		controls.push_back(x);
	}
	cin >> s_point;
}

void dijsktra() {
	dij_dist.resize(nr_nodes + 1, INF);
	father.resize(nr_nodes + 1, 0);
	viz.resize(nr_nodes + 1, false);
	dij_dist[s_point] = 0;
	p_que.push(make_pair(s_point, 0));

	pair<int, int> node = p_que.top();
	// While not all nodes have been visited and the best distance isn't INF
	for (int j = 0; j < nr_nodes && node.second != INF; ++j) {
		// Compute the distance to all neighbours
		for (auto i : adj[node.first])
			if (node.second + i.second < dij_dist[i.first]) {
				father[i.first] = node.first;
				dij_dist[i.first] = node.second + i.second;
				p_que.push(make_pair(i.first, dij_dist[i.first]));
			}

		viz[node.first] = true;
		// Select the node with best distance that isn't visited
		do {
			p_que.pop();
			if (node == p_que.top()) {
				j = nr_nodes;
				break;
			}
			node = p_que.top();
		} while (viz[node.first]);
	}
}

void print(int node) {
	if (!father[node])
		return;
	print(father[node]);
	cout << father[node] << ' ';
}

int main() {
	read();
	dijsktra();

	int minim = INF, min_node = controls[0];

	for (auto i : controls)
		if (dij_dist[i] < minim) {
			minim = dij_dist[i];
			min_node = i;
		}

	cout << "Closest control point: " << min_node << '\n';
	cout << "Minimum road to control point: ";
	print(min_node);
	cout << min_node << '\n';

	return 0;
}