#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
using namespace std;


#ifndef EXPRESSION
#define EXPRESSION
class Expression {
    int current_state, next_state;
    char e_event;

public:
    Expression(int c_state, int n_state, char event) {
        current_state = c_state;
        next_state = n_state;
        e_event = event;
    }

    Expression() {
        current_state = next_state = e_event = 0;
    }

    int current() { return current_state; }
    int next() { return next_state; }
    char event() { return e_event; }
    void set_current(int state) { current_state = state; }
    void set_next(int state) { next_state = state; }
    void set_event(char event) { e_event = event; }
};
#endif // EXPRESSION


#ifndef LANG
#define LANG
class Language {
    int starting_state = 0;
    unordered_set<int> final_states;
    vector<Expression> expressions;
    unordered_map<char, int> events;
    int** transition_table;
    int nr_states = 0, nr_events = 0;

public:
    Language(vector<Expression> exp, int starting_state, unordered_set<int> final_states) {
        expressions = exp;
        starting_state = starting_state;
        this->final_states = final_states;

        unordered_set<int> states;
        int index = 0;
        for (vector<Expression>::iterator it = expressions.begin(); it != expressions.end(); ++it) {
            states.insert(it->current());
            states.insert(it->next());
            if (events.find(it->event()) == events.end()) {
                events[it->event()] = index++;
            }
        }
        nr_states = states.size();
        nr_events = events.size();

        transition_table = new int*[nr_states];
        for (int i = 0; i < nr_states; ++i) {
            transition_table[i] = new int[nr_events];
            for (int j = 0; j < nr_events; ++j) {
                transition_table[i][j] = -1;
            }
        }
        for (vector<Expression>::iterator it = expressions.begin(); it != expressions.end(); ++it) {
            transition_table[it->current()][events[it->event()]] = it->next();
        }
    }

    bool in_language(string word) {
        int current_state = starting_state;

        for (unsigned int i = 0; i < word.length(); ++i) {
            current_state = transition_table[current_state][events[word[i]]];
            if (current_state == -1) {
                return false;
            }
        }
        if (final_states.find(current_state) != final_states.end()) {
            return true;
        }
        return false;
    }

    unordered_set<int> get_f_states() { return final_states; }
    vector<Expression> get_expressions() { return expressions; }
    unordered_map<char, int> get_events() { return events; }
    int count_states() { return nr_states; }
    int count_events() { return nr_events; }
    int** get_table() { return transition_table; }
    int get_s_state() { return starting_state; }
};
#endif // LANG


int main() {
    ifstream in("DFA.in");
    string line;

    getline(in, line);
    unordered_set<int> final_states;
    for (unsigned int i = 0; i < line.length(); ++i)
        if (isdigit(line[i]))
            final_states.insert(line[i] - '0');

    vector<Expression> exp;
    Expression e;
    int a, c;
    char b;
    while (in >> a >> b >> c) {
        e.set_current(a);
        e.set_next(c);
        e.set_event(b);
        exp.push_back(e);
    }

    Language lang(exp, 0, final_states);
    cout << "Input your word: ";
    string word;
    cin >> word;
    if (lang.in_language(word))
        cout << "Word is in language!\n";
    else cout << "Word isn't in language!\n";

    return 0;
}
