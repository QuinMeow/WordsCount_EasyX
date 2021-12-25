#include <iostream>
#include <graphics.h>
#include <string>
#include "Dictionary.h"
using namespace std;

int main()
{
	int operate = 0;
	while (operate != 4)
	{

		cout << "1----Load Document" << endl
			<< "2----Count a word" << endl
			<< "3----Locate a word" << endl
			<< "4----Exit" << endl
			<< "Choose Your Operation:";
		cin >> operate;
		switch (operate)
		{
		case 1:
			cout << "Load Document" << endl;
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