#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include "Dictionary.h"
using namespace std;

int main()
{
	ifstream infile;
	string path;
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
		cin.ignore(65535,'\n'); 
		switch (operate)
		{
		case 1:
			cout << "Input the path: ";
			getline(cin, path, '\n');
			infile.open(path, ios::in); //打开文件
			if (!infile.is_open())
				cerr << "Can't open with " << path << endl;
			else
			{
				infile >> dic; //传入文件流
				infile.close();
			}
			break;
		case 2:
			cout << "Count a word" << endl;
			break;
		case 3:
			cout << "Locate a word" << endl;
			break;
		case 4:
			return 1;
		default:
			cout << "Wrong Operation" << endl;
			break;
		}
	}

}