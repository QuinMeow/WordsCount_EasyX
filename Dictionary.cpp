#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	string line;
	string word;
	//stringstream ss;
	vector<string> v_line;

	regex word_reg("[a-z|A-Z]+"); //无符号字母

	while (getline(input, line)) //按行获取
	{
		//正则匹配
		sregex_token_iterator pos(line.begin(), line.end(), word_reg, 0);
		decltype(pos) end;
		for (; pos != end; ++pos)
			v_line.push_back(pos->str());
		/*ss.str(line);
		while (getline(ss, word, ' ')) //以空格分割获取单词
		{
			v_line.push_back(word);
		}*/
		d.map.push_back(v_line);
		v_line.clear(); //清空当前行

	}
	return input;
}
