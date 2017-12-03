#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return (a.second > b.second) ? true : false;
}

void terminate(ofstream &out)
{
    out.close();
    out.open("lab.out");
    out << "Impossible!\n";
}

void interclas(vector< pair<int, int> > &grades, int right)
{
    int i = 1, j = right;
    vector< pair<int, int> >aux;

    while (i < right && j < (int)grades.size())
        if (grades[i].second > grades[j].second)
            aux.push_back(grades[i++]);
        else
            aux.push_back(grades[j++]);

    while (i < right)
        aux.push_back(grades[i++]);

    while (j < (int)grades.size())
        aux.push_back(grades[j++]);

    swap(aux, grades);
}

int main()
{
    int nr_nodes, grade_sum = 0;
    bool isolated = false;
    vector< pair<int, int> > grades;
    vector< pair<int, int> > save;

    ifstream in("havel-hakimi.in");
    ofstream out("lab.txt");
    in >> nr_nodes;

    out << "A:\n";
    for (int i = 0; i < nr_nodes; ++i)
    {
        int grade;
        in >> grade;
        // Computes the grades sum for future use when constructing the tree
        grade_sum += grade;
        // Check if any node is isolated for future use when constructing the tree
        if (!grade)	
        	isolated = true;

        // If the grade is greater or equal to the no of nodes, then it's
        // impossible to create a graph or tree
        if (grade >= nr_nodes)
        {
            terminate(out);
            return 0;
        }

        grades.push_back(make_pair(i, grade));
    }

    // Make a copy of the grades
    save = grades;

    // Sort grades descending
    sort(grades.begin(), grades.end(), cmp);

    vector<int> adj[nr_nodes];

    while (!grades.empty())
    {
        // If there is any grade with value greater then the number of grades
        // still in vector, it's impossible to continue || should not be ever true
    	if (grades[0].second >= grades.size())
    	{
    		terminate(out);
    		return 0;
    	}

        // Decrement the next grades[0] values by 1
        for (int i = 1; i <= grades[0].second; ++i)
        {
            // If grade is already 0, then it's impossible
            if (!grades[i].second)
            {
                terminate(out);
                return 0;
            }

            --grades[i].second;
            // Create the list of adjance, marking a vertex between this 2 nodes
            adj[grades[0].first].push_back(grades[i].first);
            adj[grades[i].first].push_back(grades[0].first);
            out << grades[0].first << ' ' << grades[i].first << '\n';
        }

        // If the last decremented grade becomes lesser in value then the grade
        // that follows it, merge this two chunks of array (it will dispose the first element)
        if (grades.size() > 2 && grades[grades[0].second].second < grades[grades[0].second + 1].second)
            interclas(grades, grades[0].second + 1);
        else
            grades.erase(grades.begin()); // Otherwise, delete the first value
    }

    out << "B:\n";

    // If there is any isolated node or the number of vertexs are different then
    // n - 1, it's impossible to create a tree
    if (isolated || grade_sum != (nr_nodes - 1) * 2) {
    	out << "Impossible!\n";
    	return 0;
    }

    queue< pair<int, int> > terminal; // Nodes that have grade equal to 1
    queue< pair<int, int> >  not_terminal; // Otherwise
    vector<int> father(nr_nodes, 0);
    // Insert each node to it's coresponding queue
    for (auto i = save.begin(); i != save.end(); ++i)
    	if (i->second == 1)
    		terminal.push(*i);
    	else not_terminal.push(*i);

    while (!not_terminal.empty()) {
    	pair<int, int> fn_terminal = not_terminal.front();
    	
        // While the grade of the node is greater then 1, attach terminal
        // nodes to it
    	while (fn_terminal.second > 1) {
    		--fn_terminal.second;
            // Establish a connection from the node to the terminal nodes attached
    		father[terminal.front().first] = fn_terminal.first;
    		terminal.pop();
    	}
        // Then push the node to terminal queue
    	terminal.push(fn_terminal);
    	not_terminal.pop();
    }

    // For the remaining terminal nodes, connect them between themselves
    while (!terminal.empty()) {
    	int front = terminal.front().first;
    	terminal.pop();
    	father[front] = terminal.front().first;
    	terminal.pop();
    }

    for (int i = 0; i < nr_nodes; ++i)
    	if (father[i])
    		out << i << ' ' << father[i] << '\n';

    out.close();

    return 0;
}
