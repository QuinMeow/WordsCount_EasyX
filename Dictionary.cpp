#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	string line;
	string word;
	//stringstream ss;
	vector<string> v_line;

	regex word_reg("[a-z|A-Z]+"); //�޷�����ĸ

	while (getline(input, line)) //���л�ȡ
	{
		//����ƥ��
		sregex_token_iterator pos(line.begin(), line.end(), word_reg, 0);
		decltype(pos) end;
		for (; pos != end; ++pos)
			v_line.push_back(pos->str());
		/*ss.str(line);
		while (getline(ss, word, ' ')) //�Կո�ָ��ȡ����
		{
			v_line.push_back(word);
		}*/
		d.map.push_back(v_line);
		v_line.clear(); //��յ�ǰ��

	}
	return input;
}
