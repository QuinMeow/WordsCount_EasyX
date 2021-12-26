#include <iostream>
#include <fstream>
#include <sstream>
#include <graphics.h>
#include <vector>
#include <string>
#include <regex>

using namespace std;
class Dictionary
{
public:
	Dictionary() {}
	~Dictionary() {}
	void Count(string word) const; //����
	void Locate(string word) const; //��λ
	void Empty() { map.clear(); } //���
	friend ifstream& operator>>(ifstream& input, Dictionary& d);

private:
	vector<vector<string>> map; //�ڽӾ���洢
};