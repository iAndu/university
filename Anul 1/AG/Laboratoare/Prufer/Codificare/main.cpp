#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int nr_nodes;
int g_max = -1, i_max = -1;
vector<int> *network;
vector<bool> visited;
vector<int> father;
vector<int> grades;

// Creates a tree based on the grades sequence
void create_tree(int node) {
	visited[node] = true;
	for (auto i = network[node].begin(); i != network[node].end(); ++i)
		if (!visited[*i]) {
			++grades[node];
			++grades[*i];
			father[*i] = node;
			create_tree(*i);
		}
}

// Initialize all the components
void initialize() {
	network = new vector<int>[nr_nodes];
	grades.resize(nr_nodes, 0);
	visited.resize(nr_nodes, false);
	father.resize(nr_nodes, -2);
}

int main() {
	// Read the file and create the network
	ifstream in("retea.in");
	in >> nr_nodes;
	initialize();
	int x, y;
	while (in >> x >> y) {
		network[x - 1].push_back(y - 1);
		network[y - 1].push_back(x - 1);
	}
	in.close();

	// Create a tree with the last node as root
	// because that will be one of the last two nodes remaining when making
	// the Prufer serialization
	create_tree(nr_nodes - 1);

	ofstream out("rezultat.txt");
	// Chosen assures that we will do only nr_nodes - 2 steps
	int chosen = 0;
	// For each node, if it's grade is equal to 1, substract one from him and
	// his father, and add his father to the Prufer sequence
	for (int i = 0; i < nr_nodes && chosen < nr_nodes - 2; ++i)
		if (grades[i] == 1) {
			++chosen;
			--grades[i];
			--grades[father[i]];
			if (father[i] == -2) // Should not evaluate to true, but just to be sure
				out << 0 << ' ';
			else out << father[i] << ' ';
			int j = father[i];
			// If his father's grade became 1 and it's somewhere left of the
			// current node 'i', set another pointer there and continue the algorithm
			while (j < i && grades[j] == 1 && chosen < nr_nodes - 2) {
				++chosen;
				--grades[j];
				--grades[father[j]];
				if (father[j] == -2)
					out << 0 << ' ';
				else out << father[j] << ' ';
				j = father[j];
			}
		}
	out << '\n';
	out.close();

	return 0;
}