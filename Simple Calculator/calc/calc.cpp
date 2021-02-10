//CIS-400 Calculator Program
//Alex Navarre

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>

using namespace std;

//string testString = "4+4+4-2=";
string testString = "5*8/2=";

bool scanStringError(string test)
{
	bool failed = false;

	//test for consec operators
	for (int i = 0; i < (test.size() - 1); i++)
	{
		if (test.at(i) == '+' || test.at(i) == '-' || test.at(i) == '/' || test.at(i) == '*')
		{
			if (test.at(i + 1) == '+' || test.at(i + 1) == '-' || test.at(i + 1) == '/' || test.at(i + 1) == '*')
			{
				failed = true;
			}
		}
	}

	//start operator
	if (test.at(0) == '+' || test.at(0) == '-' || test.at(0) == '/' || test.at(0) == '*')
		failed = true;

	//last char operator
	if (test.at(test.size() - 2) == '+' || test.at(test.size() - 2) == '-' || test.at(test.size() - 2) == '/' || test.at(test.size() - 2) == '*')
		failed = true;

	if (test.at(test.size() - 1) != '=')
		failed = true;

	return failed;
}

int main()
{
	vector<int> v1;
	vector<char> v2;

	cout << "Test String: " << testString << endl << endl;
	
	//char x = '9';
	//int y = (int)x - 48;

	if (scanStringError(testString))
	{
		cout << "Error: invalid input" << endl;
		return 0;
	}

	for (int i = 0; i < testString.size(); i++)
	{
		if (testString.at(i) == '+' || testString.at(i) == '-' || testString.at(i) == '/' || testString.at(i) == '*')
		{
			v2.push_back(testString.at(i));
		}
		else if (testString.at(i) == '=')
		{
			;
		}
		else
		{
			v1.push_back((int)testString.at(i) - 48);
		}
	}

	vector<int>::iterator iter;
	vector<int>::iterator iter2;
	vector<char>::iterator iter3;
	int op1, op2;
	
	while (v1.size() > 1)
	{
		//find highest precedence operator
		int j = v2.size() - 1;
		bool found = false;

		iter = v1.end();
		iter--;
		iter2 = v1.end();
		iter2--; iter2--;
		iter3 = v2.end();
		iter3--;

		while (!found && j >= 0)
		{
			//cout << "loop to find operator: " << j << endl;
			if (v2.at(j) == '+' || v2.at(j) == '-')
			{
				//cout << "found operator at: " << j << endl;
				op1 = v1.at(j);
				op2 = v1.at(j + 1);
				//cout << "op1=" << op1 << " op2=" << op2 << endl;

				if (v2.at(j) == '+')
					(*iter2) = (op1 + op2);
				else
					(*iter2) = (op1 - op2);

				v1.erase(iter);
				v2.erase(iter3);

				found = true;
			}
			else
			{
				if(iter != v1.begin())
					iter--;

				if(iter3 != v2.begin())
					iter3--;

				if (iter2 != v1.begin())
					iter2--;
			}
			j--;
		}

		if (!found)
		{
			iter = v1.end();
			iter--;
			iter2 = v1.end();
			iter2--; iter2--;
			iter3 = v2.end();
			iter3--;

			j = v2.size() - 1;
			//cout << "look for * or /" << endl;
			bool found2 = false;
			while (!found2 && j >= 0)
			{
				//cout << "loop to find operator: " << j << endl;
				if (v2.at(j) == '*' || v2.at(j) == '/')
				{
					//cout << "found operator at: " << j << endl;
					op1 = v1.at(j);
					op2 = v1.at(j + 1);
					//cout << "op1=" << op1 << " op2=" << op2 << endl;

					if (v2.at(j) == '*')
						(*iter2) = (op1 * op2);
					else
						(*iter2) = (op1 / op2);

					v1.erase(iter);
					v2.erase(iter3);

					found2 = true;
				}
				else
				{
					if (iter != v1.begin())
						iter--;

					if (iter3 != v2.begin())
						iter3--;

					if (iter2 != v1.begin())
						iter2--;
				}
				j--;
			}
		}
		else
			;
	}
	cout << "Answer: " << v1.at(0);
	}