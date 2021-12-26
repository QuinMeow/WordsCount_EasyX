#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include "Dictionary.h"
using namespace std;

string& trim(string& s) //去除字符串前后引号
{
	if (s.empty())
	{
		return s;
	}
	s.erase(0, s.find_first_not_of("\""));
	s.erase(s.find_last_not_of("\"") + 1);
	return s;
}

int main()
{
	ifstream infile;
	string path, word;
	Dictionary dic;
	int operate = 0;
	while (operate != 4)
	{

		cout << "1----Load Document" << endl
			<< "2----Count a word" << endl
			<< "3----Locate a word" << endl
			<< "4----Exit" << endl
			<< "Choose Your Operation:";
		cin >> operate;
		cin.clear();  //忽略重复操作
		cin.ignore(65535, '\n');
		switch (operate)
		{
		case 1:
			if (infile.is_open())//若已打开，则先关闭
			{
				infile.close(); 
				dic.Empty(); //清空原有
			}
			cout << "Input the path: ";
			getline(cin, path, '\n'); //路径可能含空格
			infile.open(trim(path), ios::in); //打开文件
			if (!infile.is_open())
				cerr << "Can't open with " << path << endl;
			else
				infile >> dic; //传入文件流
			break;
		case 2:
			if (!infile.is_open()) //文件未打开
				cerr << "Document haven't been loaded!" << endl;
			else
			{
				cout << "Input the word: ";
				cin >> word;
				dic.Count(word);
			}
			break;
		case 3:
			if (!infile.is_open())
				cerr << "Document haven't been loaded!" << endl;
			else
			{
				cout << "Input the word: ";
				cin >> word;
				dic.Locate(word);
			}
			break;
		case 4:
			if (infile.is_open())
				infile.close(); //关闭文件流
			return 1;
		default:
			cout << "Wrong Operation" << endl;
			break;
		}
	}
}