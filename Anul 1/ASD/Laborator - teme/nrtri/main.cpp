#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> match;

int binarySearch(int left, int right, int value) {
    int mid;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (match[mid] == value) {
            return mid;
        } else if (match[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return right;
}

int findLast(int index, int noOfMatches) {
    while (index < noOfMatches - 1 && match[index] == match[index + 1]) {
        ++index;
    }

    return index;
}

int main() {
    int noOfMatches, nrSol = 0;

    ifstream in("nrtri.in");
    in >> noOfMatches;
    for (int i = 0; i < noOfMatches; ++i) {
        int lenOfMatch;
        in >> lenOfMatch;
        match.push_back(lenOfMatch);
    }
    in.close();

    sort(match.begin(), match.end());

    for (int i = 0; i < noOfMatches - 1; ++i) {
        for (int j = i + 1; j < noOfMatches; ++j) {
            int searchedVal = match[i] + match[j];
            int index = binarySearch(0, noOfMatches - 1, searchedVal);
            index = findLast(index, noOfMatches);
            if (index > j) {
                nrSol += index - j;
            }
        }
    }

    ofstream out("nrtri.out");
    out << nrSol << '\n';
    out.close();

    return 0;
}
