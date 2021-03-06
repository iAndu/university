#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

#ifndef FILE
#define FILE

class File {
    vector<string> text;
    vector<string>::iterator it;
    string path;

public:
    void SetPath(string param) {
        this->path = param;
    }
    string GetPath() {
        return this->path;
    }
    void AddLine(string line) {
        this->text.push_back(line);
    }
    string GetNextLine() {
        string line = *it;
        ++it;
        return line;
    }
    void GoToBegining() {
        this->it = this->text.begin();
    }
    bool EndOfFile() {
        return (this->it == this->text.end());
    }
};

#endif // FILE

int main() {
    File file;
    string path;

    cout << "Include file's path: ";
    cin >> path;

    file.SetPath(path);
    ifstream in(file.GetPath());
    string line;
    while (getline(in, line)) {
        file.AddLine(line);
    }
    in.close();

    cout << "Press ENTER to get the file line by line:\n";
    cout << "FILE_PATH: " << file.GetPath() << "\n";
    file.GoToBegining();
    cin.get();
    while (!file.EndOfFile()) {
        cin.get();
        cout << file.GetNextLine();
    }

    return 0;
}
