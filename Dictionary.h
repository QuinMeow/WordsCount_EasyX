#include <iostream>
#include <fstream>
#include <graphics.h>
#include <vector>
#include <string>
#include <regex>
#include <conio.h>

const int HASH_SIZE = 100;
using namespace std;

struct HashNode
{
	string key;
	vector<pair<int, int>> location;
	HashNode(string &a, int row, int col) :key(a) { location.push_back(make_pair(row, col)); }
};

class Dictionary
{
public:
	Dictionary() { HashTable = new vector<HashNode>[HASH_SIZE]; }
	~Dictionary() {}
	void Count(string word) const; //计数
	void Locate(string word) const; //定位
	void Empty(); //清空
	friend ifstream& operator>>(ifstream& input, Dictionary& d);

protected:
	vector<vector<string>> map; //邻接矩阵存储
	vector<HashNode>* HashTable; //散列表

	int Hash(string& word) const; //生成哈希值
	void InsertHashWithDisplay(string word, int row, int col); //插入到哈希表并显示
	void InsertHash(string word, int row, int col); //插入到哈希表并显示
	int SearchHash(string& word) const; //搜索哈希表
	void InitialDisplay() const;
	void DisplayHash(int pos, int layer = -1) const; //绘制部分哈希表


};