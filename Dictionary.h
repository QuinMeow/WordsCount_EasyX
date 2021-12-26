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
	void Count(string word) const; //计数
	void Locate(string word) const; //定位
	void Empty() { map.clear(); } //清空
	friend ifstream& operator>>(ifstream& input, Dictionary& d);

private:
	vector<vector<string>> map; //邻接矩阵存储
};