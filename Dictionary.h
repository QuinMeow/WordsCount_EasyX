#include <iostream>
#include <fstream>
#include <sstream>
#include <graphics.h>
#include <vector>
#include <string>

using namespace std;
class Dictionary
{
public:
	Dictionary() {}
	~Dictionary() {}
	unsigned int Count(string word) const;
	vector<vector<int>> Locate(string word) const;
	friend ifstream& operator>>(ifstream& input, Dictionary& d);

private:
	vector<vector<string>> map;
};