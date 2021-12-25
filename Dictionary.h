#include <iostream>
#include <graphics.h>
#include <vector>
#include <string>

class Dictionary
{
public:
	Dictionary() {}
	~Dictionary() {}
	unsigned int Count(string word) const;
	vector<vector<int>> Locate(string word) const;

	friend istream& operator<< (istream& input, const Dictionary& d);
private:
	vector<vector<string>> map;
};