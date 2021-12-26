#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	int row = 0, col = 0; //用于统计行列
	string line;
	string word;
	vector<string> v_line;

	regex word_reg("[a-z|A-Z]+"); //无符号字母

	while (getline(input, line)) //按换行符获取行
	{
		sregex_token_iterator pos(line.begin(), line.end(), word_reg, 0); //正则匹配获取单词
		decltype(pos) end;
		for (; pos != end; ++pos)
		{
			d.InsertHash(pos->str(), row, col); //将单词插入哈希表
			col++;
		}
		col = 0;
		row++;
	}
	return input;
}

void Dictionary::Count(string word) const
{
	int pos = Hash(word); //获取桶
	int layer = SearchHash(word); //获取在桶的第几层
	if (layer != -1)
	{
		int counts = HashTable[pos][layer].location.size(); //直接获取位置数量
		cout << "The word \"" << word << "\" appeared " << counts << " times" << endl;
	}
	else
		cout << "The word \"" << word << "\" didn't been found!" << endl;

}

void Dictionary::Locate(string word) const
{
	int pos = Hash(word);
	int layer = SearchHash(word);
	if (layer != -1)
	{
		vector<pair<int, int>>::iterator location = HashTable[pos][layer].location.begin();
		for (; location != HashTable[pos][layer].location.end(); ++location) //逐个输出位置
			cout << "Line " << location->first + 1 << " Word " << location->second + 1 << endl;
	}
	else
		cout << "The word \"" << word << "\" didn't been found!" << endl;
}

void Dictionary::Empty()
{
	map.clear();
	for (int i = 0; i < HASH_SIZE; i++)
		HashTable[i].clear();
}

int Dictionary::Hash(string& word) const
{
	int seed = 31;
	int hash = 0;
	int strln = word.length();
	for (int i = 0; i < strln; i++)
		hash = (hash * seed + word[i]) % HASH_SIZE; //哈希算法
	return hash % HASH_SIZE;
}

void Dictionary::InsertHash(string word, int row, int col)
{
	bool find = false;
	int pos = Hash(word); //获取单词哈希值
	vector<HashNode>::iterator Point;
	for (Point = HashTable[pos].begin(); Point != HashTable[pos].end(); ++Point) //遍历该哈希值的桶
	{
		if (Point->key == word) //该单词已经出现过
		{
			Point->location.push_back(make_pair(row, col)); //追加位置
			find = true;
			break;
		}
	}
	if (!find) //该单词未出现
		HashTable[pos].push_back(HashNode(word, row, col)); //将该单词放入桶
}

int Dictionary::SearchHash(string& word) const
{
	int layer = 0;
	int pos = Hash(word);
	vector<HashNode>::iterator Point;
	for (Point = HashTable[pos].begin(); Point != HashTable[pos].end(); ++Point) //遍历该哈希值的桶
	{
		if (Point->key == word) //在桶内找到了单词
		{
			return layer; //返回在桶内的层级
		}
		layer++;
	}
	return -1; //没有找到返回-1
}
