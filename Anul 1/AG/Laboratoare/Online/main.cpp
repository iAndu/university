#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int x, y, cost;
};

int nr_cities, nr_roads, nr_queries;
vector<edge> edges;
vector<int> father;
vector<int> height;

bool cmp(const edge &a, const edge &b) {
	return a.cost < b.cost;
}

/* search() *
 ************
 * Searches for the root of the tree that node belongs to while compressing
 * the edges
*/
int search(int node) {
	if (father[node] != node)
		father[node] = search(father[node]);
	return father[node];
}

void join(int a, int b) {
	a = search(a);
	b = search(b);

	// Attach smaller tree to the bigger one
	if (height[a] < height[b]) {
		father[a] = b;
		++height[b];
	} else {
		father[b] = a;
		++height[a];
	}
}

/* kruskal() *
 *************
 * Computes the MST's cost based on edges vector
*/
int kruskal() {
	int chosen = 0;
	auto i = edges.begin();
	int min_cost = 0;

	for (int i = 1; i <= nr_cities; ++i) {
		height[i] = 0;
		father[i] = i;
	}

	while (chosen < nr_cities - 1) {
		if (search(i->x) != search(i->y)) {
			join(i->x, i->y);
			min_cost += i->cost;
			++chosen;

			// Save the best edges to the front of the vector
			edges[chosen - 1] = *i;
		}
		++i;
	}

	return min_cost;
}

void insert_edge(const edge &e) {
	for (auto i = edges.begin(); i != edges.end(); ++i)
		if (e.cost < i->cost) {
			edges.insert(i, e);
			return;
		}
}

int main() {
	ifstream in("online.in");
	in >> nr_cities >> nr_roads;

	for (int i = 0; i < nr_roads; ++i) {
		edge e;
		in >> e.x >> e.y >> e.cost;
		edges.push_back(e);
	}

	sort(edges.begin(), edges.end(), cmp);

	father.resize(nr_cities + 1);
	height.resize(nr_cities + 1);
	ofstream out("online.out");
	out << kruskal() << '\n';

	in >> nr_queries;
	for (int i = 0; i < nr_queries; ++i) {
		edge e;
		in >> e.x >> e.y >> e.cost;
		insert_edge(e);

		out << kruskal() << '\n';
	}

	out.close();
	in.close();

	return 0;
}