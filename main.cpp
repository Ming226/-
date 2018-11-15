#include "Calculator.h"
#include<string>
int main()
{
	caculator test;
	int con = 1;

	while (con)
	{
		test.run();
		cout << "ÊÇ·ñ¼ÌÐø£¿1/0" << endl;
		cin >> con;
		cin.ignore();
	}

	system("PAUSE");
	return 0;
}