#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int readFile(vector<string> &words)
{
    string fileName = "test.txt";
    fstream fin;
    fin.open(fileName, ios::in);
    if (!fin.is_open()) {
        cout << "read file " << fileName << " failed." << endl;
        return 1;
    }

    string w;
    while (fin >> w) 
        words.push_back(w);

    return 0;
}

bool isShorter(const string &w1, const string &w2)
{
    return w1.size() < w2.size();
}

void limDups(vector<string> &words)
{
    stable_sort(words.begin(), words.end(), isShorter);
    // auto end_unique = unique(words.begin(), words.end());
    // words.erase(end_unique, words.end());
}
int main ()
{
    vector<string> words;
    readFile(words);
    limDups(words);
    for (auto &i : words)
        cout << i << " ";
    cout << endl;
    return 0;
}