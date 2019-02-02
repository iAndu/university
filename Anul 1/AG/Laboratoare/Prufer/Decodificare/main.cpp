#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	int nr_nodes;
	vector<int> prufer;
	vector<int> grades;

	// Read the output from the Prufer serialization output
	int x;
	ifstream in("../Codificare/rezultat.txt");
	while (in >> x)
		prufer.push_back(x);
	in.close();

	// No of nodes will be the Prufer sequence size + 2
	nr_nodes = prufer.size() + 2;
	// Initialize the grades of each node to 1 because each node appears in the
	// Prufer sequence for [grade] - 1 times
	grades.resize(nr_nodes, 1);
	for (auto i = prufer.begin(); i != prufer.end(); ++i)
		++grades[*i];

	auto it = prufer.begin();
	ofstream out("conexiuni.txt");
	// For each node until all the sequence is parsed
	for (int i = 0; i < nr_nodes && it != prufer.end(); ++i)
		// If it's grade is equal to 1, substract 1 from him and his father
		// and create a vertex between this two
		if (grades[i] == 1) {
			out << i << ' ' << *it << '\n';
			--grades[i];
			--grades[*it];
			int j = *it;
			++it;
			// If his father's grade became 1 and is in the left side of the
			// current position, set another pointer to it and continue the algorithm
			while (j < i && grades[j] == 1 && it != prufer.end()) {
				out << j << ' ' << *it << '\n';
				--grades[j];
				--grades[*it];
				j = *it;
				++it;
			}
		}
	// At last, there will be 2 more nodes left with grade equal to 1 and we
	// have to connect those two
	for (int i = 0; i < nr_nodes; ++i)
		if (grades[i])
			out << i << ' ';
	out << '\n';
	out.close();

	return 0;
}