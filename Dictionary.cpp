#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	int row = 0, col = 0; //用于统计行列
	char display;
	string line;
	string word;
	vector<string> v_line;
	regex word_reg("[a-z|A-Z]+"); //无符号字母

	cout << "Show the process? [y/N]" << endl;
	cin >> display;
	if (display == 'y' || display == 'Y')
	{
		d.InitialDisplay();
		while (getline(input, line)) //按换行符获取行
		{
			sregex_token_iterator pos(line.begin(), line.end(), word_reg, 0); //正则匹配获取单词
			decltype(pos) end;
			for (; pos != end; ++pos)
			{
				d.InsertHashWithDisplay(pos->str(), row, col); //将单词插入哈希表
				col++;
			}
			col = 0;
			row++;
		}
		closegraph();
	}
	else
	{
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

void Dictionary::InsertHashWithDisplay(string word, int row, int col)
{
	bool find = false;
	int pos = Hash(word); //获取单词哈希值
	/*vector<HashNode>::iterator Point;
	for (Point = HashTable[pos].begin(); Point != HashTable[pos].end(); ++Point) //遍历该哈希值的桶
	{
		if (Point->key == word) //该单词已经出现过
		{
			Point->location.push_back(make_pair(row, col)); //追加位置
			find = true;
			break;
		}
	}*/
	for (int i = 0; i < HashTable[pos].size(); i++)
	{
		if (HashTable[pos][i].key == word)
		{
			HashTable[pos][i].location.push_back(make_pair(row, col));
			DisplayHash(pos, i);
			find = true;
			break;
		}
	}
	if (!find) //该单词未出现
	{
		HashTable[pos].push_back(HashNode(word, row, col)); //将该单词放入桶
		DisplayHash(pos, HashTable[pos].size() - 1);
	}
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
	{
		HashTable[pos].push_back(HashNode(word, row, col)); //将该单词放入桶
	}
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

void Dictionary::InitialDisplay() const
{
	initgraph(720, 480);
	setbkcolor(WHITE);
	setorigin(360, 150);
	cleardevice();
}

void Dictionary::DisplayHash(int pos, int layer) const
{
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	settextcolor(BLACK);
	RECT Tables[7];
	TCHAR s[50];
	//绘制桶
	for (int i = -3; i <= 3; i++)
	{
		if (pos + i < 0 || pos + i >= 100)
			continue; //超出范围不绘制
		Tables[i + 3] = { i * 80 - 40, -40, (i + 1) * 80 - 40, 40 };
		rectangle(i * 80 - 40, -40, (i + 1) * 80 - 40, 40);

		_stprintf_s(s, _T("%d"), pos + i);
		drawtext(s, &Tables[i + 3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 2);
	rectangle(-40, -40, 40, 40);
	//绘制字符信息
	if (layer != -1)
	{
		//绘制key
		_stprintf_s(s, 50, _T("%S"), HashTable[pos][layer].key.c_str());
		settextcolor(BLACK);
		outtextxy(-20, 50, _T("Key:"));
		settextcolor(RED);
		outtextxy(-20, 65, s);
		//绘制次数
		settextcolor(BLACK);
		_stprintf_s(s, 50, _T("%d"), HashTable[pos][layer].location.size());
		outtextxy(-20, 80, _T("Times:"));
		settextcolor(RED);
		outtextxy(-20, 95, s);
		//绘制位置
		settextcolor(BLACK);
		outtextxy(-20, 110, _T("Locations:"));
		settextcolor(RED);
		for (int i = 0; i < HashTable[pos][layer].location.size(); i++)
		{
			_stprintf_s(s, 50, _T("Line %d"), HashTable[pos][layer].location[i].first);
			outtextxy(-20, 125, s);
			_stprintf_s(s, 50, _T("Word %d"), HashTable[pos][layer].location[i].second);
			outtextxy(-20, 140, s);
		}
	}
	_getch();
}

