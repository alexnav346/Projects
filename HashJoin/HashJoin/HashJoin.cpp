//Hash Join Project
//Alex Navarre

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Tables.h"
#include "Buckets.h"

using namespace std;

//used during getKey() method
bool checkInput(string input, bool table)
{
	char test = input.at(0);

	if (table == true)
	{
		if (test == 'A' || test == 'B' || test == 'C' || test == 'a' || test == 'b' || test == 'c')
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else if (table == false)
	{
		if (test == 'W' || test == 'X' || test == 'Y' || test == 'Z' || test == 'w' || test == 'x' || test == 'y' || test == 'z')
		{
			return true;
		}
		else
		{
			return false;
		}
	}


}

//gets key from user input
void getFirstColumn(char&column)
{
	string input;

	cout << "Select Column from R1(a, b, c): ";
	cin >> input;
	cout << endl;

	bool test = checkInput(input, true);
	
	if (test == false)
	{
		do
		{
			cout << "Error invalid input, please re-enter: ";
			cin >> input;
			cout << endl;
			test = checkInput(input, true);
		} while (test == false);
	}
	else
	{
		;
	}

	column = tolower(input.at(0));
}

void getSecondColumn(char&column)
{
	string input;

	cout << "Select Column from R2(w, x, y, z): ";
	cin >> input;
	cout << endl;

	bool test = checkInput(input, false);

	if (test == false)
	{
		do
		{
			cout << "Error invalid input, please re-enter: ";
			cin >> input;
			cout << endl;
			test = checkInput(input, false);
		} while (test == false);
	}
	else
	{
		;
	}

	column = tolower(input.at(0));
}

int getHashValue(int value)
{
	return (value % 3);
}

//Used to process FirstTable
void processFile1(ifstream&file, FirstTable&table, char column, HashBuckets&bucks)
{
	int word;
	int tupleNumber = 1;
	int a, b, c = 0;
	int counter = 0;
	
	while (file >> word)
	{
		if (counter == 0)
		{
			a = word;
			counter++;
		}
		else if (counter == 1)
		{
			b = word;
			counter++;
		}
		else if (counter == 2)
		{
			c = word;
			table.addTuple(a, b, c);
			counter = 0;

			if (column == 'a')
			{
				//hash this value, record tuple row number
				bucks.insertBucket(getHashValue(a), tupleNumber);
			}
			else if (column == 'b')
			{
				bucks.insertBucket(getHashValue(b), tupleNumber);
			}
			else if (column == 'c')
			{
				bucks.insertBucket(getHashValue(c), tupleNumber);
			}

			tupleNumber++;
		}

	}
	
}

//Used to process SecondTable
void processFile2(ifstream&file, FirstTable&table1, SecondTable&table2, FinalTable&table3, char column, HashBuckets&bucks)
{
	int word;
	int tupleNumber = 1;
	int a, b, c, w, x, y, z = 0;
	int counter = 0;
	int temp;
	vector<Pairs> tempPair;
	vector<Pairs>::iterator it;

	while (file >> word)
	{
		if (counter == 0)
		{
			w = word;
			counter++;
		}
		else if (counter == 1)
		{
			x = word;
			counter++;
		}
		else if (counter == 2)
		{
			y = word;
			counter++;
		}
		else if (counter == 3)
		{
			z = word;
			table2.addTuple(w, x, y, z);
			counter = 0;

			if (column == 'w')
			{
				//hash value w
				//use HV to determine which bucket to search
				if (getHashValue(w) == 0)
				{
					//check bucket a
					//void getTuple(int lineNumber, int&one, int&two, int&three)
					tempPair = bucks.getA();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}

				}
				else if (getHashValue(w) == 1)
				{
					//check bucket b
					tempPair = bucks.getB();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}
				}
				else if (getHashValue(w) == 2)
				{
					//check bucket c
					tempPair = bucks.getC();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}
				}
				else
				{
					cout << "processFile2() failed at choosing hash bucket to search\n";
				}

			}
			else if (column == 'x')
			{
				if (getHashValue(x) == 0)
				{
					//check bucket a
					//void getTuple(int lineNumber, int&one, int&two, int&three)
					tempPair = bucks.getA();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}

				}
				else if (getHashValue(x) == 1)
				{
					//check bucket b
					tempPair = bucks.getB();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}
				}
				else if (getHashValue(x) == 2)
				{
					//check bucket c
					tempPair = bucks.getC();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}
				}
				else
				{
					cout << "processFile2() failed at choosing hash bucket to search\n";
				}
			}
			else if (column == 'y')
			{
				if (getHashValue(y) == 0)
				{
					//check bucket a
					//void getTuple(int lineNumber, int&one, int&two, int&three)
					tempPair = bucks.getA();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}

				}
				else if (getHashValue(y) == 1)
				{
					//check bucket b
					tempPair = bucks.getB();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}
				}
				else if (getHashValue(y) == 2)
				{
					//check bucket c
					tempPair = bucks.getC();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}
				}
			}
			else if (column == 'z')
			{
				if (getHashValue(z) == 0)
				{
					//check bucket a
					//void getTuple(int lineNumber, int&one, int&two, int&three)
					tempPair = bucks.getA();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}

				}
				else if (getHashValue(z) == 1)
				{
					//check bucket b
					tempPair = bucks.getB();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}
				}
				else if (getHashValue(z) == 2)
				{
					//check bucket c
					tempPair = bucks.getC();
					if (tempPair.size() > 0)
					{
						it = tempPair.begin();
						for (int i = 0; i < tempPair.size(); i++)
						{
							table1.getTuple(it->tupleNumber, a, b, c);
							table3.addTuple(a, b, c, w, x, y, z);
							it++;
						}
					}
					else
					{
						cout << "no match\n";
					}
				}
			}

			tupleNumber++;
		}
	}
}

//File "validation", only works with file in right format!
ifstream checkFile()
{
	string fileName;
	string test;

	cout << "Enter File Name: ";
	cin >> fileName;

	ifstream file;
	file.open(fileName);

	while (!file.is_open())
	{
		cout << "Couldn't find file, re-enter: ";
		cin >> fileName;
		file.open(fileName);
	}

	return file;
}

int main()
{
	//Joining tables on this columns
	char firstJoin, secondJoin;

	FirstTable test1;
	SecondTable test2;
	FinalTable test3;

	HashBuckets testBuckets;

	int w, x, y, z = 0;


	//Inputing and procesing R1
	ifstream file1 = checkFile();
	getFirstColumn(firstJoin);
	processFile1(file1, test1, firstJoin, testBuckets);


	//Inputing and processing R2
	ifstream file2 = checkFile();
	getSecondColumn(secondJoin);
	processFile2(file2, test1, test2, test3, secondJoin, testBuckets);


	//printing out tables
	test1.printRows();
	test2.printRows();
	test3.printRows();

	//testBuckets.printRows();
}