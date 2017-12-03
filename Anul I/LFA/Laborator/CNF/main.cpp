#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>

#define SIGMA 26

using namespace std;

map<char, set<string> > production;
set<char> vars;
bool mark[SIGMA];




void read() {
	ifstream in("Grammar.in");

	while(!in.eof()) {
		char str[255];
		in.getline(str, 255);
		if (!in.eof()) {
			char *p = strtok(str, " ");
			char state = *p;
			vars.insert(*p);
			p = strtok(NULL, " ");
			while ((p = strtok(NULL, " ")) != NULL) {
				production[state].insert(p);
				p = strtok(NULL, " ");
			}
		}
	}
	in.close();
}

void print() {
	ofstream out("Grammar.out");

	for (auto i : production) {
		out << i.first << " -> ";
		for (auto j : i.second) {
			out << j << " | ";
		}
		out << '\n';
	}

	out.close();
}






// Step 1






// Mark all nullable productions
void markNullable() {
	// If a production contains lambda, mark it
	for (auto i : production)
		for (auto j : i.second)
			if (j == "_") {
				mark[i.first - 'A'] = true;
				break;
			}

	// Mark all productions that go into a null production
	bool ok;
	do {
		ok = false;

		for (auto i : production)
			for (auto j : i.second)
				if (!mark[i.first - 'A'] && j.size() == 1 && mark[j[0] - 'A']) {
					mark[i.first - 'A'] = true;
					ok = true;
					break;
				}
	} while(ok);
}

bool valid(int k, vector<int> &stack) {
	for (int i = 0; i < k; ++i)
		if (stack[i] >= stack[k])
			return false;
	return true;
}

// Gets a string and returns a string without certain null variables
string addString(string str, vector<int> &stack, vector<int> &pos, int k) {
	for (int i = 0; i <= k; ++i) {
		str.erase(pos[stack[i]] - i, 1);
	}
	return str;
}

// Returns new productions after removing nullable variables from productions
set<string> getNewProds(string str) {
	vector<int> pos;
	// Mark nullable variables in string(production)
	for (int i = 0; i < str.length(); ++i)
		if (mark[str[i] - 'A'])
			pos.push_back(i);

	set<string> prods;
	vector<int> stack(pos.size() + 1, -1);
	// Backtracking. Get all productions from production S by removing nullable variables
	int k = 0;
	while (k >= 0) {
		if (k == pos.size())
			--k;
		else if ((int)stack[k] < (int)pos.size() - 1) {
			++stack[k];
			if (valid(k, stack)) {
				prods.insert(addString(str, stack, pos, k));
				++k;
			}
		} else stack[k--] = -1;
	}

	return prods;
}

// Adds new productions for each variable by removing nullable variables from productions
void addNewProds() {
	for (auto i = production.begin(); i != production.end(); ++i) {
		set<string> prods;
		for (auto j : i->second) {
			set<string> aux = getNewProds(j);
			prods.insert(aux.begin(), aux.end());
		}
		i->second.insert(prods.begin(), prods.end());
	}		
}

// Removes lambda productions
void removeLambdaProds() {
	for (auto i = production.begin(); i != production.end(); ++i)
		if (mark[i->first - 'A'])
			for (auto j = i->second.begin(); j != i->second.end(); ++j)
				if (*j == "_")
					i->second.erase(j);
}




// Step 2




void renameProductions() {
	// Add productions from simple transitions like V -> N
	for (auto i = production.begin(); i != production.end(); ++i)
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
			if (j->size() == 1 && (*j)[0] <= 'Z') 
				i->second.insert(production[(*j)[0]].begin(), production[(*j)[0]].end());

	// Remove all single-variabled productions
	for (auto i = production.begin(); i != production.end(); ++i)
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
			if (j->size() == 1 && (*j)[0] <= 'Z') 
				i->second.erase(j);
}





// Step 3




// Replace long productions with new ones and create new ones
void replaceLongProds() {
	srand(time(0));
	bool ok;
	// While there are still productions that have three or more letters
	do {
		ok = false;
		for (map<char, set<string> >::iterator i = production.begin(); i != production.end(); ++i)
			for (set<string>::iterator j = i->second.begin(); j != i->second.end(); ++j)
				// If the production has more then two letters
				if (j->size() > 2) {
					ok = true;

					stringstream ss;
					// Fetch the last two letters
					string str = j->substr(j->size() - 2, 2);

					bool sw = false;
					// Check if there already exists a variable that defines this production
					for (auto k : production) {
						if (k.second.size() == 1 && *(k.second.begin()) == str) {
							sw = true;
							// Remove the production
							i->second.erase(j);

							ss << k.first;
							string aux;
							ss >> aux;

							// Add the new production
							i->second.insert(j->substr(0, j->size() - 2) + aux);
						}
					}

					// If there is no such variable, create a new one
					if (!sw) {
						char new_var;
						// Do while the variable name isn't used
						do {
							new_var = (char)(rand() % 26 + 'A');
						} while(vars.find(new_var) != vars.end());
						// Add the new var to the set
						vars.insert(new_var);
						// Insert the production to the variable
						production[new_var].insert(str);
						// Remove the production
						i->second.erase(j);

						ss << new_var;
						string aux;
						ss >> aux;

						// Insert the new production
						i->second.insert(j->substr(0, j->size() - 2) + aux);
					}
				}
	} while (ok);
}




// Step 4






int containsLetter(string str) {
	for (int i = 0; i < str.size(); ++i)
		if (str[i] >= 'a' && str[i] <= 'z')
			return i;
	return -1;
}

// Replace all productions like Va, with VAa, where Aa -> a
void replaceCombined() {
	srand(time(0));	

	int pos;
	// For each production
	for (map<char, set<string> >::iterator i = production.begin(); i != production.end(); ++i)
		for (set<string>::iterator j = i->second.begin(); j != i->second.end(); ++j)
			// If it contains a letter, save the position where it is
			if (j->size() == 2 && (pos = containsLetter(*j)) != -1) {
				bool sw = false;
				// Check if there already exists a variable that defines this production
				for (auto k : production) {
					if (k.second.size() == 1 && (*(k.second.begin()))[0] == (*j)[pos]) {
						sw = true;
						// Remove the production
						i->second.erase(j);

						stringstream ss;
						ss << k.first;
						string aux;
						ss >> aux;

						// Add the new production depending on the position of the letter
						if (pos == 0)
							i->second.insert(aux + j->substr(1, 1));
						else
							i->second.insert(j->substr(0, 1) + aux);
					}
				}

				// If there is no such variable, create a new one
				if (!sw) {
					char new_var;
					// Do while the variable name isn't used
					do {
						new_var = (char)(rand() % 26 + 'A');
					} while(vars.find(new_var) != vars.end());
					// Add the new var to the set
					vars.insert(new_var);
					// Insert the production to the variable
					stringstream ss;
					ss << (*j)[pos];
					string aux;
					ss >> aux;
					production[new_var].insert(aux);
					// Remove the production
					i->second.erase(j);

					// Create a string from the letter-variable
					stringstream sz;
					sz << new_var;
					string aux2;
					sz >> aux2;

					// Insert the new production depending on the position of the letter
					if (pos == 0)
						i->second.insert(aux2 + j->substr(1, 1));
					else
						i->second.insert(j->substr(0, 1) + aux2);
				}
			}
}

int main() {
	read();

	// Step 1
	markNullable();
	addNewProds();
	removeLambdaProds();

	// Step 2
	renameProductions();

	// Step 3
	replaceLongProds();

	// Step 4
	replaceCombined();

	print();

	return 0;
}