#include <iostream>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

struct expression {
    int current, next;
    char event;
};

vector<int>** create_automata(vector<expression> exp, unordered_map<char, int> event_map, int nr_states) {
    vector<int>** table = new vector<int>*[nr_states];
    for (int i = 0; i < nr_states; ++i)
        table[i] = new vector<int>[event_map.size()];

    for (vector<expression>::iterator it = exp.begin(); it != exp.end(); ++it)
        table[it->current][event_map[it->event]].push_back(it->next);

    return table;
}

bool accepted_word(string word, vector<int>** table, unordered_set<int> f_states, unordered_map<char, int> event_map) {
    unordered_set<int> state;
    state.insert(0);

    for (unsigned int i = 0; i < word.length(); ++i) {
        unordered_set<int> aux;
        for (unordered_set<int>::iterator it = state.begin(); it != state.end(); ++it) {
            vector<int> next = table[*it][event_map[word[i]]];
            for (vector<int>::iterator jt = next.begin(); jt != next.end(); ++jt)
                aux.insert(*jt);
        }
        state = aux;
    }

    for (unordered_set<int>::iterator it = state.begin(); it != state.end(); ++it)
        if (f_states.find(*it) != f_states.end())
            return true;

    return false;
}

int main() {
    ifstream in("NFA.in");
    unordered_set<int> final_states;
    unordered_set<int> states;
    vector<expression> exp;
    unordered_map<char, int> event_map;

    string line;
    getline(in, line);
    for (unsigned int i = 0; i < line.length(); ++i)
        if (isdigit(line[i]))
            final_states.insert(line[i] - '0');

    expression e;
    int index = 0;
    while (in >> e.current >> e.event >> e.next) {
        exp.push_back(e);
        states.insert(e.current);
        states.insert(e.next);
        if (event_map.find(e.event) == event_map.end())
            event_map[e.event] = index++;
    }

    vector<int> **table = create_automata(exp, event_map, states.size());

    cout << "Input your word: ";
    string word;
    while (word != "t") {
    cin >> word;
    if (accepted_word(word, table, final_states, event_map))
        cout << "Word is accepted!";
    else cout << "Word isn't accepted!";
    }

    return 0;
}
