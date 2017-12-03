#include <cstdio>
#include <vector>

using namespace std;

struct tree {
    int val, mark;
};

void markAncestors(int node, vector<tree> &father, int step) {
    while(node != 0) {
        father[node - 1].mark = step;
        node = father[node - 1].val;
    }
}

int findAncestor(int node, vector<tree> &father, int step) {
    while (father[node - 1].mark != step) {
        node = father[node - 1].val;
    }

    return node;
}

int main() {
    vector<tree> father;
    tree node;
    int noOfNods, noOfQuestions;

    FILE *input = fopen("lca.in", "r");
    fscanf(input, "%d %d", &noOfNods, &noOfQuestions);
    node.mark = -1;
    node.val = 0;
    father.push_back(node);
    for (int i = 0; i < noOfNods - 1; ++i) {
        fscanf(input, "%d", &node.val);
        father.push_back(node);
    }

    FILE *output = fopen("lca.out", "w");
    for (int i = 0; i < noOfQuestions; ++i) {
        int firstNode, secondNode, comAncestor;
        fscanf(input, "%d %d", &firstNode, &secondNode);

        markAncestors(firstNode, father, i);
        comAncestor = findAncestor(secondNode, father, i);
        fprintf(output, "%d\n", comAncestor);
    }
    fclose(input);
    fclose(output);

    return 0;
}
