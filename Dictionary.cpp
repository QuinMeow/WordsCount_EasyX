#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	string line;
	string word;
	//stringstream ss;
	vector<string> v_line;

	regex word_reg("[a-z|A-Z]+"); //无符号字母

	while (getline(input, line)) //按换行符获取行
	{
		sregex_token_iterator pos(line.begin(), line.end(), word_reg, 0); //正则匹配获取单词
		decltype(pos) end;
		for (; pos != end; ++pos)
			v_line.push_back(pos->str());

		/*ss.str(line); //以空格分割获取单词
		while (getline(ss, word, ' ')) 
		{
			v_line.push_back(word);
		}*/

		d.map.push_back(v_line);
		v_line.clear(); //清空当前行

	}
	return input;
}

void Dictionary::Count(string word) const
{
	unsigned int counts=0;
	for (unsigned int i = 0; i < map.size(); i++)
		for (unsigned int j = 0; j < map[i].size(); j++)
			if (map[i][j] == word)
				counts++;
	cout << "The word \"" << word << "\" appeared "<< counts << " times" << endl;
}

void Dictionary::Locate(string word) const
{
	for (unsigned int i = 0; i < map.size(); i++)
		for (unsigned int j = 0; j < map[i].size(); j++)
			if (map[i][j] == word)
				cout << "Line " << i+1 << " Word " << j+1 << endl;
}
