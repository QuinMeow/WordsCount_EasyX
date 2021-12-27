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
	void Count(string word) const; //����
	void Locate(string word) const; //��λ
	void Empty(); //���
	friend ifstream& operator>>(ifstream& input, Dictionary& d);

protected:
	vector<vector<string>> map; //�ڽӾ���洢
	vector<HashNode>* HashTable; //ɢ�б�

	int Hash(string& word) const; //���ɹ�ϣֵ
	void InsertHashWithDisplay(string word, int row, int col); //���뵽��ϣ����ʾ
	void InsertHash(string word, int row, int col); //���뵽��ϣ����ʾ
	int SearchHash(string& word) const; //������ϣ��
	void InitialDisplay() const;
	void DisplayHash(int pos, int layer = -1) const; //���Ʋ��ֹ�ϣ��


};