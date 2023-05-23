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

bool short5(const string &w1)
{
    return w1.size() < 5;
}

vector<string>::iterator my_partition(vector<string> &words, bool short5(const string &w1))
{
    int l = 0, r = words.size() - 1;
    for (;l < r;) {
        while (short5(words[l])) l++;
        while (!short5(words[r])) r--;
        if (l < r) swap(words[l], words[r]);
    }
    return words.begin() + l;
}

int main ()
{
    vector<string> words;
    readFile(words);

    auto begin5 = my_partition(words, short5);
    // auto begin5 = partition(words.begin(), words.end(), short5); // stl

    cout << "less 5:" << endl;
    for (auto it = words.begin(); it != begin5; ++it)
        cout << *it << " ";
    cout << endl;

    cout << "greater 5:" << endl;
    for (auto it = begin5; it != words.end(); ++it)
        cout << *it << " ";
    cout << endl;
    return 0;
}