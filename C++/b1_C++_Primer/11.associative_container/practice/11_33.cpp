#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>

using namespace std;

map<string, string> buildMap(ifstream &map_file)
{
	map<string, string> m;
	string line;
	string key;
	string value;
	while (map_file >> key && getline(map_file, value)) {
		if (value.size() < 1)
			throw runtime_error("no  rule for " + key);
		else
			m[key] = value.substr(1);
//		m.insert({key, value.substr(1)}); // the difference between them is whether the original value will be overwritten. 
	}
	return m;
}

string& transform(string &s, map<string, string> &m)
{
	if (m.count(s) == 0) {
		return s;
	} else {
		return m[s];
	}
}

int word_transform(ifstream &map_file, ifstream &input)
{
	auto trans_map = buildMap(map_file);
	string word;
	string text;
	while (getline(input, text)) {
		istringstream stream(text);
		while(stream >> word){
			cout << transform(word, trans_map) << " ";
		}
		cout << '\b' << endl;
	}

	return 0;
}
int main(int argc, char **argv)
{
	ifstream map_file(argv[1]);
	ifstream input(argv[2]);
	word_transform(map_file, input);
	return 0;
}
