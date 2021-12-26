#include "Dictionary.h"

ifstream& operator>>(ifstream& input, Dictionary& d)
{
	string line;
	string word;
	//stringstream ss;
	vector<string> v_line;

	regex word_reg("[a-z|A-Z]+"); //�޷�����ĸ

	while (getline(input, line)) //�����з���ȡ��
	{
		sregex_token_iterator pos(line.begin(), line.end(), word_reg, 0); //����ƥ���ȡ����
		decltype(pos) end;
		for (; pos != end; ++pos)
			v_line.push_back(pos->str());

		/*ss.str(line); //�Կո�ָ��ȡ����
		while (getline(ss, word, ' ')) 
		{
			v_line.push_back(word);
		}*/

		d.map.push_back(v_line);
		v_line.clear(); //��յ�ǰ��

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
