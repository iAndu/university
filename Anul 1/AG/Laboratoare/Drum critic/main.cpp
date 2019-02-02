#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge { int x, y; };

int nr_activities, nr_edges;
vector<int> duration;
vector<int> int_grades;
vector<int> ext_grades;
vector<int> *adj;
vector<int> topologic;
vector<int> dijs_dist;
vector<int> father;
vector<edge> edges;

void topologic_sort() {
	queue<int> que;
	// Push the nodes with internal grades 0 in the queue
	for (auto i = int_grades.begin() + 1; i != int_grades.end(); ++i)
		if (!(*i))
			que.push(i - int_grades.begin());

	while (!que.empty()) {
		int node = que.front();
		topologic.push_back(node);
		// Decrement adjancent nodes's grades. If they become 0, add to queue
		for (auto i = adj[node].begin(); i != adj[node].end(); ++i)
			if (!(--int_grades[*i]))
				que.push(*i);
		que.pop();
	}
}

void read() {
	ifstream in("activitati.in");
	in >> nr_activities;
	// +1 because numbers aren't indexed from 0
	adj = new vector<int>[nr_activities + 1];
	int_grades.resize(nr_activities + 1, 0);
	ext_grades.resize(nr_activities + 1, 0);
	// Duration for activity '0'
	duration.push_back(0);
	for (int i = 0; i < nr_activities; ++i) {
		int x;
		in >> x;
		duration.push_back(x);
	}
	in >> nr_edges;
	for (int i = 0; i < nr_edges; ++i) {
		edge e;
		in >> e.x >> e.y;
		++int_grades[e.y];
		++ext_grades[e.x];
		adj[e.x].push_back(e.y);
		edges.push_back(e);
	}
}

void dijsktra() {
	dijs_dist.resize(nr_activities + 1, -999);
	father.resize(nr_activities + 1, 0);

	topologic_sort();
	// Check which are the 'terminal' activities and attach them to activity 0
	// Activity 0 will be the finish point
	for (auto i = ext_grades.begin(); i != ext_grades.end(); ++i)
		if (!(*i)) {
			adj[i - ext_grades.begin()].push_back(0);
			++int_grades[0];
		}

	for (auto i : topologic)
		for (auto j : adj[i])
			if (dijs_dist[i] + duration[i] > dijs_dist[j]) {
				dijs_dist[j] = dijs_dist[i] + duration[i];
				father[j] = i;
			}
}

void print_answer(int node = 0) {
	if (!father[node])
		return;
	print_answer(father[node]);
	cout << father[node] << ' ';
}

int main() {
	read();
	dijsktra();

	cout << "Timp minim: " << 999 + dijs_dist[0] << '\n';
	cout << "Activitati critice: ";
	
	print_answer();
	cout << '\n';

	for (int i = 1; i <= nr_activities; ++i) {
		cout << i << ": ";
		cout << 999 + dijs_dist[i] << ' ' << 999 + dijs_dist[i] + duration[i] << '\n';
	}

	return 0;
}