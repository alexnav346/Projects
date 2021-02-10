#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Tables.h"


typedef struct {
	int hash;
	int tupleNumber;
} Pairs;

class HashBuckets
{

private:


	//Bucket 1 = a, 2 = b, 3 = c
	vector<Pairs> a, b, c;

	vector<Pairs>::iterator itA, itB, itC;

	Pairs temp;

public:

	HashBuckets()
	{
		;
	}

	//This function adds hash value and tuple row number to the one of the buckets
	//Values from first table
	void insertBucket(int hashValue, int tupleNumber)
	{
		temp.hash = hashValue;
		temp.tupleNumber = tupleNumber;

		if (hashValue == 0)
		{
			a.push_back(temp);
			//cout << "pushed on a\n";
		}
		else if (hashValue == 1)
		{
			b.push_back(temp);
			//cout << "pushed on b\n";
		}
		else if (hashValue == 2)
		{
			c.push_back(temp);
			//cout << "pushed on c\n";
		}
		else
		{
			cout << "did fucking nothing........\n";
		}
	}

	vector<Pairs> getA()
	{
		return a;
	}

	vector<Pairs> getB()
	{
		return b;
	}

	vector<Pairs> getC()
	{
		return c;
	}

	void printRows()
	{
		//cout << "a size: " << a.size() << endl;
		//cout << "b size: " << b.size() << endl;
		//cout << "c size: " << c.size() << endl;

		itA = a.begin();
		itB = b.begin();
		itC = c.begin();

		int tupleCount = a.size();
		cout << "Bucket A:\n";
		for (int i = 0; i < tupleCount; i++)
		{
			cout << itA->hash << "  " << itA->tupleNumber << endl;
			itA++;
		}
		cout << endl;
		
		tupleCount = b.size();
		cout << "Bucket B:\n";
		for (int i = 0; i < tupleCount; i++)
		{
			cout << itB->hash << "  " << itB->tupleNumber << endl;
			itB++;
		}
		cout << endl;

		tupleCount = c.size();
		cout << "Bucket C:\n";
		for (int i = 0; i < tupleCount; i++)
		{
			cout << itC->hash << "  " << itC->tupleNumber << endl;
			itC++;
		}

		cout << endl;
	}

};