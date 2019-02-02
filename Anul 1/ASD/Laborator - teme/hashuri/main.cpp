#include <fstream>
#include <vector>
#define HASH 7640827
using namespace std;

struct nod {
    int val;
    nod *next;
};

vector<nod*> vec(HASH);

void add_to_hash(int x) {
    nod *new_nod = new nod;
    new_nod->val = x;

    if (vec[x % HASH] == NULL) {
        new_nod->next = NULL;
        vec[x % HASH] = new_nod;
        return;
    }
    nod *aux = vec[x % HASH];
    while (aux != NULL) {
        if (aux->val == x)
            return;
        aux = aux->next;
    }
    new_nod->next = vec[x % HASH];
    vec[x % HASH] = new_nod;
}

void delete_hash(int x) {
    if (vec[x % HASH] == NULL) {
        return;
    }
    if (vec[x % HASH]->val == x) {
        nod *aux = vec[x % HASH];
        vec[x % HASH] = aux->next;
        delete aux;
        return;
    }
    nod *aux = vec[x % HASH];
    while (aux->next != NULL && aux->next->val != x) {
        aux = aux->next;
    }
    if (aux->next != NULL) {
        nod *save = aux->next;
        aux->next = aux->next->next;
        delete save;
    }
}

bool find_hash(int x) {
    if (vec[x % HASH] == NULL) {
        return false;
    }
    nod *aux = vec[x % HASH];
    while (aux != NULL) {
        if (aux->val == x) {
            return true;
        }
        aux = aux->next;
    }
    return false;
}

int main() {
    int n;

    ifstream in("hashuri.in");
    ofstream out("hashuri.out");
    in >> n;
    for (int i = 0; i < n; ++i) {
        int op, val;
        in >> op >> val;
        switch (op) {
            case 1: add_to_hash(val);
                    break;
            case 2: delete_hash(val);
                    break;
            case 3: out << find_hash(val) << '\n';
                    break;
        }
    }
    in.close();
    out.close();

    return 0;
}
