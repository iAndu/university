/*
    Complexitate - citire in O(n), construirea arborelui O(n), verificare O(n)
*/

#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <climits>
#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *left, *right;

    Node(int d = 0) : data(d), left(NULL), right(NULL) { }
};

unordered_map<int, bool> checked;

bool is_number(string &str) {
    string::iterator it = str.begin();
    
    while (it != str.end() && isdigit(*it)) {
        ++it;
    }

    return !str.empty() && it == str.end();
}

Node* build_tree(istream &in) {
    string str;
    Node *root = NULL;
    in >> str;

    if (is_number(str)) {
        root = new Node(atoi(str.c_str()));
        root->left = build_tree(in);
        root->right = build_tree(in);
    }

    return root;
}

bool is_binary_tree(Node *root, int min_value, int max_value) {
    if (!root) {
        return true;
    }

    return !checked[root->data]++ && root->data < max_value && root->data > min_value && 
            is_binary_tree(root->left, min_value, root->data) &&
            is_binary_tree(root->right, root->data, max_value);
}

int main() {
    ifstream in("date.in");
    Node *root = build_tree(in);
    in.close();

    ofstream out("date.out");
    if (is_binary_tree(root, INT_MIN, INT_MAX)) {
        out << "da\n";
    } else {
        out << "nu\n";
    }
    out.close();

    return 0;    
}