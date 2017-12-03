#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

struct edge {
	int x, y, dist;
};

bool cmp (const edge &a, const edge &b) {
	return a.dist < b.dist;
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

/* distanta() *
 **************
 * Computes the Levenstein distance between two strings
*/
int distanta(char *s1, char *s2){
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	int *ci1 = new int[n2+1];
	int *ci = new int[n2+1];

	for(int j = 0; j <= n2; j++)
		ci1[j] = j;

	for(int i = 1; i <= n1; i++)  {
		ci[0]=i;
		for(int j = 1; j <= n2; j++)
		if(s1[i	- 1] == s2[j - 1])
			ci[j] = ci1[j	- 1];
		else
			ci[j] = 1 + min(min(ci1[j], ci[j - 1]), ci1[j - 1]);
		for(int j = 0; j <= n2; j++)
			ci1[j] = ci[j];
	}

	return ci[n2];
}

int main() {
	int k;
	cin >> k;

	ifstream in("cuvinte.in");

	vector<char*> words;
	
	while (!in.eof())  {
		char *str = new char[256];
		in >> str;
		if (!in.eof()) 
			words.push_back(str);
	}

	in.close();

	father.resize(words.size());
	height.resize(words.size());

	for (int i = 0; i < words.size(); ++i) {
		father[i] = i;
		height[i] = 0;
	}

	vector<edge> edges;
	edge v;
	for (auto i = words.begin(); i < words.end(); ++i)
		for (auto j = i + 1; j != words.end(); ++j) {
			v.x = i - words.begin();
			v.y = j - words.begin();
			v.dist = distanta(*i, *j);
			edges.push_back(v);
		}

	sort(edges.begin(), edges.end(),cmp);

	int chosen = 0;
	auto i = edges.begin();
	// Join n - k + 1 words in clusters
	while (chosen <= words.size() - k && i != edges.end()) {
		if (father[i->x] != father[i->y]) {
			join(i->x, i->y);
			++chosen;
		}
		++i;
	}

	int min_distance;

	for (i; i != edges.end(); ++i)
		if (father[i->x] != father[i->y]) {
			min_distance = i->dist;
			break;
		}

	// Compress the tree one more time
	for (int i = 0; i < words.size(); ++i)
		father[i] = search(i);

	vector<bool> visited(father.size(), false);
	for (auto i = father.begin(); i != father.end(); ++i) {
		if (!visited[*i]) {
			for (auto j = father.begin(); j != father.end(); ++j)
				if (*i == *j)
					cout << words[j - father.begin()] << ' ';
			cout << '\n';
			visited[*i] = true;
		}
	}
	cout << min_distance << '\n';

	return 0;
}