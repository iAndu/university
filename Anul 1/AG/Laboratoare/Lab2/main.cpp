#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <stack>
using namespace std;

vector<bool> viz;
vector<int> min_level;
vector<int> level;
set<int> crit_nodes;
vector< pair<int, int> > crit_edges;
stack< pair<int, int> > comp_edges;
vector< set<int> > comp;
vector< vector< pair<int, int> > > c_edges;

/*void stash_comp(int father, int son)
{
    set<int> c;
    vector< pair<int, int> > x;
    int tx, ty;

    do
    {
        tx = comp_edges.top().first;
        ty = comp_edges.top().second;
        c.insert(tx);
        c.insert(ty);
        x.push_back(make_pair(tx, ty));
        comp_edges.pop();
    } while (tx != father && ty != son);

    comp.push_back(c);
    c_edges.push_back(x);
}*/

void build_tree(int node, int nr_nodes, vector<int> adj[], vector<int> &father) {
    viz[node] = 1;
        for (vector<int>::iterator it = adj[node].begin(); it != adj[node].end(); ++it) {
            if (!viz[*it]) {
                father[*it] = node;
                level[*it] = level[node] + 1;
                build_tree(*it, nr_nodes, adj, father);
            }
        }
}

/*void print_stack(int father, int son)
{
    stack< pair<int, int> > s = comp_edges;
    
    while (s.top().first != father && s.top().second != son)
    {
        cout << s.top().first << ' ' << s.top().second << endl;
        s.pop();
    }
    cout << endl;
}*/

void find_crits(int node, int nr_nodes, vector<int> adj[], vector<int> &father) {
    viz[node] = 1;
    min_level[node] = level[node];
    for (vector<int>::iterator it = adj[node].begin(); it != adj[node].end(); ++it) {
        if (!viz[*it]) {
            //comp_edges.push(make_pair(node, *it));
            //cout << node << ' ' << *it << '\n';
            find_crits(*it, nr_nodes, adj, father);
            if (min_level[*it] >= level[node] && father[node]) {
                crit_nodes.insert(node);
                //print_stack(node, *it);
            }
            /*if (min_level[*it] >= level[node])
                stash_comp(node, *it);
            comp_edges.pop();*/
            if (min_level[*it] > level[node]) {
                crit_edges.push_back(make_pair(node, *it));
            }
        }
        if (*it != father[node]) {
            min_level[node] = min(min_level[node], min_level[*it]);
        }
    }
}

int main() {
    int nr_nodes, nr_edges;

    ifstream in("graf.in");
    in >> nr_nodes >> nr_edges;
    vector<int> adj[nr_nodes + 1];
    vector<int> father(nr_nodes + 1);
    viz.resize(nr_nodes + 1, 0);
    min_level.resize(nr_nodes + 1, 0);
    level.resize(nr_nodes + 1, 0);
    for (int i = 0; i < nr_edges; ++i) {
        int x, y;
        in >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    in.close();

    build_tree(1, nr_nodes, adj, father);
    int sons = 0;
    for (int i = 1; i <= nr_nodes; ++i) {
        if (father[i] == 1) {
            ++sons;
        }
    }

    for (int i = 1; i <= nr_nodes; ++i) {
        viz[i] = 0;
    }
    find_crits(1, nr_nodes, adj, father);
    if (sons > 1) {
        crit_nodes.insert(1);
    }

    ofstream out("graf.out");
    out << "Legaturi critice:\n";
    for (vector< pair<int, int> >::iterator it = crit_edges.begin(); it != crit_edges.end(); ++it) {
        out << it->first << ' ' << it-> second << '\n';
    }
    out << "Noduri vulnerabile:\n";
    for (set<int>::iterator it = crit_nodes.begin(); it != crit_nodes.end(); ++it) {
        out << *it << '\n';
    }

    int i = 0;
    int maxim = comp[0].size();

    for (int j = 1; j < comp.size(); ++j)
        if (comp[j].size() > maxim)
        {
            maxim = comp[j].size();
            i = j;
        }

    out << "Componeneta biconexa maximala:\n";
    for (auto j = comp[i].begin(); j != comp[i].end(); ++j)
        out << *j << ' ';
    out << '\n';
    for (auto j = c_edges[i].begin(); j != c_edges[i].end(); ++j)
        out << j->first << ' ' << j->second << '\n';

    out.close();

    return 0;
}
