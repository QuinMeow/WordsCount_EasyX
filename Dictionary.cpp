#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	string line;
	string word;
	stringstream ss;
	vector<string> v_line;

	while (getline(input, line)) //按行获取
	{
		ss.str(line);
		while (getline(ss, word, ' ')) //以空格分割获取单词
		{
			v_line.push_back(word);
		}
		d.map.push_back(v_line);
	}
	return input;
}
