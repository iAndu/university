#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct vertex {
	int x, y, cost;
};

bool cmp (const vertex &a, const vertex &b) {
	return a.cost < b.cost;
}

vector<int> father;
vector<int> height;

/* search() *
 ************
 * Returns the tree that 'node' is contained while compressing it
*/
int search(const int node) {
	if (father[node] != node)
		father[node] = search(father[node]);
	return father[node];
}

/* join() *
 **********
 * Joins the a's and b's trees
*/
void join(int a, int b) {
	a = search(a);
	b = search(b);

	if (height[a] < height[b]) {
		father[a] = b;
		++height[b];
	} else {
		father[b] = a;
		++height[a];
	}
}

int main() {
	int n, m;
	vector<vertex> vertexes;

	ifstream in("grafpond.in");
	in >> n >> m;
	father.resize(n);
	height.resize(n);
	for (int i = 0; i < n; ++i) {
		father[i] = i;
		height[i] = 0;
	}

	for (int i = 0; i < m; ++i) {
		vertex x;
		in >> x.x >> x.y >> x.cost;
		--x.x;
		--x.y;
		vertexes.push_back(x);
	}
	in.close();

	sort(vertexes.begin(), vertexes.end(), cmp);

	vector<vertex> chosen;
	auto i = vertexes.begin();
	// While not a tree and we still have vertexes
	while (chosen.size() < n - 1 && i != vertexes.end()) {
		// If x and y are not in the same tree yet, join them and chose the vertex
		if (father[i->x] != father[i->y]) {
			join(i->x, i->y);
			chosen.push_back(*i);
		}
		++i;
	}

	for (auto i = chosen.begin(); i != chosen.end(); ++i)
		cout << i->x << ' ' << i->y << ' ' << i->cost << '\n';

	return 0;
}
