#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	string line;
	string word;
	stringstream ss;
	vector<string> v_line;

	while (getline(input, line)) //���л�ȡ
	{
		ss.str(line);
		while (getline(ss, word, ' ')) //�Կո�ָ��ȡ����
		{
			v_line.push_back(word);
		}
		d.map.push_back(v_line);
	}
	return input;
}
