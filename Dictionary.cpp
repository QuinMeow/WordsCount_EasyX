#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	int row = 0, col = 0; //����ͳ������
	string line;
	string word;
	vector<string> v_line;

	regex word_reg("[a-z|A-Z]+"); //�޷�����ĸ

	while (getline(input, line)) //�����з���ȡ��
	{
		sregex_token_iterator pos(line.begin(), line.end(), word_reg, 0); //����ƥ���ȡ����
		decltype(pos) end;
		for (; pos != end; ++pos)
		{
			d.InsertHash(pos->str(), row, col); //�����ʲ����ϣ��
			col++;
		}
		col = 0;
		row++;
	}
	return input;
}

void Dictionary::Count(string word) const
{
	int pos = Hash(word); //��ȡͰ
	int layer = SearchHash(word); //��ȡ��Ͱ�ĵڼ���
	if (layer != -1)
	{
		int counts = HashTable[pos][layer].location.size(); //ֱ�ӻ�ȡλ������
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
		for (; location != HashTable[pos][layer].location.end(); ++location) //������λ��
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
		hash = (hash * seed + word[i]) % HASH_SIZE; //��ϣ�㷨
	return hash % HASH_SIZE;
}

void Dictionary::InsertHash(string word, int row, int col)
{
	bool find = false;
	int pos = Hash(word); //��ȡ���ʹ�ϣֵ
	vector<HashNode>::iterator Point;
	for (Point = HashTable[pos].begin(); Point != HashTable[pos].end(); ++Point) //�����ù�ϣֵ��Ͱ
	{
		if (Point->key == word) //�õ����Ѿ����ֹ�
		{
			Point->location.push_back(make_pair(row, col)); //׷��λ��
			find = true;
			break;
		}
	}
	if (!find) //�õ���δ����
		HashTable[pos].push_back(HashNode(word, row, col)); //���õ��ʷ���Ͱ
}

int Dictionary::SearchHash(string& word) const
{
	int layer = 0;
	int pos = Hash(word);
	vector<HashNode>::iterator Point;
	for (Point = HashTable[pos].begin(); Point != HashTable[pos].end(); ++Point) //�����ù�ϣֵ��Ͱ
	{
		if (Point->key == word) //��Ͱ���ҵ��˵���
		{
			return layer; //������Ͱ�ڵĲ㼶
		}
		layer++;
	}
	return -1; //û���ҵ�����-1
}
